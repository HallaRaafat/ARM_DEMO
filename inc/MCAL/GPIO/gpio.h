#ifndef GPIO_H_
#define GPIO_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include <stdint.h>
#include "gpio_defines.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define PORT_H     ((void* const)0x40021C00)
#define PORT_E     ((void* const)0x40021000)
#define PORT_D     ((void* const)0x40020C00)
#define PORT_C     ((void* const)0x40020800)
#define PORT_B     ((void* const)0x40020400)
#define PORT_A     ((void* const)0x40020000)

#define PIN_0       (uint8_t)0
#define PIN_1       (uint8_t)1
#define PIN_2       (uint8_t)2
#define PIN_3       (uint8_t)3
#define PIN_4       (uint8_t)4
#define PIN_5       (uint8_t)5
#define PIN_6       (uint8_t)6
#define PIN_7       (uint8_t)7
#define PIN_8       (uint8_t)8
#define PIN_9       (uint8_t)9
#define PIN_10      (uint8_t)10
#define PIN_11      (uint8_t)11
#define PIN_12      (uint8_t)12
#define PIN_13      (uint8_t)13  
#define PIN_14      (uint8_t)14
#define PIN_15      (uint8_t)15

#define PIN_VALUE_HIGH      (uint8_t)0x01
#define PIN_VALUE_LOW       (uint8_t)0x00

#define RETURN_GPIO_OK           (uint8_t)0
#define RETURN_GPIO_NOT_OK       (uint8_t)1

//PUPD2_OTYPE1_MODE2
#define MODE_OUTPUT_PP      (uint8_t)(MODE_OUTPUT|OTYPE_PP|PUPD_NONE)
#define MODE_OUTPUT_PP_PU   (uint8_t)(MODE_OUTPUT|OTYPE_PP|PUPD_PU)
#define MODE_OUTPUT_PP_PD   (uint8_t)(MODE_OUTPUT|OTYPE_PP|PUPD_PD)

#define MODE_OUTPUT_OD      (uint8_t)(MODE_OUTPUT|OTYPE_OD|PUPD_NONE)
#define MODE_OUTPUT_OD_PU   (uint8_t)(MODE_OUTPUT|OTYPE_OD|PUPD_PU)
#define MODE_OUTPUT_OD_PD   (uint8_t)(MODE_OUTPUT|OTYPE_OD|PUPD_PD)

#define MODE_AF_PP          (uint8_t)(MODE_AF|OTYPE_PP|PUPD_NONE)
#define MODE_AF_PP_PU       (uint8_t)(MODE_AF|OTYPE_PP|PUPD_PU)
#define MODE_AF_PP_PD       (uint8_t)(MODE_AF|OTYPE_PP|PUPD_PD)
#define MODE_AF_OD          (uint8_t)(MODE_AF|OTYPE_OD|PUPD_NONE)
#define MODE_AF_OD_PU       (uint8_t)(MODE_AF|OTYPE_OD|PUPD_PU)
#define MODE_AF_OD_PD       (uint8_t)(MODE_AF|OTYPE_OD|PUPD_PD)

#define MODE_IP_FLOATING    (uint8_t)(MODE_INPUT|OTYPE_DEFAULT|PUPD_NONE)
#define MODE_IP_PU          (uint8_t)(MODE_INPUT|OTYPE_DEFAULT|PUPD_PU)
#define MODE_IP_PD          (uint8_t)(MODE_INPUT|OTYPE_DEFAULT|PUPD_PD)

#define MODE_ANALOG         (uint8_t)(MODE_AN|OTYPE_DEFAULT|PUPD_NONE)

#define SPEED_LOW           (uint8_t)0x00
#define SPEED_MEDIUM        (uint8_t)0x01
#define SPEED_HIGH          (uint8_t)0x02
#define SPEED_VERY_HIGH     (uint8_t)0x03

#define AF_SYSTEM                   (uint8_t)0x00
#define AF_TIM_1_2                  (uint8_t)0x01
#define AF_TIM_3_4_5                (uint8_t)0x02
#define AF_TIM_9_10_11              (uint8_t)0x03
#define AF_I2C_1_2_3                (uint8_t)0x04
#define AF_SPI_1_2_3_4              (uint8_t)0x05
#define AF_SPI_3                    (uint8_t)0x06
#define AF_USART_1_2                (uint8_t)0x07
#define AF_USART_6                  (uint8_t)0x08
#define AF_I2C_2_3                  (uint8_t)0x09
#define AF_OTG_FS                   (uint8_t)0x0A
#define AF_SDIO                     (uint8_t)0x0C
#define AF_EVENTOUT                 (uint8_t)0x0F

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct {
    uint8_t pin;
    uint8_t speed;
    uint8_t mode;
    uint8_t af;
    void* port;    
}gpioPin_t;


/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/
uint8_t gpio_initPin(gpioPin_t* pinCfg);
uint8_t gpio_setPinValue(void* port, uint8_t pin, uint8_t pin_value);
uint8_t gpio_getPinValue(void* port, uint8_t pin, uint8_t* pin_value);


#endif /* GPIO_H_ */