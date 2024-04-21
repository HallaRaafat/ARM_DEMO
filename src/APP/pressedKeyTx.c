#include"APP/app.h"

#include"HAL/H_SW/H_sw.h"
#include"MCAL/USART/USART.h"

extern uint8_t pressedKey_id;

uint8_t currentPressed_flag = 0;
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
    if(pressed_flag ||(prev_pressed == _swsNum)){
        // USART_SendBufferAsync(&Tx);
        // pressedKey_id = pressedKey_sendId;
        pressedKey_sendId = _swsNum;
        pressedKey_id = _swsNum;
    }
    else if((!pressed_flag) && (prev_pressed != _swsNum)) { /* currently sw released but previously was pressed */
        hsw_getState(prev_pressed,&SW_state);
        if(SW_state == SW_STATE_RELEASED){
            pressedKey_sendId = prev_pressed /*+ '0'*/;
            // pressedKey_id = prev_pressed;
            USART_SendBufferAsync(&Tx);
            prev_pressed = _swsNum;
        }
    } 
}

void txCBF(void){

}