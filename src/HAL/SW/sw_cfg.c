/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/SW/sw_cfg.h"
#include "HAL/SW/sw.h"
#include "MCAL/GPIO/gpio.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
const swCfg_t switches[_swsNum] = {
    [sw_up] = {
        .port = PORT_A,
        .pin = PIN_4,
        .sw_connection = SW_CONNECTION_PULLUP
    },
    [sw_down] = {
        .port = PORT_A,
        .pin = PIN_5,
        .sw_connection = SW_CONNECTION_PULLUP
    },
    [sw_right] = {
        .port = PORT_A,
        .pin = PIN_3,
        .sw_connection = SW_CONNECTION_PULLUP
    },
    [sw_left] = {
        .port = PORT_A,
        .pin = PIN_6,
        .sw_connection = SW_CONNECTION_PULLUP
    },
    [sw_edit_reset] = {
        .port = PORT_A,
        .pin = PIN_2,
        .sw_connection = SW_CONNECTION_PULLUP
    },
    [sw_ok_start] = {
        .port = PORT_A,
        .pin = PIN_1,
        .sw_connection = SW_CONNECTION_PULLUP
    },
    [sw_mode] = {
        .port = PORT_A,
        .pin = PIN_0,
        .sw_connection = SW_CONNECTION_PULLUP
    }
};

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/


