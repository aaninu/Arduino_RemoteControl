//////////////////////////////////////////////////////////////////////
#include "Settings.h"
#include "LCD.h"
#include "Radio.h"


//////////////////////////////////////////////////////////////////////
void DebugMode_Setup();
void DebugMode_Msg(String text);
void DebugMode_Msg(String text, int valoare);
void DebugMode_Msg(String text, char* valoare);
void DebugMode_Msg(String text, String valoare);
void DebugMode_Serial();
void Serial_Control(char value);

void Potentiometer_Control();
void Joystick_LeftRight();
void Joystick_TopBottom();

void Buttons_Setup();
void Leds_Setup();
void Buttons_Press();

void APP_LED_Left(bool status);
void APP_LED_Right(bool status);
void APP_LED_Avarii(bool status);
void APP_LED_Pozitii(bool status);
void APP_LED_FazaLunga(bool status);
void APP_MOTOR_Top(bool status);
void APP_MOTOR_Bottom(bool status);

void Control_Option_Menu();
void Control_Save_Car();
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
void DebugMode_Msg(String text, String valoare){
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


/** Serial_Control(char value):
	Send Radio Commands from SERIAL MODE (DebugMode)
*/
void Serial_Control(char value){
  // Semnalizare stanga
  if (value == 'a') APP_LED_Left(true);
  if (value == 'A') APP_LED_Left(false);

  // Semnalizare dreapta
  if (value == 'b') APP_LED_Right(true);
  if (value == 'B') APP_LED_Right(false);

  // Avarii (Left And Right)
  if (value == 'c') APP_LED_Avarii(true);
  if (value == 'C') APP_LED_Avarii(false);

  // Pozitii
  if (value == 'd') APP_LED_Pozitii(true);
  if (value == 'D') APP_LED_Pozitii(false);

  // Faza lunga
  if (value == 'e') APP_LED_FazaLunga(true);
  if (value == 'E') APP_LED_FazaLunga(false);

  // Gilofar
  // if (value == 'f') Radio_Send((char*)"APP_LED_Gil: {True}");
  // if (value == 'F') Radio_Send((char*)"APP_LED_Gil: {False}");
  
  // Control Motor Servo
  // if (value == 'g') Radio_Send((char*)"APP_Ser_Top: {512}");
  // if (value == 'G') Radio_Send((char*)"APP_Ser_Top: {0}");
  
  // Motor (Top)
  if (value == 'h') APP_MOTOR_Top(true);
  if (value == 'H') APP_MOTOR_Top(false);
  
  // Motor (Bpttom)
  if (value == 'i') APP_MOTOR_Bottom(true);
  if (value == 'I') APP_MOTOR_Bottom(false);
 

}


/** Potentiometer_Control():
	Potentiometer Control Rotation
*/
void Potentiometer_Control(){
    Val_Potentiometer = analogRead(PIN_Potentiometer);
    if (OLD_Potentiometer <= Val_Potentiometer-3 || OLD_Potentiometer >= Val_Potentiometer+3){
        OLD_Potentiometer = Val_Potentiometer;

        // Afiseaza pe ecran valoarea potentiometrului
        if (DebugMode_PressButtons) LCD_Print("Potentiometer:", (String)OLD_Potentiometer, "", "DebugMode");
        
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


/** Joystick_LeftRight():
	Joystick Control LEFT <-> RIGHT
*/
void Joystick_LeftRight(){
  Val_Joystick_LeftRight = analogRead(PIN_Joystick_LeftRight);
  if (OLD_Joystick_LeftRight <= Val_Joystick_LeftRight-3 || OLD_Joystick_LeftRight >= Val_Joystick_LeftRight+3){
        OLD_Joystick_LeftRight = Val_Joystick_LeftRight;

        // Verifica directia de miscare
        String Direction = "Center";
        if (OLD_Joystick_LeftRight < 500){
          Direction = "Right";

          APP_LED_Right(true);
          
        }else if (OLD_Joystick_LeftRight > 520){
          Direction = "Left";
        
          APP_LED_Left(true);
          
        }else{
          Direction = "Center";
        
          APP_LED_Left(false);
          APP_LED_Right(false);
        }
        // Afiseaza pe ecran valoarea Joystick Left Right
        if(DebugMode_PressButtons) LCD_Print("Joystick LeftRight:", (String)OLD_Joystick_LeftRight, Direction, "DebugMode");
  }
}


/** Joystick_TopBottom():
	Joystick Control TOP <-> BOTTOM
*/
void Joystick_TopBottom(){
  Val_Joystick_TopBottom = analogRead(PIN_Joystick_TopBottom);
  if (OLD_Joystick_TopBottom <= Val_Joystick_TopBottom-3 || OLD_Joystick_TopBottom >= Val_Joystick_TopBottom+3){
        OLD_Joystick_TopBottom = Val_Joystick_TopBottom;

        // Verifica directia de miscare
        String Direction = "Center";
        if (OLD_Joystick_TopBottom < 500){
          Direction = "Bottom";

          APP_MOTOR_Bottom(true);
          
		}else if (OLD_Joystick_TopBottom > 520){
          Direction = "Top";

          APP_MOTOR_Top(true);
          
        }else{
          Direction = "Center";
          
          APP_MOTOR_Top(false);
          APP_MOTOR_Bottom(false);
        }
        // Afiseaza pe ecran valoarea Joystick Top Bottom
        if (DebugMode_PressButtons) LCD_Print("Joystick TopBottom:", (String)OLD_Joystick_TopBottom, Direction, "DebugMode");       
  }
}


/** Buttons_Setup():
	Buttons Setup PIN MODE
*/
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


/** Leds_Setup():
	LED Setup PIN MODE
*/
void Leds_Setup(){
  pinMode(PIN_Led_1, OUTPUT);
  pinMode(PIN_Led_2, OUTPUT);
}


/** Buttons_Press(): Aceasta face legatura intre User Interface si COD. */
void Buttons_Press(){
	// Joystick Button
	{
		ButtonCheck_1 = digitalRead(PIN_Button_1);
		if (ButtonCheck_1 == HIGH) {
			digitalWrite(PIN_Led_2, LOW);
			Press_Button_J1_Status = false;
		} else {
			digitalWrite(PIN_Led_2, HIGH);
			if (DebugMode_PressButtons) LCD_Print("Joystick Button:", "Pressed", "", "DebugMode");
			
			if (Press_Button_J1_Status == false){
				Press_Button_J1_Status = true;
				Control_Option_Menu();
				Control_Save_Car();
			}
		
		}
	}
	
	// Control Button Top 1
	{
		ButtonCheck_2 = digitalRead(PIN_Button_2);
		if (ButtonCheck_2 == HIGH) {
			digitalWrite(PIN_Led_2, LOW);
			Press_Button_T1_Status = false;
		} else {
			digitalWrite(PIN_Led_2, HIGH);
			if (DebugMode_PressButtons) LCD_Print("Top Bar:", "Button 1", "Pressed", "DebugMode");
			
			if (Press_Button_T1_Status == false){
				Press_Button_T1_Status = true;
				
				// Show / Hide >> Menu Control
				if (LCD_Menu_Status == false){
					LCD_Menu_Status = true;
					LCD_Menu_Pos = 1;
					LCD_First_Page = false;
					LCD_Car_List = false;
				}else{
					LCD_Menu_Status = false;
					LCD_First_Page = true;
					LCD_Car_List = false;
				}
			}
		}
	}
	
	// Control Button Top 2
	{
		ButtonCheck_3 = digitalRead(PIN_Button_3);
		if (ButtonCheck_3 == HIGH) {
			digitalWrite(PIN_Led_2, LOW);
			Press_Button_T2_Status = false;
		} else {
			digitalWrite(PIN_Led_2, HIGH);
			if (DebugMode_PressButtons) LCD_Print("Top Bar:", "Button 2", "Pressed", "DebugMode");
			
			if (Press_Button_T2_Status == false){
				Press_Button_T2_Status = true;
				
				// Show / Hide >> Car List
				if (LCD_Car_List == false){
					LCD_Car_List = true;
					LCD_Car_Pos = 1;
					LCD_First_Page = false;
					LCD_Menu_Status = false;
				}else{
					LCD_Car_List = false;
					LCD_First_Page = true;
					LCD_Menu_Status = false;
				}
			}
		}
	}
	
	// Control Button Top 3
	{
		ButtonCheck_4 = digitalRead(PIN_Button_4);
		if (ButtonCheck_4 == HIGH) {
			digitalWrite(PIN_Led_2, LOW);
			Press_Button_T3_Status = false;
		} else {
			digitalWrite(PIN_Led_2, HIGH);
			if (DebugMode_PressButtons) LCD_Print("Top Bar:", "Button 3", "Pressed", "DebugMode");
			
			if (Press_Button_T3_Status == false){
				Press_Button_T3_Status = true;
				// Function HERE
				
			}
		}
	}
	
	// Control Button Top 4
	{
		ButtonCheck_5 = digitalRead(PIN_Button_5);
		if (ButtonCheck_5 == HIGH) {
			digitalWrite(PIN_Led_2, LOW);
			Press_Button_T4_Status = false;
		} else {
			digitalWrite(PIN_Led_2, HIGH);
			if (DebugMode_PressButtons) LCD_Print("Top Bar:", "Button 4", "Pressed", "DebugMode");
			
			if (Press_Button_T4_Status == false){
				Press_Button_T4_Status = true;
				// Function HERE
				
			}
		}
	}
	
	// Control Button Right 1
	{
		ButtonCheck_6 = digitalRead(PIN_Button_6);
		if (ButtonCheck_6 == HIGH) {
			digitalWrite(PIN_Led_1, LOW);
			Press_Button_R1_Status = false;
		} else {
			digitalWrite(PIN_Led_1, HIGH);
			if (DebugMode_PressButtons) LCD_Print("Right Bar:", "Button 1", "Pressed", "DebugMode");
			
			if (Press_Button_R1_Status == false){
				Press_Button_R1_Status = true;
				LCD_Menu_Pos -= 1;
				if (LCD_Menu_Pos < 1) LCD_Menu_Pos = 1;
				LCD_Car_Pos -= 1;
				if (LCD_Car_Pos < 1) LCD_Car_Pos = 1;
			}
		}
	}
	
	// Control Right Button 2
	{
		ButtonCheck_7 = digitalRead(PIN_Button_7);
		if (ButtonCheck_7 == HIGH) {
			digitalWrite(PIN_Led_1, LOW);
			Press_Button_R2_Status = false;
		} else {
			digitalWrite(PIN_Led_1, HIGH);
			if (DebugMode_PressButtons) LCD_Print("Right Bar:", "Button 2", "Pressed", "DebugMode");
		
			if (Press_Button_R2_Status == false){
				Press_Button_R2_Status = true;
				LCD_Menu_Pos += 1;
				if (LCD_Menu_Pos >= GetCarMaxOption()) LCD_Menu_Pos = GetCarMaxOption();
				LCD_Car_Pos += 1;
				if (LCD_Car_Pos >= MAX_PAGE_CARS) LCD_Car_Pos = MAX_PAGE_CARS - 1;
			}
		}
	}
	
	// Control Button Right 3
	{
		ButtonCheck_8 = digitalRead(PIN_Button_8);
		if (ButtonCheck_8 == HIGH) {
			digitalWrite(PIN_Led_1, LOW);
			Press_Button_R3_Status = false;
		} else {
			digitalWrite(PIN_Led_1, HIGH);
			if (DebugMode_PressButtons) LCD_Print("Right Bar:", "Button 3", "Pressed", "DebugMode");
			
			if (Press_Button_R3_Status == false){
				Press_Button_R3_Status = true;
				// Function HERE
			}
		}
	}
}


/*---------------------------------------------------------------------------------------------------------*/
/* Functii de comunicare intre telecomanda si masina                                                       */
/*---------------------------------------------------------------------------------------------------------*/

/** Trimite comenzi pentru ON/OFF LED Left */
void APP_LED_Left(bool status){
	VAR_LED_Left = status;
	if (status == true) 
		Radio_Send((char*)"APP_LED_Lef: {True}");
	else 
		Radio_Send((char*)"APP_LED_Lef: {False}");
}

/** Trimite comenzi pentru ON/OFF LED Right */
void APP_LED_Right(bool status){
	VAR_LED_Right = status;
	if (status == true) 
		Radio_Send((char*)"APP_LED_Rig: {True}");
	else 
		Radio_Send((char*)"APP_LED_Rig: {False}");
}

/** Trimite comenzi pentru ON/OFF LED Avarii */
void APP_LED_Avarii(bool status){
	VAR_LED_Left = false;
	VAR_LED_Right = false;
	VAR_LED_Avarii = status;
	if (status == true) 
		Radio_Send((char*)"APP_LED_LAR: {True}");
	else 
		Radio_Send((char*)"APP_LED_LAR: {False}");
}

/** Trimite comenzi pentru ON/OFF LED Pozitii */
void APP_LED_Pozitii(bool status){
	VAR_LED_Pozitii = status;
	if (status == true) 
		Radio_Send((char*)"APP_LED_Pos: {True}");
	else 
		Radio_Send((char*)"APP_LED_Pos: {False}");
}

/** Trimite comenzi pentru ON/OFF LED Avarii */
void APP_LED_FazaLunga(bool status){
	VAR_LED_FazaLunga = status;
	if (status == true) 
		Radio_Send((char*)"APP_LED_Faz: {True}");
	else 
		Radio_Send((char*)"APP_LED_Faz: {False}");
}

/** Trimite comenzi pentru ON/OFF Motor Top */
void APP_MOTOR_Top(bool status){
	VAL_MOTOR_Bottom = false;
	VAL_MOTOR_Top = status;
	if (status == true) 
		Radio_Send((char*)"APP_MOT_TOP: {True}");
	else 
		Radio_Send((char*)"APP_MOT_TOP: {False}");
}

/** Trimite comenzi pentru ON/OFF Motor Bottom */
void APP_MOTOR_Bottom(bool status){
	VAL_MOTOR_Top = false;
	VAL_MOTOR_Bottom = status;
	if (status == true) 
		Radio_Send((char*)"APP_MOT_BOT: {True}");
	else 
		Radio_Send((char*)"APP_MOT_BOT: {False}");
}



// LCD MENU
void Control_LCD_Menu_Effect(){
	if (LCD_Menu_Status){
		if (LCD_Effect_Time == 250){
			LCD_Effect(0, LCD_Menu_Pos - 1, " ");
			if (LCD_Menu_Pos < 3) LCD_Effect(0, LCD_Menu_Pos + 1, " ");
			LCD_Effect(0, LCD_Menu_Pos, ">");
		}else if (LCD_Effect_Time == 500){
			LCD_Effect(0, LCD_Menu_Pos - 1, " ");
			if (LCD_Menu_Pos < 3) LCD_Effect(0, LCD_Menu_Pos + 1, " ");
			LCD_Effect(0, LCD_Menu_Pos, " ");
		}else if (LCD_Effect_Time == 750){
			LCD_Effect_Time = -1;
		}
		LCD_Effect_Time += 1;
	}else{
		LCD_Menu_Pos = 0;
		LCD_Effect_Time = 0;
	}
}
void Control_LCD_Menu(){
	if (LCD_Menu_Status){
		String Line_1 = " Optiuni:           ";
		String Line_2 = GetOptionName(PageWithOption[Current_Car_ID][LCD_Menu_Pos][0]);
		String Line_3 = GetOptionName(PageWithOption[Current_Car_ID][LCD_Menu_Pos][1]);
		String Line_4 = GetOptionName(PageWithOption[Current_Car_ID][LCD_Menu_Pos][2]);
		LCD_Print(Line_1, Line_2, Line_3, Line_4);
	}
}
void Control_LCD_First(){
	if (LCD_First_Page){
		String Line_1 = GetCarName();
		LCD_Print(Line_1, "", "", "");
	}
}
void Control_Option_Menu(){
	if (LCD_Menu_Status){
		int PosCODid = 2;
		if (LCD_Menu_Pos == 1) PosCODid = 0;
		else if (LCD_Menu_Pos == 2) PosCODid = 1;
		String COD_Option = PageWithOption[Current_Car_ID][LCD_Menu_Pos][PosCODid];
		String RadioCommand = CarRadioCommand(COD_Option);

		DebugMode_Msg("Control_Option_Menu():", RadioCommand);

	}
}


// LCD Car MENU
void Control_LCD_CarList_Effect(){
	if (LCD_Car_List){
		if (LCD_Car_Time == 250){
			LCD_Effect(0, LCD_Car_Pos - 1, " ");
			if (LCD_Car_Pos < 3) LCD_Effect(0, LCD_Car_Pos + 1, " ");
			LCD_Effect(0, LCD_Car_Pos, ">");
		}else if (LCD_Car_Time == 500){
			LCD_Effect(0, LCD_Car_Pos - 1, " ");
			if (LCD_Car_Pos < 3) LCD_Effect(0, LCD_Car_Pos + 1, " ");
			LCD_Effect(0, LCD_Car_Pos, " ");
		}else if (LCD_Car_Time == 750){
			LCD_Car_Time = -1;
		}
		LCD_Car_Time += 1;
	}else{
		LCD_Car_Pos = 1;
		LCD_Car_Time = 0;
	}
}
void Control_LCD_CarList(){
	if (LCD_Car_List){
		String Line_1 = " Lista cu masini:   ";
		LCD_Print(Line_1, PageWithCars[LCD_Car_Pos][0], PageWithCars[LCD_Car_Pos][1], PageWithCars[LCD_Car_Pos][2]);
	}
}
void Control_Save_Car(){
	if (LCD_Car_List){
		Current_Car_ID = LCD_Car_Pos-1;
		CurrentCar = ControlCar[Current_Car_ID][0];
		LCD_Effect(1, LCD_Car_Pos, ">>>");
		DebugMode_Msg("Control_Save_Car():", CurrentCar);
	}
}

