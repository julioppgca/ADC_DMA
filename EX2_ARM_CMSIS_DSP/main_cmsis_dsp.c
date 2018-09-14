

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

/* Include ARM Math CMSIS DSP Lib */
#include <arm_math.h>

#define HEART_BEAT_TIME     500     //time in ms


/* ----- Heart Beat ----- */
void heartBeat_TASK(void)
{
    // start samplling before enter heart beat loop
    startSampling();

    while (1)
    {
        Task_sleep(HEART_BEAT_TIME);
        GPIO_toggle(Board_LED1);
    }
}


/* ----- RMS Calc ----- */
void rmsCalc_TASK(void)
{
    static float32_t rmsValue;
    static float32_t meanValue;
    static float32_t ain0[SAMPLE_FRAME];

    while(1)
    {
        // reset rms value
        rmsValue = 0 ;

        // wait dma process
        Event_pend(e_adcData_Ready, Event_Id_00, Event_Id_NONE,
                BIOS_WAIT_FOREVER);

        //copy to new vector
        arm_copy_f32(ADCchannel[0], ain0, SAMPLE_FRAME);

        // get mean value
        arm_mean_f32(ain0, SAMPLE_FRAME, &meanValue);

        // apply offset
        arm_offset_f32( ain0, -meanValue, ain0, SAMPLE_FRAME);

        // get rms value from sample
        arm_rms_f32(ain0, SAMPLE_FRAME, &rmsValue);

        // lets take a rest
        Task_sleep(300);

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
