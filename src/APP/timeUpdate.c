#include"APP/app.h"

extern uint8_t stopwatchState;

uint64_t timestamp = 0;
uint64_t stopwatchTime = 0;

uint8_t hrs;
uint8_t min;
uint8_t sec;

void timeUpdate(){
    timestamp += 6;
    hrs = (timestamp / (1000 * 60 * 60)) % 24;
    min = (timestamp / (1000 * 60)) % 60;
    sec = (timestamp / 1000) % 60;
    if(stopwatchState == STOPWATCH_STATE_RUN){
        stopwatchTime += 6;
    }
}

