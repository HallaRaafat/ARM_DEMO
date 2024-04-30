#include"MCAL/RCC/rcc.h"
#include"MCAL/NVIC/nvic.h"
#include"MCAL/USART/USART.h"
#include"MCAL/GPIO/gpio.h"
#include"HAL/LED/led.h"
#include"HAL/H_SW/H_sw.h"
#include"SCHED/sched.h"
#include<stdint.h>
#include"APP/app.h"

User_Request_t Tx;
User_Request_t RX;

uint8_t flag = 0;

uint8_t Arr=0x01;
uint8_t Rx_Arr[6]={0};

extern ledCfg_t leds[_ledsNum];
// extern swCfg_t switches [_swsNum];

void rxcbf1(){
    Arr = 0xFF;
    if(Rx_Arr[0] == FRAME_START){
        switch (Rx_Arr[1]){
            case GPIO_MOD:
                switch(Rx_Arr[2]){
                    case GPIO_SET:
                        Arr = gpio_setPinValue(0x40020000+(Rx_Arr[4]*0x400),Rx_Arr[3],Rx_Arr[5]);
                        break;
                    case GPIO_GET:
                        gpio_getPinValue(0x40020000+(Rx_Arr[4]*0x400),Rx_Arr[3],&Arr);
                        break;
                }
                break;
            case LED_MOD:
                switch(Rx_Arr[2]){
                    case LED_SET:
                        led_setState(Rx_Arr[3],Rx_Arr[4]);
                        gpio_getPinValue(leds[Rx_Arr[3]].port,leds[Rx_Arr[3]].pin,&Arr);
                        Arr ^= leds[Rx_Arr[3]].led_connection;                        
                        break;
                }
                break;
            case SW_MOD:
                switch(Rx_Arr[2]){
                    case SW_GET:
                        hsw_getState(Rx_Arr[3],&Arr);                       
                        break;
                }
                break;
        }
    }
    USART_SendBufferAsync(&Tx);    
}
void txcbf1(){
    USART_ReceiveBufferAsync(&RX);
}


int main(){
    rcc_enableClk(CLOCK_HSI);
    uint8_t res;
    rcc_getClkStatus(CLOCK_HSI,&res);
    if(res == CLK_READY) {
        rcc_selectSysClk(SYSCLK_HSI);
    }
    // rcc_configAHB(AHB_PRE_1);
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
	
	Tx.Ptr_Buffer=&Arr;
	Tx.USART_Num=USART_1;
	Tx.CallBack=txcbf1;
    Tx.Length=1;
    
    RX.Ptr_Buffer=Rx_Arr;
 	RX.USART_Num=USART_1;
 	RX.CallBack=rxcbf1;
    RX.Length=5;

    led_init();
    hsw_init();
	USART_Init();
    USART_ReceiveBufferAsync(&RX);
	sched_init();
    sched_start();   
}