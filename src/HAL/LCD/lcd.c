/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/LCD/lcd.h"
#include "MCAL/GPIO/gpio.h"

/*****************************************************************************/
/*                               Macros                                      */
/*****************************************************************************/
#define ENABLE_DONE             ((enableState == ENABLE_STATE_READY) && enableTime_mS)


#define CMD_FUNCTION_SET            (uint8_t)((1<<5)|(LCD_MODE<<4)|(LCD_NUM_LINES<<3)|(LCD_FONT<<2))
#define CMD_DISPLAY_CONTROL         (uint8_t)((1<<3)|(lcdCfg.display<<2)|(lcdCfg.cursor<<1)|lcdCfg.blink)
#define CMD_ENTRY_MODE_SET          (uint8_t)((1<<2)|(lcdCfg.cursor_dir<<1)|(lcdCfg.disp_shift))
#define CMD_CLEAR_SCREEN            (uint8_t)(0x01)
#define CMD_GOTO_X0Y0               (uint8_t)(0x80)
#define CMD_GOTO_X0Y1               (uint8_t)(0xC0)

#define LCD_TASK_TICK_MS            2
#define POWER_ON_DELAY_MS           30

#define ENABLE_STATE_READY          1
#define ENABLE_STATE_HIGH           2
#define ENABLE_STATE_LOW            3

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef enum {
    initState_powerOn,
    initState_functionSet,
    initState_displayControl,
    initState_clearScreen,
    initState_entryModeSet,
    // initState_done    
}initState_t;

typedef enum {
    writeState_ready,
    writeState_setCursor,
    writeState_writeChar
}writeState_t;

typedef enum {
    reqType_write,
    reqType_clear,
    reqType_setCursor,
    reqType_writeXY,
    reqType_blinkCursor
}reqType_t;

typedef struct {
    lcdReqState_t reqState;
    reqType_t reqType; 
    callback_t reqCallback;
}usrReq_t;

typedef struct {
    const uint8_t* data;
    uint8_t len;
    uint8_t x;
    uint8_t y;
    uint8_t currentIndex;
}writeReq_t;

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
extern lcdCfg_t lcdCfg;

static lcdState_t lcdState = lcdState_off;

static initState_t initState = initState_powerOn;

static uint8_t enableTime_mS = 0;
static uint8_t enableState = ENABLE_STATE_READY;

static writeReq_t writeReq;
static usrReq_t usrReq;

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/
static void init();
static void setCursor();
static void clearScreen();
static void sendCmd(uint8_t cmd);
static void sendData(uint8_t data);
static void writeByte(uint8_t data);
static void trgEnable();
static void writeCharXY();
static void writeChar();
static void blinkCursor();

