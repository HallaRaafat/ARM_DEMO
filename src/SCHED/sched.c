/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "SCHED/sched.h"
#include "SCHED/runnables.h"
#include "MCAL/STK/stk.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/


/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
extern const runnable_t runnables[_runsNum];
static uint8_t pendingTicks = 0;
static uint64_t timeStamp = 0;

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/
static void sched();
static void tickCallBack();
/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
void sched_init() {
    stk_cfgMode(STK_MODE_PERIODIC);
    stk_setCallBck(tickCallBack);
    stk_setTime_mS((uint32_t)SCHED_TIME_MS);
}
void sched_start() {
    stk_start();
    while(1){
        if(pendingTicks) {
            pendingTicks--;
            sched();
        }
    }
}
static void sched() {
    timeStamp += SCHED_TIME_MS;
    for(uint8_t i = 0; i < _runsNum; i++) {
        if(!(timeStamp % runnables[i].period_mS)) {
            runnables[i].callBck();
        }
    }
}
static void tickCallBack(void) {
    pendingTicks++;
}