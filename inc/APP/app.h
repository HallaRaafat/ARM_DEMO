#ifndef APP_H_
#define APP_H_

#include<stdint.h>

#define NULL        (void*)0

#define APP_STATE_CLOCK                 0
#define APP_STATE_STOPWATCH             1

#define CLOCK_STATE_DISPLAY             2
#define CLOCK_STATE_EDIT                3
#define STOPWATCH_STATE_RESET           4
#define STOPWATCH_STATE_RUN             5
#define STOPWATCH_STATE_PAUSE           6

#endif 