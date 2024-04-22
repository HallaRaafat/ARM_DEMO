#include"APP/app.h"

#include"HAL/H_SW/H_sw.h"
#include"MCAL/USART/USART.h"


uint8_t pressedKey_id = _swsNum;
uint8_t rxBuffer;

void rxCBF(void);

void pressedKeyRx(void){
    User_Request_t Rx;
    Rx.Ptr_Buffer = &rxBuffer;
 	Rx.USART_Num = USART_1;
 	Rx.CallBack = rxCBF;
    Rx.Length = 1;
    USART_ReceiveBufferAsync(&Rx);
}


void rxCBF(){
    // static uint8_t
    if((rxBuffer >= 0) && (rxBuffer < _swsNum)){
        pressedKey_id = rxBuffer;
    }
}
