#include"APP/app.h"

#if(APP == HSW_TASK_APP)

#include "SCHED/sched.h"

#include"MCAL/RCC/rcc.h"

#include"HAL/LED/led.h"
#include"HAL/H_SW/H_sw.h"

/*****************************************************************************/
/*                              Module Task                                  */
/*****************************************************************************/
void App_task(){
    uint8_t sw_state = SW_STATE_RELEASED;
    hsw_getState(sw_blue,&sw_state);
    if(sw_state == SW_STATE_PRESSED){
        led_setState(led_blue,LED_STATE_ON);
    }
    else if(sw_state == SW_STATE_RELEASED){
        led_setState(led_blue,LED_STATE_OFF);
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
    
    led_init();
    hsw_init();

    sched_init();
    sched_start();

}



#endif