// Transmitator

#include "Functions.h"

void setup() {
  DebugMode_Setup();
  LCD_Setup();
  Radio_Setup();

  Buttons_Setup();
  Leds_Setup();
}

TimedAction Timed_DebugMode_Serial = TimedAction(1, DebugMode_Serial);
TimedAction Timed_Radio_Receiver = TimedAction(1, Radio_Receiver);
TimedAction Timed_Potentiometer_Control = TimedAction(10, Potentiometer_Control);
TimedAction Timed_Joystick_LeftRight = TimedAction(10, Joystick_LeftRight);
TimedAction Timed_Joystick_TopBottom = TimedAction(10, Joystick_TopBottom);
TimedAction Timed_Buttons_Press = TimedAction(1, Buttons_Press);

TimedAction Timed_Control_LCD_Menu_Effect = TimedAction(1, Control_LCD_Menu_Effect);
TimedAction Timed_Control_LCD_Menu = TimedAction(1, Control_LCD_Menu);
TimedAction Timed_Control_LCD_First = TimedAction(1, Control_LCD_First);

TimedAction Timed_Control_LCD_CarList = TimedAction(1, Control_LCD_CarList);
TimedAction Timed_Control_LCD_CarList_Effect = TimedAction(1, Control_LCD_CarList_Effect);

void loop(){
  Timed_DebugMode_Serial.check();
  Timed_Radio_Receiver.check();

  Timed_Potentiometer_Control.check();

  Timed_Joystick_LeftRight.check();
  Timed_Joystick_TopBottom.check();
  Timed_Buttons_Press.check();
  
  Timed_Control_LCD_Menu_Effect.check();
  Timed_Control_LCD_Menu.check();
  Timed_Control_LCD_First.check();
  
  Timed_Control_LCD_CarList.check();
  Timed_Control_LCD_CarList_Effect.check();
  
}
