// Car Functions:


// Options
#define MAX_MENU 5
#define MAX_OPTION 2
String ControlMenu[MAX_MENU][MAX_OPTION] = {
	{"APP_OPTION_NULL", " Nu exista optiuni! "},
	{"APP_LED_POZITII", " Pozitii            "},
	{"APP_LED_FAZALUN", " Faza Lunga         "},
	{"APP_LED_AVARII_", " Avarii             "},
	{"APP_LED_GILOFAR", " Gilogar            "},
};

/** CAR FULL LIST AND PAGE */
#define MAX_CAR 6
#define MAX_CAR_OPTION 2
String ControlCar[MAX_CAR][MAX_CAR_OPTION] = {
	{"CAR_v1.0", " CAR v1.0 >> TIR    "},
	{"CAR_v2.0", " CAR v2.0 >> BUGGY  "},
	{"CAR_v3.0", " CAR v3.0 >> AUTO   "},
	{"CAR_v4.0", " CAR v4.0 >> DEV    "},
	{"CAR_v5.0", " CAR v5.0 >> Test   "},
	{"CAR_v6.0", " CAR v6.0 >> Best   "},
};
#define MAX_PAGE_CARS 7
String PageWithCars[MAX_PAGE_CARS][3] = {
	{"", "", ""},
	{ControlCar[0][1], ControlCar[1][1], ControlCar[2][1]},
	{ControlCar[0][1], ControlCar[1][1], ControlCar[2][1]},
	{ControlCar[0][1], ControlCar[1][1], ControlCar[2][1]},
	{ControlCar[1][1], ControlCar[2][1], ControlCar[3][1]},
	{ControlCar[2][1], ControlCar[3][1], ControlCar[4][1]},
	{ControlCar[3][1], ControlCar[4][1], ControlCar[5][1]},
};
////////////////////////////////////////////////////////////////////////

// Optiuni pentru >> "CAR_v1.0"
String Car_V1_0[5][3] = {
	{"", "", ""},
	{ControlMenu[1][0], ControlMenu[2][0], ControlMenu[3][0]},
	{ControlMenu[1][0], ControlMenu[2][0], ControlMenu[3][0]},
	{ControlMenu[1][0], ControlMenu[2][0], ControlMenu[3][0]},
	{ControlMenu[2][0], ControlMenu[3][0], ControlMenu[4][0]},
};

// Optiuni pentru >> "CAR_v2.0"
String Car_V2_0[5][3] = {
	{"", "", ""},
	{ControlMenu[1][0], ControlMenu[2][0], ControlMenu[3][0]},
	{ControlMenu[1][0], ControlMenu[2][0], ControlMenu[3][0]},
	{ControlMenu[1][0], ControlMenu[2][0], ControlMenu[3][0]},
};

// Optiuni pentru >> "CAR_v4.0"
String Car_V4_0[5][3] = {{"", "", ""}, {ControlMenu[0][0], "", ""}};

String PageWithOption[MAX_CAR][5][3] = {
	Car_V1_0,
	Car_V2_0,
	Car_V2_0,
	Car_V4_0,
	Car_V4_0,
	Car_V4_0,
};

int CarMaxOption[MAX_CAR] = {4, 3, 3, 1, 1, 1};

// Start with this car
int Current_Car_ID = 2;
String CurrentCar = ControlCar[Current_Car_ID][0];

/** Get Current Car Name */
String GetCarName(){
	for (int i = 0; i < MAX_CAR; i++)
		if (ControlCar[i][0] == CurrentCar)
			return ControlCar[i][1];
	return "UnknownCar";
}

/** Get Number of options for current car */
int GetCarMaxOption(){
	return CarMaxOption[Current_Car_ID];
}

/** Get Option Name By String COD */
String GetOptionName(String sCode){
	if (sCode == "") return "";
	for(int i = 0; i < MAX_MENU; i++)
		if (ControlMenu[i][0] == sCode)
			return ControlMenu[i][1];
	return "UnknownOption";
}

/** List with Radio Commands */
String RadioCommands[9][2] = {
	{"APP_OPTION_NULL", ""},
	{"APP_LED_POZITII", "APP_LED_Pos"},
	{"APP_LED_FAZALUN", "APP_LED_Faz"},
	{"APP_LED_AVARII_", "APP_LED_LAR"},
	{"APP_LED_GILOFAR", ""},
	{"APP_LED_LEFT___", "APP_LED_Lef"},
	{"APP_LED_RIGHT__", "APP_LED_Rig"},
	{"APP_MOTOR_TOP__", "APP_MOT_TOP"},
	{"APP_MOTOR_BOTTO", "APP_MOT_BOT"},
};

String GetRadioCommand(String sCode){
	if (sCode == "") return "";
	for (int i = 0; i < 9; i++)
		if (RadioCommands[i][0] == sCode)
			return RadioCommands[i][1];
	return "";
}

String CarRadioCommand(String sCode){
	String RadioCommand = GetRadioCommand(sCode);
	if (RadioCommand == "") return "";
	String COD_Car = CurrentCar;
	COD_Car = COD_Car.substring(3,6);
	COD_Car.replace("_", "A");
	RadioCommand.replace("APP", COD_Car);
	return RadioCommand;
}

