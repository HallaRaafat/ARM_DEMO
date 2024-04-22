#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include <stdint.h>

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define LCD_MODE    LCD_MODE_8_BIT

#define LCD_MODE_4_BIT       0
#define LCD_MODE_8_BIT       1

#define LCD_NUM_LINES   LCD_TWO_LINE

#define LCD_ONE_LINE    0
#define LCD_TWO_LINE    1

#define LCD_FONT    LCD_FONT_5X7

#define LCD_FONT_5X7    0
#define LCD_FONT_5X10   1

#define LCD_DISP_SHIFT_OFF			0
#define LCD_CURSOR_DIR_INC		    1
#define LCD_CURSOR_DIR_DEC		    0
#define LCD_DISPLAY_ON              1
#define LCD_DISPLAY_OFF             0
#define LCD_CURSOR_ON               1
#define LCD_CURSOR_OFF              0
#define LCD_BLINK_ON                1
#define LCD_BLINK_OFF               0


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef enum {
    d0,
    d1,
    d2,
    d3,
    d4,
    d5,
    d6,
    d7,
    rs,
    rw,
    e,
    _lcdPinsNum
}lcdPins_t;

typedef struct {
    uint8_t pin;
    void* port;
}lcdPinCfg_t;

typedef struct {
    const lcdPinCfg_t lcdPinsArr[_lcdPinsNum];
    // uint8_t mode;
    
    uint8_t cursor_dir;
    uint8_t disp_shift;

    uint8_t display;
    uint8_t cursor;
    uint8_t blink;
}lcdCfg_t;


/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/



#endif /* _H_ */