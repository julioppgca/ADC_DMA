#include <project_includes/adc_dma_samples.h>

/**
 *
 *                     Globals
 *
 */
// uDMA control table variable
static uint32_t udmaCtrlTable[DMA_BUFFER_SIZE]__attribute__((aligned(DMA_BUFFER_SIZE)));

// transfer buffer
static uint16_t g_uint16_adc0_ping[DMA_BUFFER_SIZE];
static uint16_t g_uint16_adc0_pong[DMA_BUFFER_SIZE];

// analog channel matrix
// ADC channels stored values
#ifdef USE_FLOAT
float32_t ADCchannel[CHANNELS_COUNTER][SAMPLE_FRAME];
#else
uint16_t ADCchannel[CHANNELS_COUNTER][SAMPLE_FRAME];
#endif

float ain1[256];

void copyAin1(uint16_t *pSrc, float *pDst, uint16_t size )
{
    uint16_t i;

    for(i=0;i<size;i++)
        *pDst++ = (float)*pSrc++;

}


/**
 *                  Start Sampling proccess
 *  Must be called in order to start data acquisition system
 *
 */
void startSampling(void)
{
    adcInit();
    timerAdcInit(SAMPLE_FREQUENCY);
    dmaInit();
}

/**
 *                  Initialize ADC pins
 *  Configure all available analog input pins as analog input type.
 *
 */
static void adcPinConfig(void)
{
    //
       // Enable Peripheral Clocks
       //
       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

       //
       // Configure the GPIO Pin Mux for PE3
       // for AIN0
       //
       MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

       //
       // Configure the GPIO Pin Mux for PE2
       // for AIN1
       //
       MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);

       //
       // Configure the GPIO Pin Mux for PE1
       // for AIN2
       //
       MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1);

       //
       // Configure the GPIO Pin Mux for PE0
       // for AIN3
       //
       MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0);

       //
       // Configure the GPIO Pin Mux for PD3
       // for AIN4
       //
       MAP_GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_3);

       //
       // Configure the GPIO Pin Mux for PD2
       // for AIN5
       //
       MAP_GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);

       //
       // Configure the GPIO Pin Mux for PD1
       // for AIN6
       //
       MAP_GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1);

       //
       MAP_GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_4);

       //
       // Configure the GPIO Pin Mux for PD0
       // for AIN7
       //
       MAP_GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0);

}

/**
 *
 * @brief             Sample frequency timer set
 * Configure Timer4A to trigger ADC0 and ADC1 conversions
 * sample_freq is the desired sample frequency for ADC conversions
 * @param sample_freq Desired sample frequency in Hertz.
 */
static void timerAdcInit(uint32_t sample_freq)
{
    // Get system frequency
    uint32_t ui32ClockFreq;

//    // Set clock frequency
//    ui32ClockFreq = SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
//    SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480,
//    CLK_FREQ);

    //Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 2.5 = 80MHz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    ui32ClockFreq = SysCtlClockGet();

    // Enable timer peripheral clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
    SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER4);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER4));

    // Configure the timer
    TimerConfigure(TIMER4_BASE, TIMER_CFG_A_PERIODIC_UP);
    TimerLoadSet(TIMER4_BASE, TIMER_A, (ui32ClockFreq / sample_freq));

    // Enable timer to trigger ADC
    TimerControlTrigger(TIMER4_BASE, TIMER_A, true);

    // Enable event to trigger ADC
    TimerADCEventSet(TIMER4_BASE, TIMER_ADC_TIMEOUT_A);

    //enable timer
    TimerEnable(TIMER4_BASE, TIMER_A);

}

/**
 *
 *          Initialize ADC0 and ADC1
 *  Use 16 analog channels (AIN0...AIN15), half mapped to Sample Sequencer 0 (SS0) ADC0
 *  and half mapped to Sample Sequencer 0 (SS0) ADC1.
 *
 */
