#include"SCHED/sched.h"

#include"HAL/H_SW/H_sw.h"
#include"HAL/LCD/lcd.h"

#include"MCAL/RCC/rcc.h"
#include"MCAL/GPIO/gpio.h"
#include"MCAL/NVIC/nvic.h"
#include"MCAL/USART/USART.h"

int main(){

    rcc_enableClk(CLOCK_HSI);
    uint8_t res;
    rcc_getClkStatus(CLOCK_HSI,&res);
    while(res != CLK_READY);
    rcc_selectSysClk(SYSCLK_HSI);
    // rcc_configAHB(AHB_PRE_2);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOA,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOB,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOC,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOD,PERIPH_STATE_ENABLED);
    
    rcc_controlAPB2Peripheral(APB2_PERIPH_USART1,PERIPH_STATE_ENABLED);
    
	gpioPin_t UART_PINS[2]={
			//tx
			[0]= {
                .mode = MODE_AF_PP,
                .port = PORT_A,
                .pin = PIN_9,
                .speed = SPEED_HIGH,
                .af = AF_USART_1_2
            },
			//rx
            [1]= {
                .mode= MODE_AF_PP,
                .port=PORT_A,
                .pin=PIN_10,
                .speed=SPEED_HIGH,
                .af = AF_USART_1_2
            }
	};
    gpio_initPin(&UART_PINS[0]);
	gpio_initPin(&UART_PINS[1]);

    nvic_enableInt(IRQ_USART1);

	USART_Init();
	
    hsw_init();
    lcd_initAsync();

    sched_init();
    sched_start();
}