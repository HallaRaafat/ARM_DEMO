#include"APP/app.h"

#if(APP == LCD_APP)

#include "SCHED/sched.h"

#include"MCAL/RCC/rcc.h"

#include"HAL/LCD/lcd.h"

uint8_t flag = 0;

void write_done(void);
void clear_done(void);
void cursor_done(void);
void writeXY_done(void);

void write_done(void){
    flag = 1;
    uint8_t* name = "ya";
    lcd_writeStringXYAsync(name,2,2,1,(callback_t)writeXY_done);
}
void clear_done(void){
    lcd_setCursorAsync(5,0,(callback_t)cursor_done);
}
void cursor_done(void){
    uint8_t* name = "yaSS";
    lcd_writeStringAsync(name,4,(callback_t)write_done);
}
void writeXY_done(void){
    lcd_clearScreenAsync((callback_t)clear_done);    
}

/*****************************************************************************/
/*                              Module Task                                  */
/*****************************************************************************/

void App_task(){
    uint8_t lcdState = lcd_getLCDState();
    if(lcdState == lcdState_off){
        lcd_initAsync();
    }
    else if(lcdState == lcdState_operational){
        uint8_t lcdReqState = lcd_getReqState();
        if(lcdReqState != lcdReqState_inProgress){
            if(!flag){
                write_done();
            }
        }        
    }
}

/*****************************************************************************/
/*                                  Main                                     */
/*****************************************************************************/
int main() {
    
    rcc_enableClk(CLOCK_HSI);
    uint8_t res;
    rcc_getClkStatus(CLOCK_HSI,&res);
    if(res == CLK_READY) {
        rcc_selectSysClk(SYSCLK_HSI);
    }
    rcc_configAHB(AHB_PRE_2);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOA,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOB,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOC,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOD,PERIPH_STATE_ENABLED);
    
    sched_init();
    sched_start();

}

#endif