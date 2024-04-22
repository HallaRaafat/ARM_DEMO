#ifndef H_SW_H_
#define H_SW_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/SW/sw_cfg.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define SW_CONNECTION_PULLUP        0x01
#define SW_CONNECTION_PULLDOWN      0x00

#define SW_STATE_PRESSED            0x01
#define SW_STATE_RELEASED           0x00

#define RETURN_SW_OK       0x00
#define RETURN_SW_NOT_OK   0x01

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct {
    uint8_t pin;
    uint8_t sw_connection;
    void* port;
}swCfg_t;

/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/

uint8_t hsw_init(void);
uint8_t hsw_getState(uint8_t sw, uint8_t* sw_state);


#endif /* H_SW_H_ */