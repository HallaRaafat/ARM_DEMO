#include"APP/app.h"

#include"HAL/H_SW/H_sw.h"
#include"MCAL/USART/USART.h"

extern uint8_t pressedKey_id;
void txCBF(void);

/* work at released */
void pressedKeyTx(){
    uint8_t pressedKey_sendId = _swsNum;
    uint8_t SW_state = SW_STATE_RELEASED;
    static uint8_t prev_pressed = _swsNum;

    User_Request_t Tx;
    Tx.Ptr_Buffer = &pressedKey_sendId;
    Tx.USART_Num = USART_1;
    Tx.CallBack = txCBF;
    Tx.Length = 1;

    uint8_t pressed_flag = 0;

    for(uint8_t i = 0; i < _swsNum; i++){
        hsw_getState(i,&SW_state);
        if(SW_state == SW_STATE_PRESSED){
            pressed_flag = 1;
            prev_pressed = i;
        }
    }
    if(pressed_flag){
        pressedKey_sendId = prev_pressed;
      //  pressedKey_id = _swsNum;
    }
    else { 
        pressedKey_sendId = _swsNum /*+ '0'*/;            
    }
    USART_SendBufferAsync(&Tx);
}

void txCBF(void){

}