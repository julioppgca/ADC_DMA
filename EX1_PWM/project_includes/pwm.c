#include "project_includes/pwm.h"


void pwmInit(void)
{
    //Configure PWM Clock to match system - 80MHz.
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    // Enable clock to Port B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
        ;

    // Enable clock to PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
        ;

    // Configure the GPIO Pin Mux for PB6
    // for M0PWM0
    MAP_GPIOPinConfigure(GPIO_PB6_M0PWM0);
    MAP_GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

    //Configure PWM Options
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
    PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //Set the Period (expressed in clock ticks) - 120MHz - 1200 = 100KHz of Fs.
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, PWM_PERIOD);

    //Set PWM duty-50% (Period /2)
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, PWM_PERIOD / 2);

    // Enable the PWM generator
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    // Use negative logic
    //PWMOutputInvert(PWM0_BASE, PWM_OUT_0_BIT, true);

    // Turn on output 0
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);



//    // Configure the GPIO Pin Mux for PB7
//    // for M0PWM1
//    MAP_GPIOPinConfigure(GPIO_PB7_M0PWM1);
//    MAP_GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
//
//    //Set PWM duty-50% (Period /2)
//    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, PWM_PERIOD / 2);
//
//    // Turn on output 1
//    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);

//    // Dead band enabled turns PWM into complementary mode
//    PWMDeadBandEnable(PWM0_BASE, PWM_GEN_0, DEAD_TIME, DEAD_TIME );
}
