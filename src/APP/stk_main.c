#include "APP/app.h"

#if(APP == STK_APP)

#include"MCAL/RCC/rcc.h"
#include"MCAL/STK/stk.h"
#include"HAL/LED/led.h"

void stk_handler(void);

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
    
    led_init();

    stk_cfgMode(STK_MODE_PERIODIC);
    stk_setCallBck(stk_handler);
    stk_setTime_mS(1000);
    stk_start();

    while(1){
        if(stk_isExpired()){
            stk_handler();
        }
    }
}

void stk_handler(void){
    static uint32_t status = LED_STATE_ON ;
	status ^= (LED_STATE_ON | LED_STATE_OFF);
	led_setState(led_blue, status);
}

#endif