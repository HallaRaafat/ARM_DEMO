/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "MCAL/NVIC/nvic.h"
#include "LIB/bitMasks.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define IMPLEMENTED_BITS        4
#define NVIC_BASE               ((volatile uint32_t*)0xE000E100)
#define NVIC_STIR_ADDRESS       *((volatile uint32_t*)0xE000EF00)
#define SCB_AIRCR_ADDRESS       *((volatile uint32_t*)0xE000ED0C)
#define PRIGROUP_OFFSET         8
#define PRIGROUP_MASK           (_3BITS_MASK << PRIGROUP_OFFSET)
#define IP_MASK                 _8BITS_MASK

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct {
    uint32_t ISER[8];
    uint32_t ICER[8];
    uint32_t ISPR[8];
    uint32_t ICPR[8];
    uint32_t IABR[8];
    uint32_t IPR[60];
}nvic_t;

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
static volatile nvic_t* const nvic = (nvic_t*)NVIC_BASE;

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
void nvic_cfgIntProirity(uint8_t irq,uint8_t preempt_priority,uint8_t subgp_priority) {
    nvic->IPR[irq/4] &= ~(IP_MASK << ((irq % 4) * 8));
    nvic->IPR[irq/4] |= (((uint8_t)preempt_priority + subgp_priority) << ((irq % 4) * 8));  
}
//uint8_t nvic_getIntProirity(uint8_t irq,uint8_t* preempt_priority,uint8_t* subgp_priority);
uint8_t nvic_enableInt(uint8_t irq) {
    uint8_t errorStatus = RETURN_NOT_OK;
    nvic->ISER[irq / 32] |= (1 << (irq % 32));
    if(nvic->ISER[irq / 32] & (1 << (irq % 32))){
        errorStatus = RETURN_OK;
    }
    return errorStatus;
}
uint8_t nvic_disableInt(uint8_t irq) {
    uint8_t errorStatus = RETURN_NOT_OK;
    nvic->ICER[irq / 32] |= (1 << (irq % 32));
    if(!(nvic->ICER[irq / 32] & (1 << (irq % 32)))){
        errorStatus = RETURN_OK;
    }
    return errorStatus;
}
uint8_t nvic_setPending(uint8_t irq) {
    uint8_t errorStatus = RETURN_NOT_OK;
    nvic->ISPR[irq / 32] |= (1 << (irq % 32));
    if(nvic->ISPR[irq / 32] & (1 << (irq % 32))){
        errorStatus = RETURN_OK;
    }
    return errorStatus;
}
uint8_t nvic_clrPending(uint8_t irq) {
    uint8_t errorStatus = RETURN_NOT_OK;
    nvic->ICPR[irq / 32] |= (1 << (irq % 32));
    if(!(nvic->ICPR[irq / 32] & (1 << (irq % 32)))){
        errorStatus = RETURN_OK;
    }
    return errorStatus;
}
void nvic_getIntStatus(uint8_t irq, uint8_t* int_status) {
    *int_status = 1 && (nvic->IABR[irq / 32] | (1 << (irq % 32)));   
}
uint8_t nvic_cfgSubgpBits(uint8_t subgp_bits) {
    uint8_t errorStatus = RETURN_NOT_OK;
    uint32_t clrMask = ~PRIGROUP_MASK;
    uint32_t setMask = ((subgp_bits << PRIGROUP_OFFSET) & PRIGROUP_MASK);
    SCB_AIRCR_ADDRESS &= clrMask;
    SCB_AIRCR_ADDRESS |= setMask;
    if((SCB_AIRCR_ADDRESS & PRIGROUP_MASK)== setMask){

    }
    return errorStatus;
}
void nvic_generateSwInt(uint8_t irq) {
    NVIC_STIR_ADDRESS |= irq;
}
