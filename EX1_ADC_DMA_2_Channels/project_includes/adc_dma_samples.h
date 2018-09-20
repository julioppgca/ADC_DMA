/**
 *  @file       adc_dma_samples.h
 *
 *  @brief     ADC Driver to use along with TI-RTOS
   Created on: 24 de ago de 2017
   Updated on: 6 de jun de 2018
       Author: Eng. Julio Santos -
  This drive is designed to use DMA, in a PING/PONG burst transfer mode, in order to
  get 256 samples from AIN0 to AIN15. At the end of transfer an event semaphore is unblocked
  and the data will be available in a uint16_t matrix named ADCchannel. The total size
  of ADCchannel matrix is 16 row per 256 columns.
   Dependencies from TI-RTOS configuration file (.cfg)
@code
//  Hardware interrupt enabled
       var m3Hwi = xdc.useModule('ti.sysbios.family.arm.m3.Hwi');
//  Hwi Tasks declaration
       var m3Hwi0Params = new m3Hwi.Params();
       m3Hwi0Params.instance.name = "adcSeq0_Hwi_Handle";
       m3Hwi0Params.enableInt = false;
       m3Hwi0Params.priority = 255;
       Program.global.adcSeq0_Hwi_Handle = m3Hwi.create(30, "&adcSeq0_Hwi", m3Hwi0Params);
       var m3Hwi1Params = new m3Hwi.Params();
       m3Hwi1Params.instance.name = "adcSeq1_Hwi_Handle";
       m3Hwi1Params.enableInt = false;
       m3Hwi1Params.priority = 255;
       m3Hwi1Params.arg = 0;
       Program.global.adcSeq1_Hwi_Handle = m3Hwi.create(62, "&adcSeq1_Hwi", m3Hwi1Params);
//  Semaphores
       var Semaphore = xdc.useModule('ti.sysbios.knl.Semaphore');
       Semaphore.supportsEvents = true;
//  Events
       var event0Params = new Event.Params();
       event0Params.instance.name = "e_adcData_Ready";
       Program.global.e_adcData_Ready = Event.create(event0Params);
//  Swi Task Enabled
       var Swi = xdc.useModule('ti.sysbios.knl.Swi');
//  Swi Tasks declaration
        var swi0Params = new Swi.Params();
        swi0Params.instance.name = "adc0Ping_Swi_Handle";
        Program.global.adc0Ping_Swi_Handle = Swi.create("&adc0Ping_Swi", swi0Params);
        var swi0Params0 = new Swi.Params();
        swi0Params0.instance.name = "adc0Pong_Swi_Handle";
        Program.global.adc0Pong_Swi_Handle = Swi.create("&adc0Pong_Swi", swi0Params0);
        var swi2Params = new Swi.Params();
        swi2Params.instance.name = "adc1Ping_Swi_Handle";
        Program.global.adc1Ping_Swi_Handle = Swi.create("&adc1Ping_Swi", swi2Params);
        var swi3Params = new Swi.Params();
        swi3Params.instance.name = "adc1Pong_Swi_Handle";
        swi3Params.priority = -1;
        Program.global.adc1Pong_Swi_Handle = Swi.create("&adc1Pong_Swi", swi3Params);
@endcode
How to use:
    1 - Added (if its not added yet) the dependencies to the RTOS configuration file (.cfg).
    2 - Call the function startSampling(); somewhere in your program.
    3 - Event pend before data being filled by DMA.
        Eg.:
        @code
        // wait adc0 and adc1 data being transferred from DMA
        Event_pend(e_adcData_Ready,(Event_Id_00+Event_Id_01),Event_Id_NONE,BIOS_WAIT_FOREVER);
        @endcode
    4 - Data will be available in the matrix variable ADCchannel[channel][samples].
        Eg.:
            ADCchannel[0][0] is the first sample from channel 0 (AIN0)
            ADCchannel[0][256] is the last sample form channel 0 (AIN0)
    5 - Copy the channel specific data to your process buffer to avoid DMA overwrite sampled data.
 *
 *  The adc_dma_samples header file should be included in an application as
 *  follows:
 *  @code
 *  #include <adc_dma_samples.h>
 *  @endcode
 *
 *  ============================================================================
 */
#ifndef __SAMPLES_CONFIG_H__
#define __SAMPLES_CONFIG_H__

/* Standard variables definitions */
#include <stdint.h>
#include <stdbool.h>

/* XDCtools Header files */
#include <xdc/cfg/global.h>
#include <xdc/runtime/Log.h>   // to use Log_Info

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Event.h>

/* Tivaware Header files */
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_adc.h"
#include "inc/hw_gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "driverlib/udma.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

/* TM4C tivaware lib */
#include <ti/drivers/GPIO.h>

/* Project Header files */
#include "project_includes/Board.h"

/* ARM Math CMSIS DSP */
//#include <arm_math.h>

/**
 *
 *      Data acquisition parameters
 *
 */
#define DMA_BUFFER_SIZE                 1024            //!< don't change!
#define CLK_FREQ                        80000000        //!< TM4C clock frequency
#define ADC_OVERSAMPLE_VALUE            16               //!< Over sample value 2..64 (power of 2 steps)
#define SAMPLE_FRAME                    1024             //!< 256 points in 60Hz
#define SAMPLE_FREQUENCY                60*SAMPLE_FRAME //!< Sample Frequency: 15360Hz -> 15,36kHz
#define ADC_OFFSET                      2048.0          //!< Not used, just in case
#define ADC_SCALE                       3.3/4095        //!< Vmax/ADC_res
#define INITIAL_TRANSFER_SKIP_NUMBER    1               //!< Skip the first transfer to give ADC time to settling

/* uncomment to get ADCchannel in float format, it uses 16kb of RAM */
//#define USE_FLOAT

enum analogInputsADC0
{
    AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7, AIN_OFFSET
};

enum analogInputsADC1
{
    AIN8, AIN9, AIN10, AIN11, AIN12, AIN13, AIN14, AIN15
};

/**
 * @name    Analog channels enumeration
 * @def     analogChannels
 * @brief   List of all analog channel processed by ADC
 */
enum analogChannels
{
    CH0, CH1, CH2,  CH3,  CH4,  CH5,  CH6,  CH7,
    CH8, CH9, CH10, CH11, CH12, CH13, CH14, CH15,
    CHANNELS_COUNTER
};


/**
 *
 *      Local functions
 *
 */
static void adcPinConfig(void);                 // Analog I/O pins configuration
static void adcInit(void);                      // ADC init
static void timerAdcInit(uint32_t sample_freq); // ADC Timer trigger init
static void dmaInit(void);                      // DMA init

/**
 *
 *      Software Interrupt (Swi) functions
 *
 */
void adc0Ping_Swi(void);
void adc0Pong_Swi(void);
void adc1Ping_Swi(void);
void adc1Pong_Swi(void);

/**
 *
 *      Hardware Interrupt (Hwi) functions
 *
 */
void adcSeq0_Hwi(void);    //!< Interrupt service of ADC0 Sequencer 0
void adcSeq1_Hwi(void);    //!< Interrupt service of ADC1 Sequencer 0


/**
 *
 *      Initialization function
 *
 */
void startSampling(void);

/**
 *
 *      ADCchannel result matrix
 *
 */
//extern float ADCchannel[2][DMA_BUFFER_SIZE];


#endif // __SAMPLES_CONFIG_H__
