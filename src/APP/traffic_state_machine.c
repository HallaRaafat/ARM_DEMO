#include"APP/app.h"

#if(APP == TRAFFIC_APP)

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include"MCAL/RCC/rcc.h"
#include"HAL/LED/led.h"
#include "SCHED/sched.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define TRAFFIC_PERIODICITY_SEC     2

#define RED_LIGHT_TIME_SEC          20
#define YELLOW_LIGHT_TIME_SEC       2
#define GREEN_LIGHT_TIME_SEC        6

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef enum {
    traffic_state_red,
    traffic_state_yellow,
    traffic_state_green
}traffic_state_t;

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
/* traffic light task */
/*        2 S         */
void App_task(){
    static traffic_state_t state = traffic_state_red;
    static traffic_state_t prev_state = traffic_state_red;
    static uint32_t seconds = 0;

    seconds += TRAFFIC_PERIODICITY_SEC;

    switch (state) {
        case traffic_state_red:
            led_setState(led_red,LED_STATE_ON);
            led_setState(led_yellow,LED_STATE_OFF);
            led_setState(led_green,LED_STATE_OFF);
            if(seconds == RED_LIGHT_TIME_SEC) {
                state = traffic_state_yellow;
                prev_state = traffic_state_red;
                seconds = 0;
            }
            break;
        case traffic_state_yellow:
            led_setState(led_red,LED_STATE_OFF);
            led_setState(led_yellow,LED_STATE_ON);
            led_setState(led_green,LED_STATE_OFF);
            if(seconds == YELLOW_LIGHT_TIME_SEC) {
                if(prev_state == traffic_state_red) {
                    state = traffic_state_green;
                }
                else if(prev_state == traffic_state_green) {
                    state = traffic_state_red;
                }
                prev_state = traffic_state_yellow;
                seconds = 0;
            }
            break;
        case traffic_state_green:
            led_setState(led_red,LED_STATE_OFF);
            led_setState(led_yellow,LED_STATE_OFF);
            led_setState(led_green,LED_STATE_ON);
            if(seconds == GREEN_LIGHT_TIME_SEC) {
                state = traffic_state_yellow;
                prev_state = traffic_state_green;
                seconds = 0;
            }
            break;
    }
    
}

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

    sched_init();
    sched_start();

}



#endif