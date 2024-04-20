/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "SCHED/runnables.h"
#include "SCHED/sched.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/

void updateTime(void);
void getPressed(void);
void Hsw_task(void);
void Lcd_task(void);
void updateState(void);
void recieveKey(void);

const runnable_t runnables[_runsNum] = {
    [timeUpdate_runID] = {
        /*  */
        .period_mS = 6,
        .callBck = updateTime
    },
    [usartRx_runID] = {
        .period_mS = 3,
        .callBck = recieveKey
    },
    [appSM_runID] = {
        .period_mS = 35,
        .callBck = updateState
    },
    [pressedKeyTx_runID] = {
        /* looping over switches and updating currently pressed */
        .period_mS = 40,
        .callBck = getPressed
    },
    [hsw_runID] = {
        /* updating states PRESSED/RELEASED of all switches */
        .period_mS = 8,
        .callBck = Hsw_task
    },
    [lcd_runID] = {
        /* LCD */
        .period_mS = 2,
        .callBck = Lcd_task
    }
};

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/


