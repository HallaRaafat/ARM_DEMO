/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "MCAL/GPIO/gpio.h"
#include "LIB/bitMasks.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define NUM_GPIO_PORTS  6

#define CAST(port)            ((volatile gpio_t* const)port)

#define MODE_MASK           _2BITS_MASK
#define OTYPE_MASK          _1BITS_MASK
#define PUPD_MASK           _2BITS_MASK

#define OSPEED_MASK         _2BITS_MASK
#define AF_MASK             _4BITS_MASK

// MODER -> bit 2x,2x+1 
// ip 00
// op 01
// af 10
// an 11

// OTYPER -> 0:15
// 0 op pp
// 1 op od

// OSPEEDR -> bit 2x,2x+1 
// 00 low
// 01 medium 
// 10 high 
// 11 very high 

// PUPDR -> bit 2x,2x+1 
// 00 none 
// 01 pu 
// 10 pd
// 11 reserved 

// AFRL for pins 0 ~ 7
// AFHR for pins 8 ~ 15
// 0 : 15 for each pin shifted by 4 * pin num

// IDR 
// ODR 

// BSRR

// LCKR 

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct {
    uint32_t MODER;
    uint32_t OTYPE;
    uint32_t OSPEEDR;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFR[2];
    // uint32_t AFRH;
}gpio_t;

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/

uint8_t gpio_initPin(gpioPin_t* pinCfg) {
    uint8_t errorStatus = RETURN_GPIO_NOT_OK;

    uint32_t setMask, clrMask;
    
    setMask = ((pinCfg->mode & MODE_MASK) << (2*pinCfg->pin));
    clrMask = ~(MODE_MASK << (2*pinCfg->pin));
    CAST(pinCfg->port)->MODER &= clrMask;
    CAST(pinCfg->port)->MODER |= setMask;

    setMask = (((pinCfg->mode >> 2) & OTYPE_MASK) << pinCfg->pin);
    clrMask = ~(OTYPE_MASK << pinCfg->pin);
    CAST(pinCfg->port)->OTYPE &= clrMask; 
    CAST(pinCfg->port)->OTYPE |= setMask;
    
    setMask = (((pinCfg->mode >> 3) & PUPD_MASK) << (2*pinCfg->pin));
    clrMask = ~(PUPD_MASK << (2*pinCfg->pin));
    CAST(pinCfg->port)->PUPDR &= clrMask;
    CAST(pinCfg->port)->PUPDR |= setMask;
    
    setMask = (pinCfg->speed & OSPEED_MASK) << (2*pinCfg->pin);
    clrMask = ~(OSPEED_MASK << (2*pinCfg->pin));
    CAST(pinCfg->port)->OSPEEDR &= clrMask;
    CAST(pinCfg->port)->OSPEEDR |= setMask;

    CAST(pinCfg->port)->AFR[pinCfg->pin / 8] &= ~(AF_MASK << (pinCfg->pin % 8)*4);
    CAST(pinCfg->port)->AFR[pinCfg->pin / 8] |= (pinCfg->af << ((pinCfg->pin % 8)*4));

    errorStatus = RETURN_GPIO_OK;

    return errorStatus;
}
uint8_t gpio_setPinValue(void* port, uint8_t pin, uint8_t pin_value) {
    uint8_t errorStatus = RETURN_GPIO_NOT_OK;

    if(pin_value == PIN_VALUE_HIGH) {
        errorStatus = RETURN_GPIO_OK;
        CAST(port)->BSRR |= (1 << pin);
    }
    else if(pin_value == PIN_VALUE_LOW) {
        errorStatus = RETURN_GPIO_OK;
        CAST(port)->BSRR |= (1 << (pin + 16));
    }

    return errorStatus;
}
uint8_t gpio_getPinValue(void* port, uint8_t pin, uint8_t* pin_value) {
    uint8_t errorStatus = RETURN_GPIO_NOT_OK;
    if(pin_value){
        errorStatus = RETURN_GPIO_OK;
        *pin_value = (((CAST(port)->IDR) >> pin) & 1);
    }    

    return errorStatus;
}
