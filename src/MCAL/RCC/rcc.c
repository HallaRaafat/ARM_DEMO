/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "MCAL/RCC/rcc.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define RCC_BASE    ((volatile uint32_t*)0x40023800)

#define MCO1_PRE_SHIFT      27
#define MCO2_PRE_SHIFT      24
#define MCO1_SRC_SHIFT      21
#define MCO2_SRC_SHIFT      30  

#define MCO_PRE_CLEAR_MASK      _3BITS_MASK
#define MCO_SRC_CLEAR_MASK      _2BITS_MASK

#define SYSCLK_MASK         _2BITS_MASK
#define SYSCLK_GET_SHIFT    2
#define SYSCLK_SET_SHIFT    0

#define CLK_RDY_SHIFT       1

#define PLL_SRC_MASK        BIT22_MASK
#define PLL_N_MASK          _9BITS_MASK
#define PLL_M_MASK          _6BITS_MASK
#define PLL_P_MASK          _2BITS_MASK
#define PLL_Q_MASK          _4BITS_MASK

#define PLL_N_SHIFT         6
#define PLL_M_SHIFT         0
#define PLL_P_SHIFT         16
#define PLL_Q_SHIFT         24

#define APB_PRE_MASK        _3BITS_MASK

#define APB1_PRE_SHIFT      10
#define APB2_PRE_SHIFT      13

#define AHB_PRE_MASK        _4BITS_MASK

#define AHB_PRE_SHIFT       4


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct {
    uint32_t CR;        //control
    uint32_t PLLCFGR;    //PLL config 
    uint32_t CFGR;       //config
    uint32_t CIR;        //control interrupt flag
    uint32_t AHB1RSTR;   //AHB1 peripheral reset 
    uint32_t AHB2RSTR;   //AHB2 peripheral reset
    uint32_t reserved;
    uint32_t reserved1;    
    uint32_t APB1RSTR;   //APB1 peripheral reset 
    uint32_t APB2RSTR;  //APB2 peripheral reset
    uint32_t reserved2;
    uint32_t reserved3;    
    uint32_t AHB1ENR;    //AHB1 peripheral clock enable 
    uint32_t AHB2ENR;    //AHB2 peripheral clock enable
    uint32_t reserved4;
    uint32_t reserved5;
    uint32_t APB1ENR;    //APB1 peripheral clock enable
    uint32_t APB2ENR;    //APB2 peripheral clock enable
    uint32_t reserved6;
    uint32_t reserved7;
    uint32_t AHB1LPENR;  //AHB1 peripheral clock enable in low power mode
    uint32_t AHB2LPENR;  //AHB2 peripheral clock enable in low power mode
    uint32_t reserved8;
    uint32_t reserved9;
    uint32_t APB1LPENR;  //APB1 peripheral clock enable in low power mode
    uint32_t APB2LPENR;  //APB2 peripheral clock enable in low power mode
    uint32_t reserved10;
    uint32_t reserved11;
    uint32_t BDCR;      //Backup domain control 
    uint32_t CSR;        //clock control & status
    uint32_t reserved12;
    uint32_t reserved13;
    uint32_t SSCGR;      //spread spectrum clock generation
    uint32_t PLLI2SCFGR;     //PLLI2S configuration
    uint32_t reserved14;
    uint32_t DCKCFGR;    //Dedicated Clocks Configuration
}rcc_t;

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
static volatile rcc_t* const rcc = (rcc_t*) RCC_BASE;

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
uint8_t rcc_selectSysClk(uint8_t sysClk) {
    uint8_t errorStatus = RETURN_NOT_OK;
    
    uint32_t clear_mask = ~(SYSCLK_MASK << SYSCLK_SET_SHIFT);
    uint32_t set_mask = sysClk << SYSCLK_SET_SHIFT;
    
    rcc->CFGR &= clear_mask;
    rcc->CFGR |= set_mask;

    if((rcc->CFGR & set_mask) == set_mask) {
        errorStatus = RETURN_OK;
    }

    return errorStatus;
}
uint8_t rcc_getSysClk(uint8_t *sysClk) {
    uint8_t errorStatus = RETURN_NOT_OK;
    if(sysClk) {
        errorStatus = RETURN_OK;
        *sysClk = ((rcc->CFGR >> SYSCLK_GET_SHIFT) & SYSCLK_MASK);
    }
    return errorStatus;
}

