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
TimedAction Timed_Potentiometer_Servo = TimedAction(10, Potentiometer_Servo);
TimedAction Timed_Joystick_LeftRight = TimedAction(10, Joystick_LeftRight);
TimedAction Timed_Joystick_TopBottom = TimedAction(10, Joystick_TopBottom);
TimedAction Timed_Buttons_Press = TimedAction(1, Buttons_Press);


void loop(){
  Timed_DebugMode_Serial.check();
  Timed_Radio_Receiver.check();

  Timed_Potentiometer_Servo.check();

  Timed_Joystick_LeftRight.check();
  Timed_Joystick_TopBottom.check();
  Timed_Buttons_Press.check();

}