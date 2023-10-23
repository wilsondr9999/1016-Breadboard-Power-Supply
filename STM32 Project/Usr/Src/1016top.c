// Top file for project 1016
// Breadboard Power Supply

// Includes
#include "1016top.h"
#include "main.h"

// Private Variables
typeStMachPOSTRun stMachPOSTRun=stPowerOnDelay;
int stMachPOSTRunDelayCtr=0;
typeStMachConfig stMachConfig=st5T5B;
typeStMachInputButton stMachConfigButton=stNotPressed;
typeStMachInputButton stMachOutputButton=stNotPressed;
int stMachConfigBtnDebounceDelayCtr=0;
int stMachOutputBtnDebounceDelayCtr=0;
int stMachConfigBtnDetected=0;
int stMachOutputBtnDetected=0;
typeStMachOutput stMachOutput=stNotEnabled;
int stMachOutputWaitStableDelayCtr=0;
typeStMachError stMachError=stNoError;
int stMachErrorLEDBlinkCtr=0;
int stMachErrorLEDDelayCtr=0;

// Private Function Declarations
void POSTRunSM(void);
void ConfigButtonSM(void);
void ConfigSM(void);
void OutputButtonSM(void);
void OutputEnableMonitorSM(void);
void ErrorSM(void);

// Public Function Definitions
void _1016_TimerSetup(void) {
	// Start the main timer, this will call the ISR at 100 Hz (10 msec between calls)
	HAL_TIM_Base_Start_IT(&htim3);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	// Check to make sure we've been called by the correct timer
	if (htim == &htim3) {
		// We've been called by the correct timer, begin processing

		// Process the POST/Run State machine first
		POSTRunSM();
		// If we're not in Run mode yet, nothing else can run, exit the ISR
		if (stMachPOSTRun!=stRun) return;

		// Process the Error State Machine next
		ErrorSM();
		// If the error state machine is in any state other than No Error, exit the ISR
		if (stMachError!=stNoError) return;

		// Process the Config Button Input State Machine
		ConfigButtonSM();

		// Process the Config State Machine
		ConfigSM();

		// Process the Output Button State Machine
		OutputButtonSM();

		// Process the Output Enable and Monitoring State Machine
		OutputEnableMonitorSM();
	}
}

