//////////////////////////////////////////////////////////////////////
String LCD_Empty = "                    ";
String LCD_Text_1 = LCD_Empty;
String LCD_Text_2 = LCD_Empty;
String LCD_Text_3 = LCD_Empty;
String LCD_Text_4 = LCD_Empty;


//////////////////////////////////////////////////////////////////////
void DebugMode_Msg(String text);
void LCD_Setup();
void LCD_Clean();
void LCD_Print(String text_1);
void LCD_Print(String text_1, String text_2);
void LCD_Print(String text_1, String text_2, String text_3);
void LCD_Print(String text_1, String text_2, String text_3, String text_4);


//////////////////////////////////////////////////////////////////////
void LCD_Setup(){
  LCD.begin(20,4);
  LCD.setCursor(0,0); LCD.print("Welcome user!      ");
  LCD.setCursor(0,1); LCD.print("Created by:        ");
  LCD.setCursor(0,2); LCD.print("Aninu Applications ");
  LCD.setCursor(0,3); LCD.print("https://aninu.xyz  ");
  delay(2500);
  DebugMode_Msg("Ecran > Activ.");
}

//////////////////////////////////////////////////////////////////////
void LCD_Clean(){
  LCD.setCursor(0,0);
  LCD_Print(LCD_Empty, LCD_Empty, LCD_Empty, LCD_Empty);
}

void LCD_Print(String text_1){
  LCD_Print(text_1, LCD_Empty, LCD_Empty, LCD_Empty);
}
void LCD_Print(String text_1, String text_2){
  LCD_Print(text_1, text_2, LCD_Empty, LCD_Empty);
}
void LCD_Print(String text_1, String text_2, String text_3){
  LCD_Print(text_1, text_2, text_3, LCD_Empty);
}
void LCD_Print(String text_1, String text_2, String text_3, String text_4){
  if (LCD_Text_1 != text_1){
    LCD_Text_1 = text_1;
    LCD.setCursor(0,0); LCD.print(LCD_Empty);
    LCD.setCursor(0,0); LCD.print(text_1);
  }
  if (LCD_Text_2 != text_2){
    LCD_Text_2 = text_2;
    LCD.setCursor(0,1); LCD.print(LCD_Empty);
    LCD.setCursor(0,1); LCD.print(text_2);
  }
  if (LCD_Text_3 != text_3){
    LCD_Text_3 = text_3;
    LCD.setCursor(0,2); LCD.print(LCD_Empty);
    LCD.setCursor(0,2); LCD.print(text_3);
  }
  if (LCD_Text_4 != text_4){
    LCD_Text_4 = text_4;
    LCD.setCursor(0,3); LCD.print(LCD_Empty);
    LCD.setCursor(0,3); LCD.print(text_4);
  } 
}

void LCD_Effect(int iCol, int iRow, String sText){
	LCD.setCursor(iCol, iRow); 
	LCD.print(sText);
}