static void adcInit(void)
{
    // configure ADC pins
    adcPinConfig();

    /* ----------- ADC0 Initialization-----------*/

    // Enable ADC peripheral clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_ADC0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));

    // Configure the ADC clock to 1MSPS
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 15);

    // Use Hardware Oversample, be aware of the throughput from ADC speed!
    ADCHardwareOversampleConfigure(ADC0_BASE, ADC_OVERSAMPLE_VALUE);

    // Disable before configuring
    ADCSequenceDisable(ADC0_BASE, 0);

    // Configure ADC0 sequencer 0:
    // Triggered by timer, highest priority (0)
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_TIMER, 0);

    // Configure ADC0 sequencer 0 step 0:
    // Channel 8, last step in sequence, causes interrupt when step is complete
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH2);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH3);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ADC_CTL_CH4);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ADC_CTL_CH5);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 6, ADC_CTL_CH6);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 7, ADC_CTL_CH7 |
                             ADC_CTL_END | ADC_CTL_IE);

    // Analog reference is internal
    ADCReferenceSet(ADC0_BASE, ADC_REF_INT);

    //  Enable ADC interrupt
    ADCIntEnableEx(ADC0_BASE, ADC_INT_DMA_SS0);
    IntEnable(INT_ADC0SS0);

    // Enable ADC to use uDMA
    ADCSequenceDMAEnable(ADC0_BASE, 0);

    // Enable ADC
    ADCSequenceEnable(ADC0_BASE, 0);
}


/**
 *
 *              Initialize DMA
 *  Ping-pong mode with burst transfers.
 *
 */
static void dmaInit(void)
{
    /* Enable uDMA clock */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UDMA));

    /* Enable uDMA */
    uDMAEnable();

    /* Set the control table for uDMA */
    uDMAControlBaseSet(udmaCtrlTable);

    /* Disable unneeded attributes of the uDMA channels */
    uDMAChannelAttributeDisable(UDMA_CHANNEL_ADC0, UDMA_ATTR_ALL);

    // Only allow burst transfers ADC0
    uDMAChannelAttributeEnable(UDMA_CHANNEL_ADC0, UDMA_ATTR_USEBURST);

    // Channel A udma control set
    uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                          UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE |
                          UDMA_DST_INC_16 |
                          UDMA_ARB_8);

    uDMAChannelControlSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT,
                          UDMA_SIZE_16 |
                          UDMA_SRC_INC_NONE |
                          UDMA_DST_INC_16 |
                          UDMA_ARB_8);

    // Channel A transfer set for ADC0
    uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                           UDMA_MODE_PINGPONG,
                           (void *) (ADC0_BASE + ADC_O_SSFIFO0),
                           g_uint16_adc0_ping,
                           DMA_BUFFER_SIZE);

    uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT,
                           UDMA_MODE_PINGPONG,
                           (void *) (ADC0_BASE + ADC_O_SSFIFO0),
                           g_uint16_adc0_pong,
                           DMA_BUFFER_SIZE);

    /* Enable channels */
    // Channel for ADC0
    uDMAChannelEnable(UDMA_CHANNEL_ADC0);

}

/**
 *
 *              DMA ADC0 interrupt service
 *  Whenever DMA fills up one of the transfer buffer it call this.
 *  Reload control set and release data to be processed (AIN0...AIN7).
 *
 */
