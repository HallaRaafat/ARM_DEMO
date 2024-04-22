#include"APP/app.h"

#include"HAL/H_SW/H_sw.h"
#include"MCAL/USART/USART.h"


uint8_t pressedKey_id = _swsNum;
extern uint8_t rxBuffer;
uint8_t recievedID = _swsNum;
//void rxCBF(void);




// void pressedKeyRx(void){
//     User_Request_t Rx;
//     Rx.Ptr_Buffer = &rxBuffer;
//  	Rx.USART_Num = USART_1;
//  	Rx.CallBack = rxCBF;
//     Rx.Length = 1;
//     USART_ReceiveBufferAsync(&Rx);
// }


void rxCBF(){
    // if(pressedKey_id != _swsNum){
    //     pressedKey_id = _swsNum;
    // }
   // static 
    if((rxBuffer >= 0) && (rxBuffer < _swsNum)){
        recievedID = rxBuffer;
      //  pressedKey_id = _swsNum;
    }
    else if((recievedID >= 0) && (recievedID < _swsNum) && (rxBuffer == _swsNum)){
        pressedKey_id = recievedID;
        recievedID = _swsNum;
    }
}
