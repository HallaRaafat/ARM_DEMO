#ifndef APP_H_
#define APP_H_

#include<stdint.h>

#define NULL        (void*)0

#define FRAME_START 0x99

#define GPIO_MOD    0x01
#define GPIO_SET    0x01
#define GPIO_GET    0x02

#define SW_MOD      0x04
#define SW_GET      0x01

#define LED_MOD     0x05
#define LED_SET     0x01

// #define GPIO_PORT_A     0
// #define GPIO_PORT_B     1
// #define GPIO_PORT_C     2
// #define GPIO_PORT_D     3

#endif 