uint8_t rcc_getClkStatus(uint8_t clock, uint8_t* clockStatus) {
    uint8_t errorStatus = RETURN_NOT_OK;
    if(clockStatus) {
        errorStatus = RETURN_OK;
        *clockStatus = (((clock<<CLK_RDY_SHIFT) & rcc->CR) && CLK_READY);
    }
    return errorStatus; 
}

uint8_t rcc_enableClk(uint8_t clock) {
    uint8_t errorStatus = RETURN_NOT_OK;
    rcc->CR |= (1<<16);
    if(rcc->CR & clock) {
        errorStatus = RETURN_OK;
    }
    return errorStatus;
}
uint8_t rcc_disableClk(uint8_t clock) {
    uint8_t errorStatus = RETURN_NOT_OK;
    rcc->CR &= ~clock;
    if(!(rcc->CR & clock)) {
        errorStatus = RETURN_OK;
    }
    return errorStatus;
}

uint8_t rcc_configMCO1(uint8_t MCO1_Src, uint8_t MCO_Pre) {
    uint8_t errorStatus = RETURN_NOT_OK;
    
    uint32_t clear_mask = ~((MCO_SRC_CLEAR_MASK << MCO1_SRC_SHIFT) | (MCO_PRE_CLEAR_MASK << MCO1_PRE_SHIFT));
    uint32_t set_mask = MCO1_Src | (MCO_Pre << MCO1_PRE_SHIFT);
    
    rcc->CFGR &= clear_mask;
    rcc->CFGR |= set_mask;

    if((rcc->CFGR & set_mask) == set_mask) {
        errorStatus = RETURN_OK;
    }

    return errorStatus;
}
uint8_t rcc_configMCO2(uint8_t MCO2_Src, uint8_t MCO_Pre) {
    uint8_t errorStatus = RETURN_NOT_OK;
    
    uint32_t clear_mask = ~((MCO_SRC_CLEAR_MASK << MCO2_SRC_SHIFT) | (MCO_PRE_CLEAR_MASK << MCO1_PRE_SHIFT));
    uint32_t set_mask = MCO2_Src | (MCO_Pre << MCO2_PRE_SHIFT);
    
    rcc->CFGR &= clear_mask;
    rcc->CFGR |= set_mask;

    if((rcc->CFGR & set_mask) == set_mask) {
        errorStatus = RETURN_OK;
    }

    return errorStatus;
}


uint8_t rcc_configPLL(uint8_t PLL_src, uint16_t PLL_N, uint8_t PLL_M, uint8_t PLL_P, uint8_t PLL_Q) {
    uint8_t errorStatus = RETURN_NOT_OK;
    if(!(rcc->CR & (CLOCK_PLL | CLOCK_PLLI2S))) {    //PLL disabled
        uint32_t clearMask = ~(PLL_SRC_MASK|(PLL_N_MASK<<PLL_N_SHIFT)|(PLL_M_MASK<<PLL_M_SHIFT)|(PLL_P_MASK<<PLL_P_SHIFT)|(PLL_Q_MASK<<PLL_Q_SHIFT)); 
        uint32_t setMask = (PLL_src | (PLL_N << PLL_N_SHIFT) | PLL_M | PLL_P);
        rcc->PLLCFGR &= clearMask;
        rcc->PLLCFGR |= setMask;  
        if((rcc->PLLCFGR & setMask) == setMask) {    //check cfg is written successfully 
            errorStatus = RETURN_OK;
        }
    }
    return errorStatus;
}