// Private Functions
// POST/Run State Machine Function
void POSTRunSM(void) {
	// Handles the POST/Run state machine
	switch(stMachPOSTRun) {
		case stPowerOnDelay:
			// We're in the power-on delay period, wait 1 second (100 ticks)
			stMachPOSTRunDelayCtr++;
			// If 1 second has elapsed, advance state
			if (stMachPOSTRunDelayCtr>=100) {
				stMachPOSTRunDelayCtr=0;
				stMachPOSTRun=stLEDTest1;
			}
			break;
		case stLEDTest1:
			// Ready to test LED 1 (Top Rail 5V)
			stMachPOSTRunDelayCtr++;
			// If 0.25 second has elapsed, advance state
			if (stMachPOSTRunDelayCtr>=25) {
				stMachPOSTRunDelayCtr=0;
				HAL_GPIO_WritePin(LED_5VT_GPIO_Port, LED_5VT_Pin, GPIO_PIN_SET);
				stMachPOSTRun=stLEDTest2;
			} else
			{
				HAL_GPIO_WritePin(LED_5VT_GPIO_Port, LED_5VT_Pin, GPIO_PIN_RESET);
			}
			break;
		case stLEDTest2:
			// Ready to test LED 2 (Top Rail 3V3)
			stMachPOSTRunDelayCtr++;
			// If 0.25 second has elapsed, advance state
			if (stMachPOSTRunDelayCtr>=25) {
				stMachPOSTRunDelayCtr=0;
				HAL_GPIO_WritePin(LED_3V3T_GPIO_Port, LED_3V3T_Pin, GPIO_PIN_SET);
				stMachPOSTRun=stLEDTest3;
			} else
			{
				HAL_GPIO_WritePin(LED_3V3T_GPIO_Port, LED_3V3T_Pin, GPIO_PIN_RESET);
			}
			break;
		case stLEDTest3:
			// Ready to test LED 3 (Bottom Rail 5V)
			stMachPOSTRunDelayCtr++;
			// If 0.25 second has elapsed, advance state
			if (stMachPOSTRunDelayCtr>=25) {
				stMachPOSTRunDelayCtr=0;
				HAL_GPIO_WritePin(LED_5VB_GPIO_Port, LED_5VB_Pin, GPIO_PIN_SET);
				stMachPOSTRun=stLEDTest4;
			} else
			{
				HAL_GPIO_WritePin(LED_5VB_GPIO_Port, LED_5VB_Pin, GPIO_PIN_RESET);
			}
			break;
		case stLEDTest4:
			// Ready to test LED 4 (Bottom Rail 3V3)
			stMachPOSTRunDelayCtr++;
			// If 0.25 second has elapsed, advance state
			if (stMachPOSTRunDelayCtr>=25) {
				stMachPOSTRunDelayCtr=0;
				HAL_GPIO_WritePin(LED_3V3B_GPIO_Port, LED_3V3B_Pin, GPIO_PIN_SET);
				stMachPOSTRun=stLEDTest5;
			} else
			{
				HAL_GPIO_WritePin(LED_3V3B_GPIO_Port, LED_3V3B_Pin, GPIO_PIN_RESET);
			}
			break;
		case stLEDTest5:
			// Ready to test LED 5 (Output)
			stMachPOSTRunDelayCtr++;
			// If 0.25 second has elapsed, advance state
			if (stMachPOSTRunDelayCtr>=25) {
				stMachPOSTRunDelayCtr=0;
				HAL_GPIO_WritePin(LED_Output_GPIO_Port, LED_Output_Pin, GPIO_PIN_SET);
				stMachPOSTRun=stLEDTest6;
			} else
			{
				HAL_GPIO_WritePin(LED_Output_GPIO_Port, LED_Output_Pin, GPIO_PIN_RESET);
			}
			break;
		case stLEDTest6:
			// Ready to test LED 6 (Error)
			stMachPOSTRunDelayCtr++;
			// If 0.25 second has elapsed, advance state
			if (stMachPOSTRunDelayCtr>=25) {
				stMachPOSTRunDelayCtr=0;
				HAL_GPIO_WritePin(LED_Error_GPIO_Port, LED_Error_Pin, GPIO_PIN_SET);
				stMachPOSTRun=stPostLEDTestDelay;
			} else
			{
				HAL_GPIO_WritePin(LED_Error_GPIO_Port, LED_Error_Pin, GPIO_PIN_RESET);
			}
			break;
		case stPostLEDTestDelay:
			// Delay before entering Run mode, 1 second (100 ticks)
			stMachPOSTRunDelayCtr++;
			// If 1 second has elapsed, advance state
			if (stMachPOSTRunDelayCtr>=100) {
				stMachPOSTRunDelayCtr=0;
				stMachPOSTRun=stRun;
			}
			break;
		case stRun:
			// No action
			break;
	}
}
// Configuration Button State Machine Function
void ConfigButtonSM(void) {
	// Handles the Config Button State Machine

	// Check config button
	switch(stMachConfigButton) {
		case stNotPressed:
			// Check if the button has been pressed
			if (HAL_GPIO_ReadPin(Btn_Config_GPIO_Port, Btn_Config_Pin)==GPIO_PIN_RESET) {
				// Pin is pulled low, that means button is pressed, enter state to debounce
				stMachConfigBtnDebounceDelayCtr=0;
				stMachConfigButton=stMaybePressedDebounce;
			}
			break;
		case stMaybePressedDebounce:
			// Button must be fully held for 50 msec (5 ticks) before we consider it pressed
			if (HAL_GPIO_ReadPin(Btn_Config_GPIO_Port, Btn_Config_Pin)!=GPIO_PIN_RESET) {
				// Button bounced, return to not pressed state
				stMachConfigBtnDebounceDelayCtr=0;
				stMachConfigButton=stNotPressed;
			} else {
				// Button still down, add to counter
				stMachConfigBtnDebounceDelayCtr++;
				// If 50 msec (5 ticks) have passed, then button is definitely pressed
				if (stMachConfigBtnDebounceDelayCtr>=5) {
					stMachConfigBtnDebounceDelayCtr=0;
					stMachConfigBtnDetected=1;	// Button press has not yet been detected by other code
					stMachConfigButton=stPressed;
				}
			}
			break;
		case stPressed:
			// Check if the button has been released
			if (HAL_GPIO_ReadPin(Btn_Config_GPIO_Port, Btn_Config_Pin)==GPIO_PIN_SET) {
				// Pin is pulled high, that means button is released, enter state to debounce
				stMachConfigBtnDebounceDelayCtr=0;
				stMachConfigButton=stMaybeNotPressedDebounce;
			}
			break;
		case stMaybeNotPressedDebounce:
			// Button must be fully released for 50 msec (5 ticks) before we consider it released
			if (HAL_GPIO_ReadPin(Btn_Config_GPIO_Port, Btn_Config_Pin)!=GPIO_PIN_SET) {
				// Button bounced, return to pressed state
				stMachConfigBtnDebounceDelayCtr=0;
				stMachConfigButton=stPressed;
			} else {
				// Button still released, add to counter
				stMachConfigBtnDebounceDelayCtr++;
				// If 50 msec (5 ticks) have passed, then button is definitely released
				if (stMachConfigBtnDebounceDelayCtr>=5) {
					stMachConfigBtnDebounceDelayCtr=0;
					stMachConfigBtnDetected=0;	// Reset button pressed flag
					stMachConfigButton=stNotPressed;
				}
			}
			break;
	}
}
// Machine Configuration State Machine Function
void ConfigSM(void) {
	// Handles the Config State Machine

	// Check if config button is pressed and the press has not yet been recognized and that the output is off
	if (stMachConfigBtnDetected==1 && stMachOutput==stNotEnabled) {
		// Proceed to the next configuration
		stMachConfig++;
		if (stMachConfig>st3T3B) stMachConfig=st5T5B;
		// Flag that this button press has been recognized,
		// this makes sure the state only changes once per button press
		stMachConfigBtnDetected=0;

		// Set up the power output regulators for the selected configuration
		// To select 5V output, we ground out the select line via the open-drain GPIO by setting it low
		// To select 3V3 output, we float the select line via the open-drain GPIO by setting it high
		switch(stMachConfig) {
			case st5T5B:
				HAL_GPIO_WritePin(Select_VRailT_GPIO_Port,Select_VRailT_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Select_VRailB_GPIO_Port,Select_VRailB_Pin,GPIO_PIN_RESET);
				break;
			case st5T3B:
				HAL_GPIO_WritePin(Select_VRailT_GPIO_Port,Select_VRailT_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Select_VRailB_GPIO_Port,Select_VRailB_Pin,GPIO_PIN_SET);
				break;
			case st3T5B:
				HAL_GPIO_WritePin(Select_VRailT_GPIO_Port,Select_VRailT_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(Select_VRailB_GPIO_Port,Select_VRailB_Pin,GPIO_PIN_RESET);
				break;
			case st3T3B:
				HAL_GPIO_WritePin(Select_VRailT_GPIO_Port,Select_VRailT_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(Select_VRailB_GPIO_Port,Select_VRailB_Pin,GPIO_PIN_SET);
				break;
		}
	}

	// Set LED indicators
	// To turn LED on, we ground out the LED line via the open-drain GPIO by setting it low
	// To turn LED off, we float the LED line via the open-drain GPIO by setting it high
	switch(stMachConfig) {
		case st5T5B:
			HAL_GPIO_WritePin(LED_5VT_GPIO_Port,LED_5VT_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_3V3T_GPIO_Port,LED_3V3T_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_5VB_GPIO_Port,LED_5VB_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_3V3B_GPIO_Port,LED_3V3B_Pin,GPIO_PIN_SET);
			break;
		case st5T3B:
			HAL_GPIO_WritePin(LED_5VT_GPIO_Port,LED_5VT_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_3V3T_GPIO_Port,LED_3V3T_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_5VB_GPIO_Port,LED_5VB_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_3V3B_GPIO_Port,LED_3V3B_Pin,GPIO_PIN_RESET);
			break;
		case st3T5B:
			HAL_GPIO_WritePin(LED_5VT_GPIO_Port,LED_5VT_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_3V3T_GPIO_Port,LED_3V3T_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_5VB_GPIO_Port,LED_5VB_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_3V3B_GPIO_Port,LED_3V3B_Pin,GPIO_PIN_SET);
			break;
		case st3T3B:
			HAL_GPIO_WritePin(LED_5VT_GPIO_Port,LED_5VT_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_3V3T_GPIO_Port,LED_3V3T_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_5VB_GPIO_Port,LED_5VB_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_3V3B_GPIO_Port,LED_3V3B_Pin,GPIO_PIN_RESET);
			break;
	}
}
// Output Enable Button State Machine Function
void OutputButtonSM(void) {
	// Handles the Output Button State Machine

	// Check output enable button
	switch(stMachOutputButton) {
		case stNotPressed:
			// Check if the button has been pressed
			if (HAL_GPIO_ReadPin(Btn_OutputEn_GPIO_Port, Btn_OutputEn_Pin)==GPIO_PIN_RESET) {
				// Pin is pulled low, that means button is pressed, enter state to debounce
				stMachOutputBtnDebounceDelayCtr=0;
				stMachOutputButton=stMaybePressedDebounce;
			}
			break;
		case stMaybePressedDebounce:
			// Button must be fully held for 50 msec (5 ticks) before we consider it pressed
			if (HAL_GPIO_ReadPin(Btn_OutputEn_GPIO_Port, Btn_OutputEn_Pin)!=GPIO_PIN_RESET) {
				// Button bounced, return to not pressed state
				stMachOutputBtnDebounceDelayCtr=0;
				stMachOutputButton=stNotPressed;
			} else {
				// Button still down, add to counter
				stMachOutputBtnDebounceDelayCtr++;
				// If 50 msec (5 ticks) have passed, then button is definitely pressed
				if (stMachOutputBtnDebounceDelayCtr>=5) {
					stMachOutputBtnDebounceDelayCtr=0;
					stMachOutputBtnDetected=1;	// Button press has not yet been detected by other code
					stMachOutputButton=stPressed;
				}
			}
			break;
		case stPressed:
			// Check if the button has been released
			if (HAL_GPIO_ReadPin(Btn_OutputEn_GPIO_Port, Btn_OutputEn_Pin)==GPIO_PIN_SET) {
				// Pin is pulled high, that means button is released, enter state to debounce
				stMachOutputBtnDebounceDelayCtr=0;
				stMachOutputButton=stMaybeNotPressedDebounce;
			}
			break;
		case stMaybeNotPressedDebounce:
			// Button must be fully released for 50 msec (5 ticks) before we consider it released
			if (HAL_GPIO_ReadPin(Btn_OutputEn_GPIO_Port, Btn_OutputEn_Pin)!=GPIO_PIN_SET) {
				// Button bounced, return to pressed state
				stMachOutputBtnDebounceDelayCtr=0;
				stMachOutputButton=stPressed;
			} else {
				// Button still released, add to counter
				stMachOutputBtnDebounceDelayCtr++;
				// If 50 msec (5 ticks) have passed, then button is definitely released
				if (stMachOutputBtnDebounceDelayCtr>=5) {
					stMachOutputBtnDebounceDelayCtr=0;
					stMachOutputBtnDetected=0;	// Reset button pressed flag
					stMachOutputButton=stNotPressed;
				}
			}
			break;
	}
}
// Output Enable and Monitoring State Machine Function
void OutputEnableMonitorSM(void) {
	// Handles the Output Enable and Monitoring State Machine

	switch(stMachOutput) {
		case stNotEnabled:
			// See if user wants to turn on output, make sure we meet conditions
			if (stMachOutputBtnDetected==1 && stMachConfigButton==stNotPressed) {
				// Turn output on
				HAL_GPIO_WritePin(Output_Enable_GPIO_Port,Output_Enable_Pin,GPIO_PIN_SET);
				// Turn output LED on
				HAL_GPIO_WritePin(LED_Output_GPIO_Port,LED_Output_Pin,GPIO_PIN_RESET);
				// Flag that this button press has been recognized,
				// this makes sure the state only changes once per button press
				stMachOutputBtnDetected=0;
				stMachOutputWaitStableDelayCtr=0;
				// Go to next state
				stMachOutput=stEnabledWaitStable;
			}
			break;
		case stEnabledWaitStable:
			// We just turned on the output, need to wait for 50 msec before we begin monitoring
			// the Power_Good signals from the regulators
			stMachOutputWaitStableDelayCtr++;
			if (stMachOutputWaitStableDelayCtr>=5) {
				// We've waited 50 msec, go to monitoring state
				stMachOutputWaitStableDelayCtr=0;
				stMachOutput=stEnabledMonitor;
			}
			break;
		case stEnabledMonitor:
			// Output is on, monitor the power good signals from the regulators and shut down
			// if the power is not good.  Power good signals from the regulators are high when the
			// output power is OK.
			if (HAL_GPIO_ReadPin(PGood_RailT_GPIO_Port, PGood_RailT_Pin)==GPIO_PIN_RESET ||
				HAL_GPIO_ReadPin(PGood_RailB_GPIO_Port, PGood_RailB_Pin)==GPIO_PIN_RESET) {
				// We've detected a problem with one/both of the regulators, enter the error state
				stMachError=stErrorDetected;
				// The error state machine will shut down the regulators and blink the error LED,
				// but we're going shut them down here also so there's no delay
				// Turn output off
				HAL_GPIO_WritePin(Output_Enable_GPIO_Port,Output_Enable_Pin,GPIO_PIN_RESET);
				// Turn output LED off
				HAL_GPIO_WritePin(LED_Output_GPIO_Port,LED_Output_Pin,GPIO_PIN_SET);
				// Enter the not enabled state
				stMachOutput=stNotEnabled;
			}
			// Monitor if user wants to turn output power off
			if (stMachOutputBtnDetected==1 && stMachConfigButton==stNotPressed) {
				// Turn output off
				HAL_GPIO_WritePin(Output_Enable_GPIO_Port,Output_Enable_Pin,GPIO_PIN_RESET);
				// Turn output LED off
				HAL_GPIO_WritePin(LED_Output_GPIO_Port,LED_Output_Pin,GPIO_PIN_SET);
				// Flag that this button press has been recognized,
				// this makes sure the state only changes once per button press
				stMachOutputBtnDetected=0;
				stMachOutputWaitStableDelayCtr=0;
				// Go to next state
				stMachOutput=stNotEnabled;
			}
			break;
	}
}
// Error State Machine Function
void ErrorSM(void) {
	// Handles the Error State Machine

	switch(stMachError) {
		case stNoError:
			// No action
			break;
		case stErrorDetected:
			// The monitoring state machine detected an error from one of the regulators
			// (Power_Good went low).  Turn output off.
			HAL_GPIO_WritePin(Output_Enable_GPIO_Port,Output_Enable_Pin,GPIO_PIN_RESET);
			// Turn all LEDs off
			HAL_GPIO_WritePin(LED_Output_GPIO_Port,LED_Output_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_5VT_GPIO_Port,LED_5VT_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_3V3T_GPIO_Port,LED_3V3T_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_5VB_GPIO_Port,LED_5VB_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_3V3B_GPIO_Port,LED_3V3B_Pin,GPIO_PIN_SET);
			// Reset all state machines
			stMachConfigButton=stNotPressed;
			stMachOutputButton=stNotPressed;
			stMachConfigBtnDetected=0;
			stMachOutputBtnDetected=0;
			stMachConfigBtnDebounceDelayCtr=0;
			stMachOutputBtnDebounceDelayCtr=0;
			stMachOutput=stNotEnabled;
			stMachOutputWaitStableDelayCtr=0;
			// Go to the Error LED blink state
			stMachError=stErrorLEDOn;
			stMachErrorLEDBlinkCtr=0;
			stMachErrorLEDDelayCtr=0;
			break;
		case stErrorLEDOn:
			// Turn Error LED On
			HAL_GPIO_WritePin(LED_Error_GPIO_Port,LED_Error_Pin,GPIO_PIN_RESET);
			// Wait 250 msec before going to next state
			stMachErrorLEDDelayCtr++;
			if (stMachErrorLEDDelayCtr>=25) {
				stMachErrorLEDDelayCtr=0;
				stMachError=stErrorLEDOff;
			}
			break;
		case stErrorLEDOff:
			// Turn Error LED Off
			HAL_GPIO_WritePin(LED_Error_GPIO_Port,LED_Error_Pin,GPIO_PIN_SET);
			// Wait 250 msec before going to next state
			stMachErrorLEDDelayCtr++;
			if (stMachErrorLEDDelayCtr>=25) {
				stMachErrorLEDDelayCtr=0;
				// See if we have completed 10 blinks
				stMachErrorLEDBlinkCtr++;
				if (stMachErrorLEDBlinkCtr>=10) {
					// We completed 10 blinks, return to No Error state
					stMachErrorLEDBlinkCtr=0;
					stMachErrorLEDDelayCtr=0;
					stMachError=stNoError;
				} else {
					// We have not completed 10 blinks, return to Error LED On state
					stMachError=stErrorLEDOn;
				}
			}
			break;
	}
}
