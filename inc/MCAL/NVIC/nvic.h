#ifndef NVIC_H_
#define NVIC_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include <stdint.h>
#include "LIB/STM32F401CC_interrupts.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define RETURN_OK       0
#define RETURN_NOT_OK   1

#define INT_STATUS_ACTIVE       1
#define INT_STATUS_INACTIVE     0

#define SUBGP_BITS_0            0x00
#define SUBGP_BITS_1            0x04
#define SUBGP_BITS_2            0x05
#define SUBGP_BITS_3            0x06
#define SUBGP_BITS_4            0x07


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/



/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/
void nvic_cfgIntProirity(uint8_t irq,uint8_t preempt_priority,uint8_t subgp_priority);
//uint8_t nvic_getIntProirity(uint8_t irq,uint8_t* preempt_priority,uint8_t* subgp_priority);
uint8_t nvic_enableInt(uint8_t irq);
uint8_t nvic_disableInt(uint8_t irq);
uint8_t nvic_setPending(uint8_t irq);
uint8_t nvic_clrPending(uint8_t irq);
void nvic_getIntStatus(uint8_t irq, uint8_t* int_status);
uint8_t nvic_cfgSubgpBits(uint8_t subgp_bits);
void nvic_generateSwInt(uint8_t irq);


#endif /* NVIC_H_ */