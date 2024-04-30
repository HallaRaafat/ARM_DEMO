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

void timeUpdate(void);
void pressedKeyTx(void);
void Hsw_task(void);
void Lcd_task(void);
void appSM(void);
void pressedKeyRx(void);

const runnable_t runnables[_runsNum] = {
    // [timeUpdate_runID] = {
    //     /*  */
    //     .period_mS = 2,
    //     .callBck = timeUpdate
    // },
    // // [pressedKeyRx_runID] = {
    // //     .period_mS = 1,
    // //     .callBck = pressedKeyRx
    // // },
    // [appSM_runID] = {
    //     .period_mS = 35,
    //     .callBck = appSM
    // },
    // [pressedKeyTx_runID] = {
    //     /* looping over switches and updating currently pressed */
    //     .period_mS = 40,
    //     .callBck = pressedKeyTx
    // },
    [hsw_runID] = {
        /* updating states PRESSED/RELEASED of all switches */
        .period_mS = 8,
        .callBck = Hsw_task
    }
    // [lcd_runID] = {
    //     /* LCD */
    //     .period_mS = 2,
    //     .callBck = Lcd_task
    // }
};

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/


