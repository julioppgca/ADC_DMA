/* Standard variables definitions */
#include <stdint.h>
#include <stdbool.h>
//
///* XDCtools Header files */
//#include <xdc/cfg/global.h>
//#include <xdc/runtime/Log.h>   // to use Log_Info
//
///* BIOS Header files */
//#include <ti/sysbios/BIOS.h>
//#include <ti/sysbios/knl/Swi.h>
//#include <ti/sysbios/knl/Task.h>
//#include <ti/sysbios/knl/Semaphore.h>
//#include <ti/sysbios/knl/Event.h>

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
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"


/* TM4C tivaware lib */
#include <ti/drivers/GPIO.h>

/* Project Header files */
#include "project_includes/Board.h"


/*----- Defines ----- */
#define MCU_CLOCK       80000000                    // 80MHz
#define PWM_FREQUENCY   20000                       // 20KHZ
#define PWM_PERIOD      MCU_CLOCK/PWM_FREQUENCY     // 80MHz / 20KHz
#define DEAD_TIME       PWM_PERIOD * 0.01           // set to 0.1% of pwm period

/* ----- Init pwm function ----- */
void pwmInit(void);
