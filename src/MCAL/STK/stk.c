/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "MCAL/STK/stk.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define STK_BASE            ((volatile uint32_t*)0xE000E010)

#define CLKSOURCE_MASK      BIT2_MASK
#define ENABLE_MASK         BIT0_MASK
#define COUNTFLAG_MASK      BIT16_MASK

#define CLK                 AHB
#define AHB                 ((uint64_t)16000000)
#define AHB_8               AHB/8

#define CURRENT_VAL_MASK    _24BITS_MASK
#define LOAD_VAL_MASK       _24BITS_MASK

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
    uint32_t CALIB;
}stk_t;


/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
static volatile stk_t* const stk = (stk_t*) STK_BASE;
static volatile handler_t stk_callback = NULL;
static uint8_t mode;

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
void stk_cfgMode(uint8_t stk_mode) {
    mode = stk_mode;
    stk->CTRL |= (1 << 2)|(1 << 1); 
}

uint8_t stk_setCallBck(handler_t handler) {
    uint8_t errorStatus = STK_NOT_OK;
    if(handler){
        stk_callback = handler;
    }
    if(stk_callback){
        errorStatus = STK_OK;
    }
    return errorStatus;
}

void SysTick_Handler(void){
    if(stk_callback){
        stk_callback();
    }
    if(mode){
        stk_stop();
    }
}

uint8_t stk_setTime_mS(uint32_t time_mS) {
    uint8_t errorStatus = STK_NOT_OK;
    if(time_mS <= STK_MAX_TIME_MS){
        uint32_t counts = ((uint32_t)(uint64_t)time_mS*CLK/1000) - 1;
        stk->LOAD &= ~LOAD_VAL_MASK;
        stk->LOAD |= (counts & LOAD_VAL_MASK);
        stk->VAL &= ~CURRENT_VAL_MASK;
        if((stk->LOAD & LOAD_VAL_MASK) == counts){
            errorStatus = STK_OK;
        }
    }
    return errorStatus;
}

uint8_t stk_start() {
    uint8_t errorStatus = STK_NOT_OK;
    stk->CTRL |= (ENABLE_MASK);
    if(stk->CTRL & ENABLE_MASK){
        errorStatus = STK_OK;
    }
    return errorStatus;
}

uint8_t stk_stop() {
    uint8_t errorStatus = STK_NOT_OK;
    stk->CTRL &= ~(ENABLE_MASK);
    if(!(stk->CTRL & ENABLE_MASK)){
        errorStatus = STK_OK;
    }
    return errorStatus;
}

uint8_t stk_isExpired() {
    return (COUNTFLAG_MASK & stk->CTRL); 
}
