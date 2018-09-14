

/* XDCtools Header files  */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/cfg/global.h> // to get static definitions from RTOS.cfg file

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>


/* Board Header file */
#include "project_includes/Board.h"
#include "project_includes/adc_dma_samples.h"

#define HEART_BEAT_TIME     500     //time in ms


/* ----- Heart Beat ----- */
void heartBeat_TASK(void)
{

    startSampling();
    while (1)
    {
        Task_sleep(HEART_BEAT_TIME);
        GPIO_toggle(Board_LED1);
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();

    /* Turn on user LED */
    GPIO_write(Board_LED1, Board_LED_ON);

    System_printf("\nAlmost blank example, only a heart beat from the board...\n");
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
