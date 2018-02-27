//////////////////////////////////////////////////////////////////////
#include "Settings.h"
#include "LCD.h"
#include "Radio.h"


//////////////////////////////////////////////////////////////////////
void DebugMode_Setup();
void DebugMode_Msg(String text);
void DebugMode_Msg(String text, int valoare);
void DebugMode_Msg(String text, char* valoare);
void DebugMode_Serial();
void Serial_Control(char value);

void Potentiometer_Servo();
void Joystick_LeftRight();
void Joystick_TopBottom();

void Buttons_Setup();
void Leds_Setup();
void Buttons_Press();
//////////////////////////////////////////////////////////////////////
void DebugMode_Setup(){
  if (DebugMode){
    Serial.begin(19200);
    DebugMode_Msg("Telecomanda > Activa.");
  }
}

void DebugMode_Msg(String text){
  if (DebugMode){
    Serial.print("[DebugMode]: ");
    Serial.println(text);
  }
}
void DebugMode_Msg(String text, int valoare){
  if (DebugMode){
    Serial.print("[DebugMode]: ");
    Serial.print(text);
    Serial.print(" {");
    Serial.print(valoare);
    Serial.println("}");
  }
}
void DebugMode_Msg(String text, char* valoare){
  if (DebugMode){
    Serial.print("[DebugMode]: ");
    Serial.print(text);
    Serial.print(" {");
    Serial.print(valoare);
    Serial.println("}");
  }
}

void DebugMode_Serial(){
  if (Serial.available() > 0){
    DebugSerialValue = Serial.read();
    DebugMode_Msg("Serial.read():", DebugSerialValue);
    Serial_Control((char)DebugSerialValue);
  }
}

void Serial_Control(char value){
  // Semnalizare stanga
  if (value == 'a') Radio_Send((char*)"APP_LED_Lef: {True}");
  if (value == 'A') Radio_Send((char*)"APP_LED_Lef: {False}");

  // Semnalizare dreapta
  if (value == 'b') Radio_Send((char*)"APP_LED_Rig: {True}");
  if (value == 'B') Radio_Send((char*)"APP_LED_Rig: {False}");

  // Avarii (Left And Right)
  if (value == 'c') Radio_Send((char*)"APP_LED_LAR: {True}");
  if (value == 'C') Radio_Send((char*)"APP_LED_LAR: {False}");

  // Pozitii
  if (value == 'd') Radio_Send((char*)"APP_LED_Pos: {True}");
  if (value == 'D') Radio_Send((char*)"APP_LED_Pos: {False}");

  // Faza lunga
  if (value == 'e') Radio_Send((char*)"APP_LED_Faz: {True}");
  if (value == 'E') Radio_Send((char*)"APP_LED_Faz: {False}");

  // Gilofar
  if (value == 'f') Radio_Send((char*)"APP_LED_Gil: {True}");
  if (value == 'F') Radio_Send((char*)"APP_LED_Gil: {False}");

  if (value == 'g') Radio_Send((char*)"APP_Ser_Top: {512}");
  if (value == 'G') Radio_Send((char*)"APP_Ser_Top: {0}");
  
}

void Potentiometer_Servo(){
    Val_Potentiometer = analogRead(PIN_Potentiometer);
    if (OLD_Potentiometer <= Val_Potentiometer-3 || OLD_Potentiometer >= Val_Potentiometer+3){
        OLD_Potentiometer = Val_Potentiometer;

        // Afiseaza pe ecran valoarea potentiometrului
        if (DebugMode){
          LCD_Print("Potentiometer:", (String)OLD_Potentiometer, "", "DebugMode");
        }
        
        // Trimite comanda catre device
        if (Radio_Status){
          char command_1[] = "APP_Ser_Top: {";
          char command_2[] = "}";
          char val_pot_char[5];
          itoa (Val_Potentiometer, val_pot_char, 10);
          strcat(command_1,val_pot_char);
          strcat(command_1,command_2);
          Radio_Send(command_1);
        }
    }
}

void Joystick_LeftRight(){
  Val_Joystick_LeftRight = analogRead(PIN_Joystick_LeftRight);
  if (OLD_Joystick_LeftRight <= Val_Joystick_LeftRight-3 || OLD_Joystick_LeftRight >= Val_Joystick_LeftRight+3){
        OLD_Joystick_LeftRight = Val_Joystick_LeftRight;

        // Verifica directia de miscare
        String Direction = "Center";
        if (OLD_Joystick_LeftRight < 510)
          Direction = "Right";
        else if (OLD_Joystick_LeftRight > 520)
          Direction = "Left";
        else
          Direction = "Center";
        
        // Afiseaza pe ecran valoarea Joystick Left Right
        if (DebugMode){
          LCD_Print("Joystick LeftRight:", (String)OLD_Joystick_LeftRight, Direction, "DebugMode");
        }
  }
}

