#ifndef LCD_H_
#define LCD_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/LCD/lcd_cfg.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define CURSOR_STATE_ON         1
#define CURSOR_STATE_OFF        0


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef enum {
    lcdState_off,
    lcdState_init,
    lcdState_operational
}lcdState_t;

typedef enum {
    lcdReqState_noReq,
    lcdReqState_inProgress,
    lcdReqState_done
}lcdReqState_t;

typedef void (*callback_t)(void);

/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/
void lcd_initAsync();

lcdState_t lcd_getLCDState();
lcdReqState_t lcd_getReqState();

void lcd_writeStringXYAsync(uint8_t* dataStringPtr, uint8_t len, uint8_t x, uint8_t y, callback_t callback_writeXY);
void lcd_writeStringAsync(uint8_t* dataStringPtr, uint8_t len, callback_t callback_write);

void lcd_clearScreenAsync(callback_t callback_clear);
void lcd_setCursorAsync(uint8_t x, uint8_t y, callback_t callback_cursor);

void lcd_blinkCursorAsync(uint8_t cursor_state, callback_t callback_blinkCursor);

#endif /* LCD_H_ */