uint8_t rcc_configAPB1(uint8_t APB_pre) {
    uint8_t errorStatus = RETURN_NOT_OK;
    uint32_t clearMask = ~(APB_PRE_MASK << APB1_PRE_SHIFT);
    uint32_t setMask = (APB_pre << APB1_PRE_SHIFT);
    rcc->CFGR &= clearMask;
    rcc->CFGR |= setMask;

    if((rcc->CFGR & setMask) == setMask) {    //check cfg is written successfully 
        errorStatus = RETURN_OK;
    }

    return errorStatus;
}
uint8_t rcc_configAPB2(uint8_t APB_pre) {
    uint8_t errorStatus = RETURN_NOT_OK;
    uint32_t clearMask = ~(APB_PRE_MASK << APB2_PRE_SHIFT);
    uint32_t setMask = (APB_pre << APB2_PRE_SHIFT);
    rcc->CFGR &= clearMask;
    rcc->CFGR |= setMask;

    if((rcc->CFGR & setMask) == setMask) {    //check cfg is written successfully 
        errorStatus = RETURN_OK;
    }

    return errorStatus;
}

uint8_t rcc_configAHB(uint8_t AHB_pre) {
    uint8_t errorStatus = RETURN_NOT_OK;
    uint32_t clearMask = ~(AHB_PRE_MASK << AHB_PRE_SHIFT);
    
    rcc->CFGR &= clearMask;
    rcc->CFGR |= AHB_pre;

    if((rcc->CFGR & AHB_pre) == AHB_pre) {    //check cfg is written successfully 
        errorStatus = RETURN_OK;
    }

    return errorStatus;
}

uint8_t rcc_controlAPB1Peripheral(uint32_t APB1_periph, uint8_t periph_state) {
    uint8_t errorStatus = RETURN_NOT_OK;

    if(periph_state == PERIPH_STATE_ENABLED) {
        rcc->APB1ENR |= APB1_periph;
        if((rcc->APB1ENR & APB1_periph) == APB1_periph) {    //check cfg is written successfully 
            errorStatus = RETURN_OK;
        }
    }
    else if(periph_state == PERIPH_STATE_DISABLED) {
        rcc->APB1ENR &= ~APB1_periph;
        if(!(rcc->APB1ENR & APB1_periph)) {
            errorStatus = RETURN_OK;
        }
    }  
    return errorStatus;
}
uint8_t rcc_controlAPB2Peripheral(uint32_t APB2_periph, uint8_t periph_state) {
    uint8_t errorStatus = RETURN_NOT_OK;

    if(periph_state == PERIPH_STATE_ENABLED) {
        rcc->APB2ENR |= APB2_periph;

        if((rcc->APB2ENR & APB2_periph) == APB2_periph) {    //check cfg is written successfully 
            errorStatus = RETURN_OK;
        }
    }
    else if(periph_state == PERIPH_STATE_DISABLED) {
        rcc->APB2ENR &= ~APB2_periph;
        if(!(rcc->APB2ENR & APB2_periph)) {
            errorStatus = RETURN_OK;
        }
    } 
    return errorStatus;
}
uint8_t rcc_controlAHB1Peripheral(uint32_t AHB1_periph, uint8_t periph_state) {
    uint8_t errorStatus = RETURN_NOT_OK;

    if(periph_state == PERIPH_STATE_ENABLED) {
        rcc->AHB1ENR |= AHB1_periph;

        if((rcc->AHB1ENR & AHB1_periph) == AHB1_periph) {    //check cfg is written successfully 
            errorStatus = RETURN_OK;
        }
    }
    else if(periph_state == PERIPH_STATE_DISABLED) {
        rcc->AHB1ENR &= ~AHB1_periph;
        if(!(rcc->AHB1ENR & AHB1_periph)) {
            errorStatus = RETURN_OK;
        }
    }  
    return errorStatus;
}
uint8_t rcc_controlAHB2Peripheral(uint32_t AHB2_periph, uint8_t periph_state) {
    uint8_t errorStatus = RETURN_NOT_OK;

    if(periph_state == PERIPH_STATE_ENABLED) {
        rcc->AHB2ENR |= AHB2_periph;

        if((rcc->AHB2ENR & AHB2_periph) == AHB2_periph) {    //check cfg is written successfully 
            errorStatus = RETURN_OK;
        }
    }
    else if(periph_state == PERIPH_STATE_DISABLED) {
        rcc->AHB2ENR &= ~AHB2_periph;
        if(!(rcc->AHB2ENR & AHB2_periph)) {
            errorStatus = RETURN_OK;
        }
    }  

    return errorStatus;
}


//uint8_t rcc_configPLLI2S(uint16_t PLLI2S_N, uint8_t PLLI2S_R);



