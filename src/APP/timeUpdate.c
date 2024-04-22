#include"APP/app.h"

extern uint8_t stopwatchState;

uint64_t timestamp = 0;
uint64_t stopwatchTime = 0;

uint8_t year = 24;
uint8_t mon = 4;
uint8_t day = 22;
uint8_t hrs = 4;
uint8_t min = 15;
uint8_t sec = 0;
uint16_t mSec = 0;


void timeUpdate(){
    timestamp += 2;
    // hrs = (timestamp / (1000 * 60 * 60)) % 24;
    // min = (timestamp / (1000 * 60)) % 60;
    // sec = (timestamp / 1000) % 60;

    mSec += 2;
    if(mSec == 1000){
        sec++;
        mSec = 0;
    }
    if(sec > 59){
        min++;
        sec = 0;
    }
    if(min > 59){
        hrs++;
        min = 0;
    }
    if(hrs > 23){
        day++;
        hrs = 0;
    }
    if(day > 30){
        mon++;
        day = 1;
    }
    if(mon > 12){
        year++;
        mon = 1;
    }
    if(year == 100){
        year = 0;
    }

    if(stopwatchState == STOPWATCH_STATE_RUN){
        stopwatchTime += 2;
    }
}

