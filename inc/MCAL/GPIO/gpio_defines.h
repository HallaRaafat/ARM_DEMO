#ifndef GPIO_DEF_H_
#define GPIO_DEF_H_

#include "LIB/bitMasks.h"

#define MODE_INPUT      0x00
#define MODE_OUTPUT     0x01
#define MODE_AF         0x02
#define MODE_AN         0x03


#define OTYPE_DEFAULT   OTYPE_PP
#define OTYPE_PP        (0x00 << 2)
#define OTYPE_OD        (0x01 << 2)


#define PUPD_NONE       (0x00 << 3)
#define PUPD_PU         (0x01 << 3)
#define PUPD_PD         (0x02 << 3)

#endif /* GPIO_DEF_H_ */
