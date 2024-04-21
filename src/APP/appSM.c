#include "APP/app.h"
#include"HAL/H_SW/H_sw.h"
#include"HAL/LCD/lcd.h"

extern uint64_t stopwatchTime;
extern uint64_t timestamp;
extern uint8_t hrs;
extern uint8_t min;
extern uint8_t sec;

extern uint8_t pressedKey_id;

uint8_t state = APP_STATE_CLOCK;
uint8_t stopwatchState = STOPWATCH_STATE_RESET;
uint8_t clockState = CLOCK_STATE_DISPLAY;

uint8_t i_cursor = 0;

uint8_t clock[32] = "Date 12-04-2024 Clock 00:00:00  ";
uint8_t stopwatch[32] = "  00:00:00.00                   ";

static uint8_t numToAscii(uint8_t num);
static void incCursor();
static void decCursor();
static void setCursorBlink(uint8_t cursor_state);
static void lcdCBF();

void appSM(){

    switch(state){
        case APP_STATE_CLOCK:
            clock[22] = numToAscii(hrs / 10);
            clock[23] = numToAscii(hrs % 10);
            clock[25] = numToAscii(min / 10);
            clock[26] = numToAscii(min % 10);
            clock[28] = numToAscii(sec / 10);
            clock[29] = numToAscii(sec % 10);
            lcd_writeStringXYAsync(clock,32,0,0,lcdCBF);
            // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
            if(pressedKey_id == sw_mode){
                state = APP_STATE_STOPWATCH;
            }
            else{
                switch(clockState){
                    case CLOCK_STATE_DISPLAY:
                        setCursorBlink(CURSOR_STATE_OFF);
                        if(pressedKey_id == sw_edit_reset){
                            clockState = CLOCK_STATE_EDIT;
                        }
                        break;
                    case CLOCK_STATE_EDIT:
                    {
                        setCursorBlink(CURSOR_STATE_ON);
                        // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
                        if(pressedKey_id == sw_ok_start){
                            clockState = CLOCK_STATE_DISPLAY;
                        }
                        else if(pressedKey_id == sw_right) {
                            incCursor();
                            // i_cursor++;
                            // if(i_cursor == 32){
                            //     i_cursor = 0;
                            // }
                        }
                        else if(pressedKey_id == sw_left){
                            decCursor();
                            // if(i_cursor == 0){
                            //     i_cursor = 32;
                            // }
                            // i_cursor--;
                        }
                        else if(pressedKey_id == sw_up){
                            if(i_cursor == 22){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 36000000;
                                }
                                else {
                                    timestamp += 36000000;
                                }
                            }
                            else if(i_cursor == 23){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 3600000;
                                }
                                else {
                                    timestamp += 3600000;
                                }
                            }
                            else if(i_cursor == 25){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 600000;
                                }
                                else {
                                    timestamp += 600000;
                                }
                            }
                            else if(i_cursor == 26){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 60000;
                                }
                                else {
                                    timestamp += 60000;
                                }
                            }
                            else if(i_cursor == 28){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 10000;
                                }
                                else {
                                    timestamp += 10000;
                                }
                            }
                            else if(i_cursor == 29){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 1000;
                                }
                                else {
                                    timestamp += 1000;
                                }
                            }
                        }
                        else if(pressedKey_id == sw_down){
                            if(i_cursor == 22){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 36000000;
                                }
                                else {
                                    timestamp -= 36000000;
                                }
                            }
                            else if(i_cursor == 23){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 3600000;
                                }
                                else {
                                    timestamp -= 3600000;
                                }
                            }
                            else if(i_cursor == 25){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 600000;
                                }
                                else {
                                    timestamp -= 600000;
                                }
                            }
                            else if(i_cursor == 26){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 60000;
                                }
                                else {
                                    timestamp -= 60000;
                                }
                            }
                            else if(i_cursor == 28){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 10000;
                                }
                                else {
                                    timestamp -= 10000;
                                }
                            }
                            else if(i_cursor == 29){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 1000;
                                }
                                else {
                                    timestamp -= 1000;
                                }
                            }
                        }
                    }
                    break;
                }
            }
            break;
        case APP_STATE_STOPWATCH:
            stopwatch[2] = numToAscii(((stopwatchTime / (1000 * 60 * 60)) % 24) / 10);
            stopwatch[3] = numToAscii(((stopwatchTime / (1000 * 60 * 60)) % 24) % 10);
            stopwatch[5] = numToAscii(((stopwatchTime / (1000 * 60)) % 60) / 10);    
            stopwatch[6] = numToAscii(((stopwatchTime / (1000 * 60)) % 60) % 10);
            stopwatch[8] = numToAscii(((stopwatchTime / 1000) % 60) / 10);
            stopwatch[9] = numToAscii(((stopwatchTime / 1000) % 60) % 10);
            stopwatch[11] = numToAscii(((stopwatchTime / 10) % 100) / 10);
            stopwatch[12] = numToAscii(((stopwatchTime / 10) % 100) % 10);
            lcd_writeStringXYAsync(stopwatch,32,0,0,NULL);
            setCursorBlink(CURSOR_STATE_OFF);
            if(pressedKey_id == sw_mode){
                state = APP_STATE_CLOCK;
            }
            else{
                switch(stopwatchState){
                    case STOPWATCH_STATE_RESET:
                        stopwatchTime = 0;
                        if(pressedKey_id == sw_ok_start){
                            stopwatchState = STOPWATCH_STATE_RUN;
                        }
                        break;
                    case STOPWATCH_STATE_RUN:
                        
                        // if(pressedKey_id == sw_edit_reset){
                        //     stopwatchState = STOPWATCH_STATE_RESET;
                        // }
                        if(pressedKey_id == sw_ok_start){
                            stopwatchState = STOPWATCH_STATE_PAUSE;
                        }
                        break;
                    case STOPWATCH_STATE_PAUSE:
                        if(pressedKey_id == sw_edit_reset){
                            stopwatchState = STOPWATCH_STATE_RESET;
                        }
                        else if(pressedKey_id == sw_ok_start){
                            stopwatchState = STOPWATCH_STATE_RUN;
                        }
                        break;
                }
            }   
            break;     
    }
    // USART_ReceiveBufferAsync(&Rx);
}


static void lcdCBF(){
    lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
}

static void setCursorBlink(uint8_t cursor_state){
    lcd_blinkCursorAsync(cursor_state,NULL);
}
static void incCursor(){
    i_cursor++;
    if(i_cursor == 32){
        i_cursor = 0;
    }
    // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
}
static void decCursor(){
    if(i_cursor == 0){
        i_cursor = 32;
    }
    i_cursor--;
    // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
}

static uint8_t numToAscii(uint8_t num){
    return num + 48;
}