/*****************************************************************************/
/*                              Module Task                                  */
/*****************************************************************************/
/*      1mS     */
void Lcd_task() {
    switch(lcdState){
        case lcdState_off:
            break;
        case lcdState_init:
            init();
            // if(initState == initState_done) {
            //     lcdState = lcdState_operational;
            // }
            break;
        case lcdState_operational:
            if(usrReq.reqState == lcdReqState_done) {
                usrReq.reqState = lcdReqState_noReq;
            }
            if(usrReq.reqState == lcdReqState_inProgress) {
                switch(usrReq.reqType) {
                    case reqType_clear:
                        clearScreen();
                        if(ENABLE_DONE){
                            usrReq.reqState = lcdReqState_done;
                            if(usrReq.reqCallback){
                                usrReq.reqCallback();
                            }
                        }
                        break;
                    case reqType_writeXY:
                        writeCharXY();
                        if(writeReq.currentIndex == writeReq.len) {
                            usrReq.reqState = lcdReqState_done;
                            if(usrReq.reqCallback){
                                usrReq.reqCallback();
                            }
                        }
                        break;
                    case reqType_write:
                        writeChar();
                        if(writeReq.currentIndex == writeReq.len) {
                            usrReq.reqState = lcdReqState_done;
                            if(usrReq.reqCallback){
                                usrReq.reqCallback();
                            }
                        }
                        break;
                    case reqType_setCursor:
                        setCursor();
                        if(ENABLE_DONE){
                            usrReq.reqState = lcdReqState_done;
                            if(usrReq.reqCallback){
                                usrReq.reqCallback();
                            }
                        }
                        break;
                    case reqType_blinkCursor:
                        blinkCursor();
                        if(ENABLE_DONE){
                            usrReq.reqState = lcdReqState_done;
                            if(usrReq.reqCallback){
                                usrReq.reqCallback();
                            }
                        }
                        break;
                    

                }
            }
            break;
    }
}

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
static void writeCharXY(){
    static writeState_t writeState = writeState_ready;
    switch(writeState) {
        case writeState_ready:
            writeState = writeState_setCursor;
            break;
        case writeState_setCursor:
            setCursor();
            if(ENABLE_DONE){
                writeState = writeState_writeChar;
            }
            break;
        case writeState_writeChar:
            sendData(writeReq.data[writeReq.currentIndex]);
            if(ENABLE_DONE) {
                writeReq.currentIndex++;
                if(writeReq.currentIndex == 16){
                    writeState = writeState_setCursor;
                    writeReq.x = 0;
                    writeReq.y = 1;
                }
                if(writeReq.currentIndex == writeReq.len) {
                    writeState = writeState_ready;
                    usrReq.reqState = lcdReqState_done;
                }                
            }
            break;
    }
}

static void writeChar(){
    sendData(writeReq.data[writeReq.currentIndex]);
    if(ENABLE_DONE) {
        writeReq.currentIndex++;
        if(writeReq.currentIndex == writeReq.len) {
            usrReq.reqState = lcdReqState_done;
        }                
    }
}

static void init() {
    static uint8_t init_mS = 0;
    switch(initState) {
        case initState_powerOn:
            if(init_mS == POWER_ON_DELAY_MS) {
                initState = initState_functionSet;
            }
            init_mS += LCD_TASK_TICK_MS;
            break;
        case initState_functionSet:
            sendCmd(CMD_FUNCTION_SET);
            if(ENABLE_DONE) {
                initState = initState_displayControl;
            }
            break;
        case initState_displayControl:
            sendCmd(CMD_DISPLAY_CONTROL);
            if(ENABLE_DONE) {
                initState = initState_clearScreen;
            }
            break;
        case initState_clearScreen:
            sendCmd(CMD_CLEAR_SCREEN);
            if(ENABLE_DONE) {
                initState = initState_entryModeSet;
            }
            break;
        case initState_entryModeSet:
            sendCmd(CMD_ENTRY_MODE_SET);
            if(ENABLE_DONE) {
                // initState = initState_done;
                lcdState = lcdState_operational;
            }
            break;
    } 
}
static void setCursor() {
    if(writeReq.y == 0) {
        sendCmd(CMD_GOTO_X0Y0 + writeReq.x);    
    }
    else if(writeReq.y == 1) {
		sendCmd(CMD_GOTO_X0Y1 + writeReq.x);
	}    
}
static void blinkCursor(){
    sendCmd(CMD_DISPLAY_CONTROL);
}
void lcd_blinkCursorAsync(uint8_t cursor_state, callback_t callback_blinkCursor){
    if(usrReq.reqState != lcdReqState_inProgress){
        usrReq.reqState = lcdReqState_inProgress;
        usrReq.reqType = reqType_blinkCursor;
        
        lcdCfg.cursor = cursor_state;
        lcdCfg.blink = cursor_state;

        usrReq.reqCallback = callback_blinkCursor;
    }
}
static void clearScreen(){
    sendCmd(CMD_CLEAR_SCREEN);
}

