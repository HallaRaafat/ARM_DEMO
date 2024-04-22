#ifndef SYSTCK_H_
#define SYSTCK_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include <stdint.h>
#include "LIB/bitMasks.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define STK_OK      0
#define STK_NOT_OK  1

#define STK_STATE_EXPIRED           BIT16_MASK
#define STK_STATE_NOT_EXPIRED       0

#define STK_MODE_ONE_SHOT           1
#define STK_MODE_PERIODIC           0

#define STK_MAX_TIME_MS             1000

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef void (*handler_t)(void);


/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/
void stk_cfgMode(uint8_t stk_mode);
uint8_t stk_setCallBck(handler_t handler);
uint8_t stk_setTime_mS(uint32_t time_mS);
uint8_t stk_start();
uint8_t stk_stop();
uint8_t stk_isExpired();

#endif /* SYSTCK_H_ */