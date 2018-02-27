//////////////////////////////////////////////////////////////////////
#include "TimedAction.h"
#include "VirtualWire.h"
#include <LiquidCrystal.h>

// Initializare ecran
LiquidCrystal LCD(8,9,4,5,6,7);

// Developer
boolean DebugMode = true;
int DebugSerialValue = 0;

// Radio
boolean Radio_Status = false;
int Radio_Speed = 4000;
int PIN_tx = 10;
int PIN_rx = 11;
int Radio_Test_Value = 0;

// Potentiometer
int PIN_Potentiometer = 0;
int OLD_Potentiometer = 0;
int Val_Potentiometer = 0;

// Joystick LeftRight
int PIN_Joystick_LeftRight = 1;
int OLD_Joystick_LeftRight = 0;
int Val_Joystick_LeftRight = 0;

// Joystick TopBottom
int PIN_Joystick_TopBottom = 2;
int OLD_Joystick_TopBottom = 0;
int Val_Joystick_TopBottom = 0;

// Buttons
int PIN_Button_1 = 22;    // Joystick

int PIN_Button_2 = 24;
int PIN_Button_3 = 26;
int PIN_Button_4 = 28;
int PIN_Button_5 = 30;

int PIN_Button_6 = 31;
int PIN_Button_7 = 33;
int PIN_Button_8 = 35;

// Buttons Check
int ButtonCheck_1 = 0;
int ButtonCheck_2 = 0;
int ButtonCheck_3 = 0;
int ButtonCheck_4 = 0;
int ButtonCheck_5 = 0;
int ButtonCheck_6 = 0;
int ButtonCheck_7 = 0;
int ButtonCheck_8 = 0;

// Leds
int PIN_Led_1 = 32;
int PIN_Led_2 = 34;

