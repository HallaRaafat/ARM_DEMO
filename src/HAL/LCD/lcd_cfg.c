/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/LCD/lcd_cfg.h"
#include "HAL/LCD/lcd.h"
#include "MCAL/GPIO/gpio.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/

#define LCD_DISP_SHIFT_OFF      0
#define LCD_CURSOR_DIR_INC		1
#define LCD_CURSOR_DIR_DEC		0
#define LCD_DISPLAY_ON          1
#define LCD_DISPLAY_OFF         0
#define LCD_CURSOR_ON           1
#define LCD_CURSOR_OFF          0
#define LCD_BLINK_ON            1
#define LCD_BLINK_OFF           0


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/


/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
lcdCfg_t lcdCfg = {
    // .lcdPinsArr = {
    //     [d0] = {
    //         .pin = PIN_15,
    //         .port = PORT_B
    //     },
    //     [d1] = {
    //         .pin = PIN_14,
    //         .port = PORT_B
    //     },
    //     [d2] = {
    //         .pin = PIN_13,
    //         .port = PORT_B
    //     },
    //     [d3] = {
    //         .pin = PIN_12,
    //         .port = PORT_B
    //     },
    //     [d4] = {
    //         .pin = PIN_10,
    //         .port = PORT_B
    //     },
    //     [d5] = {
    //         .pin = PIN_9,
    //         .port = PORT_B
    //     },
    //     [d6] = {
    //         .pin = PIN_8,
    //         .port = PORT_B
    //     },
    //     [d7] = {
    //         .pin = PIN_7,
    //         .port = PORT_B
    //     },
    //     [rs] = {
    //         .pin = PIN_15,
    //         .port = PORT_C
    //     },
    //     [rw] = {
    //         .pin = PIN_14,
    //         .port = PORT_C
    //     },
    //     [e] = {
    //         .pin = PIN_13,
    //         .port = PORT_C
    //     }
    // },
    // .cursor_dir = LCD_CURSOR_DIR_INC,
    // .disp_shift = LCD_DISP_SHIFT_OFF,
    // .display = LCD_DISPLAY_ON,
    // .cursor = LCD_CURSOR_OFF,
    // .blink = LCD_BLINK_OFF
}; 

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/


