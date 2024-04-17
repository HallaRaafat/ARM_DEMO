#include "APP/app.h"

#if(APP == NVIC_APP)

#include "MCAL/RCC/rcc.h"
#include "MCAL/NVIC/nvic.h"
#include "HAL/LED/led.h"


void EXTI0_IRQHandler(void)
{
  led_setState(led_red, LED_STATE_OFF);
  led_setState(led_yellow, LED_STATE_OFF);

}

void EXTI1_IRQHandler(void)
{
  led_setState(led_red, LED_STATE_ON);
  nvic_generateSwInt(IRQ_EXT0_INTERRRUPT);
  led_setState(led_yellow, LED_STATE_ON);
}


int main() {
    
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
    
    
    led_init();

    nvic_enableInt(IRQ_EXT0_INTERRRUPT);
    nvic_enableInt(IRQ_EXT1_INTERRRUPT);

    /*Testing Nesting Priorities*/
    nvic_cfgIntProirity(IRQ_EXT0_INTERRRUPT,2,0);
    nvic_cfgIntProirity(IRQ_EXT1_INTERRRUPT,3,0);

    nvic_setPending(IRQ_EXT0_INTERRRUPT);

    nvic_generateSwInt(IRQ_EXT1_INTERRRUPT);

    while(1){

    }
}

#endif


  
  

