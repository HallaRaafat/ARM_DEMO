#include "APP/app.h"
#include"HAL/H_SW/H_sw.h"
#include"HAL/LCD/lcd.h"

extern uint64_t stopwatchTime;
extern uint64_t timestamp;

extern uint8_t year;
extern uint8_t mon;
extern uint8_t day;
extern uint8_t hrs;
extern uint8_t min;
extern uint8_t sec;

extern uint8_t pressedKey_id;

uint8_t state = APP_STATE_CLOCK;
uint8_t stopwatchState = STOPWATCH_STATE_RESET;
uint8_t clockState = CLOCK_STATE_DISPLAY;

uint8_t i_cursor = 0;
uint8_t cursor_state = CURSOR_STATE_OFF;

uint8_t clock[32] = "Date 12-04-2024 Clock 00:00:00  ";
uint8_t stopwatch[32] = "  00:00:00.00                   ";

static uint8_t numToAscii(uint8_t num);
static void incCursor();
static void decCursor();
// static void setCursorBlink(uint8_t cursor_state);
static void lcdCBF();
static void curCBF();

void appSM(){

    switch(state){
        case APP_STATE_CLOCK:
            clock[13] = numToAscii(year / 10);            
            clock[14] = numToAscii(year % 10);
            clock[8] = numToAscii(mon / 10);
            clock[9] = numToAscii(mon % 10);
            clock[5] = numToAscii(day / 10);
            clock[6] = numToAscii(day % 10);            
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
                        // setCursorBlink(CURSOR_STATE_OFF);
                        cursor_state = CURSOR_STATE_OFF;
                        if(pressedKey_id == sw_edit_reset){
                            clockState = CLOCK_STATE_EDIT;
                        }
                        break;
                    case CLOCK_STATE_EDIT:
                    {
                        cursor_state = CURSOR_STATE_ON;
                        // setCursorBlink(CURSOR_STATE_ON);
                        // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
                        if(pressedKey_id == sw_ok_start){
                            clockState = CLOCK_STATE_DISPLAY;
                        }
                        else if(pressedKey_id == sw_right) {
                            incCursor();
                        }
                        else if(pressedKey_id == sw_left){
                            decCursor();
                        }
                        else if(pressedKey_id == sw_up){
                            switch (i_cursor){
                                case 5:
                                    day += 10;
                                    break;
                                case 6:
                                    day++;
                                    break;
                                case 8:
                                    mon += 10;
                                    break;
                                case 9:
                                    mon++;
                                    break;
                                case 13:
                                    year += 10;
                                    break;
                                case 14:
                                    year++;
                                    break;
                                case 22:
                                    hrs += 10;
                                    break;
                                case 23:
                                    hrs++;
                                    break;
                                case 25:
                                    min += 10;
                                    break;
                                case 26:
                                    min++;
                                    break;
                                case 28:
                                    sec += 10;
                                    break;
                                case 29:
                                    sec++;
                                    break;
                            }
                        }
                        else if(pressedKey_id == sw_down){
                            switch (i_cursor){
                                case 5:
                                    if(day > 9){
                                        day -= 10;
                                    }
                                    else{
                                        day += 30;
                                    }                                    
                                    break;
                                case 6:
                                    if(day > 0){
                                        day--;
                                    }
                                    else{
                                        day += 9;
                                    }
                                    break;
                                case 8:
                                    if(mon > 9){
                                        mon -= 10;
                                    }
                                    else{
                                        mon += 10;
                                    }
                                    break;
                                case 9:
                                    if(mon > 0){
                                        mon--;
                                    }
                                    else{
                                        mon += 9;
                                    }
                                    break;
                                case 13:
                                    if(year > 9){
                                        year -= 10;
                                    }
                                    else{
                                        year += 90;
                                    }
                                    break;
                                case 14:
                                    if(year > 0){
                                        year --;
                                    }
                                    else{
                                        year += 9;
                                    }
                                    break;
                                case 22:
                                    hrs -= 10;
                                    break;
                                case 23:
                                    hrs--;
                                    break;
                                case 25:
                                    min -= 10;
                                    break;
                                case 26:
                                    min--;
                                    break;
                                case 28:
                                    sec -= 10;
                                    break;
                                case 29:
                                    sec--;
                                    break;
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
            // setCursorBlink(CURSOR_STATE_OFF);
            cursor_state = CURSOR_STATE_OFF;
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
    lcd_setCursorAsync(i_cursor%16,i_cursor/16,curCBF);
}
static void curCBF(){
    lcd_blinkCursorAsync(cursor_state,NULL);
}

// static void setCursorBlink(uint8_t cursor_state){
//     // lcd_blinkCursorAsync(cursor_state,NULL);
// }
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