void Joystick_TopBottom(){
  Val_Joystick_TopBottom = analogRead(PIN_Joystick_TopBottom);
  if (OLD_Joystick_TopBottom <= Val_Joystick_TopBottom-3 || OLD_Joystick_TopBottom >= Val_Joystick_TopBottom+3){
        OLD_Joystick_TopBottom = Val_Joystick_TopBottom;

        // Verifica directia de miscare
        String Direction = "Center";
        if (OLD_Joystick_TopBottom < 510)
          Direction = "Bottom";
        else if (OLD_Joystick_TopBottom > 520)
          Direction = "Top";
        else
          Direction = "Center";
          
        // Afiseaza pe ecran valoarea Joystick Top Bottom
        if (DebugMode){
          LCD_Print("Joystick TopBottom:", (String)OLD_Joystick_TopBottom, Direction, "DebugMode");
        }        
  }
}

void Buttons_Setup(){
  pinMode(PIN_Button_1, INPUT);
  
  pinMode(PIN_Button_2, INPUT_PULLUP);
  pinMode(PIN_Button_3, INPUT_PULLUP);
  pinMode(PIN_Button_4, INPUT_PULLUP);
  pinMode(PIN_Button_5, INPUT_PULLUP);
  pinMode(PIN_Button_6, INPUT_PULLUP);
  pinMode(PIN_Button_7, INPUT_PULLUP);
  pinMode(PIN_Button_8, INPUT_PULLUP);
}

void Leds_Setup(){
  pinMode(PIN_Led_1, OUTPUT);
  pinMode(PIN_Led_2, OUTPUT);
}

void Buttons_Press(){
  
  // Joystick Button
  ButtonCheck_1 = digitalRead(PIN_Button_1);
  if (ButtonCheck_1 == HIGH) {
    digitalWrite(PIN_Led_2, LOW);
  } else {
    digitalWrite(PIN_Led_2, HIGH);
    LCD_Print("Joystick Button:", "Pressed", "", "DebugMode");
  }

  // Top Button 1
  ButtonCheck_2 = digitalRead(PIN_Button_2);
  if (ButtonCheck_2 == HIGH) {
    digitalWrite(PIN_Led_2, LOW);
  } else {
    digitalWrite(PIN_Led_2, HIGH);
    LCD_Print("Top Bar:", "Button 1", "Pressed", "DebugMode");
  }

  // Top Button 2
  ButtonCheck_3 = digitalRead(PIN_Button_3);
  if (ButtonCheck_3 == HIGH) {
    digitalWrite(PIN_Led_2, LOW);
  } else {
    digitalWrite(PIN_Led_2, HIGH);
    LCD_Print("Top Bar:", "Button 2", "Pressed", "DebugMode");
  }
 
  // Top Button 3
  ButtonCheck_4 = digitalRead(PIN_Button_4);
  if (ButtonCheck_4 == HIGH) {
    digitalWrite(PIN_Led_2, LOW);
  } else {
    digitalWrite(PIN_Led_2, HIGH);
    LCD_Print("Top Bar:", "Button 3", "Pressed", "DebugMode");
  }
  
  // Top Button 4
  ButtonCheck_5 = digitalRead(PIN_Button_5);
  if (ButtonCheck_5 == HIGH) {
    digitalWrite(PIN_Led_2, LOW);
  } else {
    digitalWrite(PIN_Led_2, HIGH);
    LCD_Print("Top Bar:", "Button 4", "Pressed", "DebugMode");
  }

  // Right Button 1
  ButtonCheck_6 = digitalRead(PIN_Button_6);
  if (ButtonCheck_6 == HIGH) {
    digitalWrite(PIN_Led_1, LOW);
  } else {
    digitalWrite(PIN_Led_1, HIGH);
    LCD_Print("Right Bar:", "Button 1", "Pressed", "DebugMode");
  }
  
  // Right Button 2
  ButtonCheck_7 = digitalRead(PIN_Button_7);
  if (ButtonCheck_7 == HIGH) {
    digitalWrite(PIN_Led_1, LOW);
  } else {
    digitalWrite(PIN_Led_1, HIGH);
    LCD_Print("Right Bar:", "Button 2", "Pressed", "DebugMode");
  }
  
  // Right Button 3
  ButtonCheck_8 = digitalRead(PIN_Button_8);
  if (ButtonCheck_8 == HIGH) {
    digitalWrite(PIN_Led_1, LOW);
  } else {
    digitalWrite(PIN_Led_1, HIGH);
    LCD_Print("Right Bar:", "Button 3", "Pressed", "DebugMode");
  }
}
