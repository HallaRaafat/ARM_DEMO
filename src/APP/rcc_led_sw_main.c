#include "APP/app.h"

#if(APP == RCC_LED_SW_APP)

#include"MCAL/RCC/rcc.h"
#include"HAL/LED/led.h"
#include"HAL/SW/sw.h"

int main(){

    uint64_t ret;
    ret = rcc_enableClk(CLOCK_HSI);
    uint8_t res;
    ret = rcc_getClkStatus(CLOCK_HSI,&res);
    if(res == CLK_READY) {
        ret = rcc_selectSysClk(SYSCLK_HSI);
    }
    ret = rcc_configAHB(AHB_PRE_1);
    ret = rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOA,PERIPH_STATE_ENABLED);
    ret = rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOB,PERIPH_STATE_ENABLED);
    ret = rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOC,PERIPH_STATE_ENABLED);
    ret = rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOD,PERIPH_STATE_ENABLED);
    
    ret = led_init();
    ret = sw_init();
    ret = 500000;
    while(1){

        // ret = led_setState(led_red,LED_STATE_ON);
        // ret = led_setState(led_yellow,LED_STATE_ON);
        // ret = led_setState(led_blue,LED_STATE_ON);
        // ret = led_setState(led_green,LED_STATE_ON);

        // ret = 500000;
        // while(ret--);
        
        // ret = led_setState(led_red,LED_STATE_OFF);
        // ret = led_setState(led_yellow,LED_STATE_OFF);
        // ret = led_setState(led_blue,LED_STATE_OFF);
        // ret = led_setState(led_green,LED_STATE_OFF);


        uint8_t sw_state;
        sw_getState(sw_red,&sw_state);
        if(sw_state == SW_STATE_PRESSED){
            led_setState(led_red,LED_STATE_ON);
        }
        else if(sw_state == SW_STATE_RELEASED) {
            led_setState(led_red,LED_STATE_OFF);
        }

        sw_getState(sw_green,&sw_state);
        if(sw_state == SW_STATE_PRESSED){
            led_setState(led_green,LED_STATE_ON);
        }
        else {
            led_setState(led_green,LED_STATE_OFF);
        }
        sw_getState(sw_blue,&sw_state);
        if(sw_state == SW_STATE_PRESSED){
            led_setState(led_blue,LED_STATE_ON);
        }
        else {
            led_setState(led_blue,LED_STATE_OFF);
        }
        sw_getState(sw_yellow,&sw_state);
        if(sw_state == SW_STATE_PRESSED){
            led_setState(led_yellow,LED_STATE_ON);
        }
        else {
            led_setState(led_yellow,LED_STATE_OFF);
        }
    }
}
#endif