// ConsoleScreen.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Console.h"

void DisplayWait(void);
int main(int argc, char* argv[])
{
	//Setup the variables used for Console interaction
	SetupConsole();
	//Clear the console
	ClearConsole();
	OutputToConsole("Hello World!");
	ConsoleXY(10,10);
	OutputToConsole("Hello World!");
	//set Dark Blue on White
	SetConsoleColour(1,15);
	//No Flashing Cursor
	ConsoleCursorOn(FALSE);
	DisplayWait();
	
	//Colour kept from the previous colour change
	ClearConsole();
	//Position should be now 0,0
	OutputToConsole("Hello World!");
	//Flashing Cursor on to 100%
	ConsoleCursorOn(TRUE);
	ConsoleCursorSize(100);
	//Set Red on Blue
	SetConsoleColour(12,9);
	DisplayWait();
	RestoreSavedSettings();
	DisplayWait();
	
	return 0;
}
void DisplayWait(void)
{
	OutputToConsoleXY(20,1,"======================");
	OutputToConsoleXY(20,2,"| Waiting for a key! |");
	OutputToConsoleXY(20,3,"======================");
	ConsoleXY(20,20);
	OutputToConsole("Press a key to continue");
	getch();
}
