////////////////////////////////////////////////////////////////////
#include "MultiOptions.h"
#include "TimedAction.h"
#include "VirtualWire.h"
#include <LiquidCrystal.h>

// Initializare ecran
LiquidCrystal LCD(8,9,4,5,6,7);

// Developer
bool DebugMode = true;
bool DebugMode_PressButtons = false;
int DebugSerialValue = 0;

// Radio
boolean Radio_Status = true;
int Radio_Speed = 4000;
int PIN_tx = 10;
int PIN_rx = 11;
int Radio_Test_Value = 0;

// Potentiometer
int PIN_Potentiometer = 0;
int OLD_Potentiometer = 10;
int Val_Potentiometer = 10;

// Joystick Left <-> Right
int PIN_Joystick_LeftRight = 1;
int OLD_Joystick_LeftRight = 510;
int Val_Joystick_LeftRight = 510;

// Joystick Top <-> Bottom
int PIN_Joystick_TopBottom = 2;
int OLD_Joystick_TopBottom = 510;
int Val_Joystick_TopBottom = 510;

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

// Check One Press On BUTTON
bool Press_Button_J1_Status = false;

bool Press_Button_T1_Status = false;
bool Press_Button_T2_Status = false;
bool Press_Button_T3_Status = false;
bool Press_Button_T4_Status = false;

bool Press_Button_R1_Status = false;
bool Press_Button_R2_Status = false;
bool Press_Button_R3_Status = false;


/*-----------------------------------------------------------------*/
/* Statusul comenzilor trimise folosite pentru afisarea pe ecran   */
/*-----------------------------------------------------------------*/

bool VAR_LED_Left = false;			// LED Left Status 
bool VAR_LED_Right = false;			// LED Right Status 
bool VAR_LED_Avarii = false;		// LED Avarii (Cand se activeaza acesta)
// Aceasta variabila influenteaza cele doua variabile: VAR_LED_Left, VAR_LED_Right
bool VAR_LED_Pozitii = false;		// LED Pozitii
bool VAR_LED_FazaLunga = false;		// LED Faza Lunga

bool VAL_MOTOR_Top = false;			// Motor Top
bool VAL_MOTOR_Bottom = false;		// Motor Bottom



// LCD Menu
int LCD_Effect_Time = 0;
bool LCD_Menu_Status = false;
int LCD_Menu_Pos = 1;

// LCD First PAGE
bool LCD_First_Page = true;

// LCD List of Cars
bool LCD_Car_List = false;
int LCD_Car_Time = 0;
int LCD_Car_Pos = 1;