static void sendCmd(uint8_t cmd) {
    if(enableState == ENABLE_STATE_READY){
        gpio_setPinValue(lcdCfg.lcdPinsArr[rs].port,lcdCfg.lcdPinsArr[rs].pin,PIN_VALUE_LOW);
        writeByte(cmd); 
    }    
    trgEnable();
}
static void sendData(uint8_t data) {
    if(enableState == ENABLE_STATE_READY){
        gpio_setPinValue(lcdCfg.lcdPinsArr[rs].port,lcdCfg.lcdPinsArr[rs].pin,PIN_VALUE_HIGH);
        writeByte(data);
    }
    trgEnable();
}
static void writeByte(uint8_t data) {
    gpio_setPinValue(lcdCfg.lcdPinsArr[rw].port,lcdCfg.lcdPinsArr[rw].pin,PIN_VALUE_LOW);
    for(uint8_t i = d0; i <= d7; i++){        
        gpio_setPinValue(lcdCfg.lcdPinsArr[i].port,lcdCfg.lcdPinsArr[i].pin,((data>>i) & 1));
    }
}
// static void sendHalfByte(uint8_t data);
static void trgEnable() {
    if(enableState == ENABLE_STATE_READY) {
        enableTime_mS = 0;
        enableState = ENABLE_STATE_HIGH;
    }
    enableTime_mS += LCD_TASK_TICK_MS;
    switch(enableState){
        case ENABLE_STATE_HIGH:
            gpio_setPinValue(lcdCfg.lcdPinsArr[e].port,lcdCfg.lcdPinsArr[e].pin,PIN_VALUE_HIGH);
            if(enableTime_mS == 2){
                enableState = ENABLE_STATE_LOW;
            }
            break;
        case ENABLE_STATE_LOW:
            gpio_setPinValue(lcdCfg.lcdPinsArr[e].port,lcdCfg.lcdPinsArr[e].pin,PIN_VALUE_LOW);
            if(enableTime_mS == 4){
                enableState = ENABLE_STATE_READY;
            }
            break;
    }
}

lcdState_t lcd_getLCDState() {
    return lcdState;
}
lcdReqState_t lcd_getReqState() {
    return usrReq.reqState;
}

void lcd_initAsync() {
    lcdState = lcdState_init;
    gpioPin_t initPin = {
        .af = AF_SYSTEM,
        .mode = MODE_OUTPUT_PP,
        .speed = SPEED_HIGH
    };
    for(uint8_t i = (uint8_t)d0; i <= (uint8_t)e; i++) {
        initPin.port = lcdCfg.lcdPinsArr[i].port;
        initPin.pin = lcdCfg.lcdPinsArr[i].pin;
        gpio_initPin(&initPin);
    }
}
void lcd_writeStringXYAsync(uint8_t* dataStringPtr, uint8_t len, uint8_t x, uint8_t y, callback_t callback_writeXY) {
    if(usrReq.reqState != lcdReqState_inProgress) {
        usrReq.reqState =  lcdReqState_inProgress;
        usrReq.reqType = reqType_writeXY;
        usrReq.reqCallback = callback_writeXY;
        writeReq.data = dataStringPtr;
        writeReq.currentIndex = 0;
        writeReq.len = len;
        writeReq.x = x;
        writeReq.y = y;
    }
}

void lcd_writeStringAsync(uint8_t* dataStringPtr, uint8_t len, callback_t callback_write) {
    if(usrReq.reqState != lcdReqState_inProgress) {
        usrReq.reqState =  lcdReqState_inProgress;
        usrReq.reqType = reqType_write;
        usrReq.reqCallback = callback_write;
        writeReq.data = dataStringPtr;
        writeReq.currentIndex = 0;
        writeReq.len = len;
    }
}

void lcd_clearScreenAsync(callback_t callback_clear) {
    if(usrReq.reqState != lcdReqState_inProgress) {
        usrReq.reqState =  lcdReqState_inProgress;
        usrReq.reqType = reqType_clear;
        usrReq.reqCallback = callback_clear;
    }
}

void lcd_setCursorAsync(uint8_t x, uint8_t y, callback_t callback_cursor) {
    if(usrReq.reqState != lcdReqState_inProgress) {
        usrReq.reqState =  lcdReqState_inProgress;
        usrReq.reqType = reqType_setCursor;
        usrReq.reqCallback = callback_cursor;
        writeReq.x = x;
        writeReq.y = y;
    }
}


