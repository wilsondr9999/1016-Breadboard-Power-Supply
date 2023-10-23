// Top header file for project 1016
// Breadboard Power Supply

#ifndef INC_1016TOP_H_
#define INC_1016TOP_H_

// Includes
#include "main.h"

// Global Variables
extern TIM_HandleTypeDef htim3;

// Function Declarations
void _1016_TimerSetup(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

// State Machine Typedefs
// POST/Run State Machine
typedef enum {
	stPowerOnDelay,
	stLEDTest1,
	stLEDTest2,
	stLEDTest3,
	stLEDTest4,
	stLEDTest5,
	stLEDTest6,
	stPostLEDTestDelay,
	stRun
} typeStMachPOSTRun;

// Config State Machine
typedef enum {
	st5T5B,
	st5T3B,
	st3T5B,
	st3T3B
} typeStMachConfig;

// Config/Output Buttons State Machine
typedef enum {
	stNotPressed,
	stMaybePressedDebounce,
	stPressed,
	stMaybeNotPressedDebounce
} typeStMachInputButton;

// Output Enable/Monitoring State Machine
typedef enum {
	stNotEnabled,
	stEnabledWaitStable,
	stEnabledMonitor
} typeStMachOutput;

// Error State Machine
typedef enum {
	stNoError,
	stErrorDetected,
	stErrorLEDOn,
	stErrorLEDOff
} typeStMachError;

#endif /* INC_1016TOP_H_ */
