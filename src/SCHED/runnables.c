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
void updateState();


const runnable_t runnables[_runsNum] = {
    // [updateTime] = {
    //     .period_mS = 1,
    //     .callBck = App_task
    // },
    [display_run] = {
        /*  */
        .period_mS = 6,
        .callBck = updateTime
    },
    [updateState_] = {
        .period_mS = 35,
        .callBck = updateState
    },
    [getPressed_run] = {
        /* looping over switches and updating currently pressed */
        .period_mS = 40,
        .callBck = getPressed
    },
    [hsw_task] = {
        /* updating states PRESSED/RELEASED of all switches */
        .period_mS = 8,
        .callBck = Hsw_task
    },
    [lcd_task] = {
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