void adcSeq0_Hwi(void)
{
    GPIO_write(Board_LED0, 1);
    static uint8_t FisrtTrasnfer = 2*INITIAL_TRANSFER_SKIP_NUMBER;
    uint32_t modePrimary;
    uint32_t modeAlternate;

    // Clear the interrupt
    ADCIntClearEx(ADC0_BASE, ADC_INT_DMA_SS0);


    // Get the mode statuses of primary and alternate control structures
    modePrimary = uDMAChannelModeGet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT);
    modeAlternate = uDMAChannelModeGet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT);

    // Reload the control structures
    if ((modePrimary == UDMA_MODE_STOP) && (modeAlternate != UDMA_MODE_STOP))
    {
        // Need to reload primary control structure
        uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *) (ADC0_BASE + ADC_O_SSFIFO0),
                               g_uint16_adc0_ping,
                               DMA_BUFFER_SIZE);
        //Log_info0("DMA transfer ping - ADC0");
        // free to process g_g_uint16_adc0_ping
        if(!FisrtTrasnfer)
            Swi_post(adc0Ping_Swi_Handle);//Semaphore_post(s_adc0_ping_ready);
        else
            FisrtTrasnfer--;

    }
    else if ((modePrimary != UDMA_MODE_STOP) && (modeAlternate == UDMA_MODE_STOP))
    {
        // Need to reload alternate control structure
        uDMAChannelTransferSet(UDMA_CHANNEL_ADC0 | UDMA_ALT_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *) (ADC0_BASE + ADC_O_SSFIFO0),
                               g_uint16_adc0_pong,
                               DMA_BUFFER_SIZE);
        //Log_info0("DMA transfer pong - ADC0");
        // free to process g_g_uint16_adc0_pong
        if(!FisrtTrasnfer)
            Swi_post(adc0Pong_Swi_Handle);//Semaphore_post(s_adc0_pong_ready);
        else
            FisrtTrasnfer--;
    }
    else
    {
        // Something is wrong, restart all DMA control set
        dmaInit();
        Log_info0("DMA transfer set restarted due an error - ADC0");
    }


    GPIO_write(Board_LED0, 0);
}


/*------------------------------------------------
 *              ADC0 Transfer Values
 *-----------------------------------------------*/
void adc0Ping_Swi(void)
{
    uint16_t i, j;
    // process first part of AIN0...AIN7
    for (i = 0, j = 0; i < SAMPLE_FRAME / 2; i++)
    {
        ADCchannel[CH0][i] = g_uint16_adc0_ping[j + AIN0];
        ADCchannel[CH1][i] = g_uint16_adc0_ping[j + AIN1];
        ADCchannel[CH2][i] = g_uint16_adc0_ping[j + AIN2];
        ADCchannel[CH3][i] = g_uint16_adc0_ping[j + AIN3];
        ADCchannel[CH4][i] = g_uint16_adc0_ping[j + AIN4];
        ADCchannel[CH5][i] = g_uint16_adc0_ping[j + AIN5];
        ADCchannel[CH6][i] = g_uint16_adc0_ping[j + AIN6];
        ADCchannel[CH7][i] = g_uint16_adc0_ping[j + AIN7];
        j += AIN_OFFSET;
    }
}

void adc0Pong_Swi(void)
{
    uint16_t i, j;
    // process last part of AIN0...AIN7
    for (i = SAMPLE_FRAME / 2, j = 0; i < SAMPLE_FRAME; i++)
    {
        ADCchannel[CH0][i] =  g_uint16_adc0_pong[j + AIN0];
        ADCchannel[CH1][i] =  g_uint16_adc0_pong[j + AIN1];
        ADCchannel[CH2][i] =  g_uint16_adc0_pong[j + AIN2];
        ADCchannel[CH3][i] =  g_uint16_adc0_pong[j + AIN3];
        ADCchannel[CH4][i] =  g_uint16_adc0_pong[j + AIN4];
        ADCchannel[CH5][i] =  g_uint16_adc0_pong[j + AIN5];
        ADCchannel[CH6][i] =  g_uint16_adc0_pong[j + AIN6];
        ADCchannel[CH7][i] =  g_uint16_adc0_pong[j + AIN7];
        j += AIN_OFFSET;
    }

    // debug only, use CCS Graph tool
    copyAin1(ADCchannel[CH1],ain1,256);

    // post event ADC0 data ready
    Event_post(e_adcData_Ready, Event_Id_00);
}


