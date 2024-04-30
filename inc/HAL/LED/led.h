#ifndef LED_H_
#define LED_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include <stdint.h>
#include "HAL/LED/led_cfg.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define LED_STATE_ON    (uint8_t)0x01
#define LED_STATE_OFF   (uint8_t)0x00

#define LED_CONNECTION_FORWARD  (uint8_t)0x00
#define LED_CONNECTION_REVERSE  (uint8_t)0x01

#define RETURN_LED_OK       (uint8_t)0x00
#define RETURN_LED_NOT_OK   (uint8_t)0x01

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct {
    uint8_t pin;
    uint8_t led_connection;
    uint8_t led_state;
    void* port;
}ledCfg_t;

/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/
uint8_t led_init(void);
uint8_t led_setState(uint8_t led, uint8_t led_state);

#endif /* LED_H_ */