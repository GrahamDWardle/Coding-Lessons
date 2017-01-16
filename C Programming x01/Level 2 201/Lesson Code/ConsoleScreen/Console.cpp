#include "StdAFx.h"
#include "Console.h"

//Global variables read and set for console
CONSOLE_SCREEN_BUFFER_INFO csbi;
CONSOLE_SCREEN_BUFFER_INFO Save_csbi;
CONSOLE_CURSOR_INFO CursorInfo;
CONSOLE_CURSOR_INFO Save_CursorInfo;
HANDLE hStdOutput =NULL;

void SetupConsole(void)
{
	if(hStdOutput)
	{
		printf("\n\nConsole already Setup\n", GetLastError());
		getch();
	}
	else
	{
		// Find the console output Handle
		hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		//Read in Screen Info
		if(!GetConsoleScreenBufferInfo(hStdOutput, &csbi))
			printf("GetConsoleScreenBufferInfo failed: %d\n", GetLastError());
		//Read in Screen Info to save for restore
		else if (!GetConsoleScreenBufferInfo(hStdOutput, &Save_csbi))
			printf("GetConsoleScreenBufferInfo failed: %d for Save Results\n", GetLastError());
		else if(!GetConsoleCursorInfo(hStdOutput,&Save_CursorInfo))
			printf("GetConsoleCursorInfo failed: %d\n",GetLastError());
		else if(!GetConsoleCursorInfo(hStdOutput,&CursorInfo))
			printf("GetConsoleCursorInfo failed: %d for Saved Results\n", GetLastError());
	}
}
// Clear Screen for a console Screen
void ClearConsole(void)
{
    // here's where we'll home the cursor */ 
	const COORD ScreenHome = { 0, 0 };
    BOOL bSuccess=FALSE;
    DWORD cCharsWritten=0;
	// number of character cells in the current buffer  
    DWORD dwConSize=0;

    //get the number of character cells in the current buffer 
    bSuccess = GetConsoleScreenBufferInfo(hStdOutput,&csbi);
    PERR(bSuccess,"GetConsoleScreenBufferInfo");
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    //fill the entire screen with blanks 
    bSuccess = FillConsoleOutputCharacter(hStdOutput,(TCHAR)' ',
       dwConSize,ScreenHome,&cCharsWritten);
    PERR(bSuccess,"FillConsoleOutputCharacter");

    /* get the current text attribute */ 
    bSuccess = GetConsoleScreenBufferInfo(hStdOutput,&csbi);
    PERR(bSuccess,"ConsoleScreenBufferInfo");

    /* now set the buffer's attributes accordingly */ 
    bSuccess = FillConsoleOutputAttribute(hStdOutput,csbi.wAttributes,
       dwConSize, ScreenHome, &cCharsWritten);
    PERR(bSuccess,"FillConsoleOutputAttribute");

    /* put the cursor at (0, 0) */ 
    bSuccess = SetConsoleCursorPosition(hStdOutput,ScreenHome);
    PERR(bSuccess,"SetConsoleCursorPosition");
    return;
} 
void SetConsoleColour(WORD foreColour,WORD backColour)
{
	SetConsoleTextAttribute(hStdOutput,(WORD)((backColour<<4)|foreColour));
}
void OutputToConsole(char *msg)
{
	printf("%s",msg);
}
// Put the cursor to postion (x,y)
void ConsoleXY(int x, int y)
{
	csbi.dwCursorPosition.X=x;
	csbi.dwCursorPosition.Y=y;
	SetConsoleCursorPosition(hStdOutput, csbi.dwCursorPosition );
}
//Display text at the (x,y) screen coordinates
void OutputToConsoleXY(int x, int y,char *msg)
{
	ConsoleXY(x, y);
	OutputToConsole(msg);
}
//Allow the restoration of the Screen settings
void RestoreSavedSettings(void)
{
	SetConsoleTextAttribute(hStdOutput, Save_csbi.wAttributes);
	ClearConsole();
	SetConsoleCursorInfo(hStdOutput,&Save_CursorInfo);
	SetConsoleCursorPosition(hStdOutput, Save_csbi.dwCursorPosition );
}
// Turn on or off the Cursor
void ConsoleCursorOn(BOOL On)
{
	CursorInfo.bVisible = On;
	SetConsoleCursorInfo(hStdOutput,&CursorInfo);
}
void ConsoleCursorSize(int percent)
{
	//keep cursor size in range 1 to 100 percent
	if(percent<1) 
		percent = 1;
	if(percent>100)
		percent = 100;
	CursorInfo.dwSize= percent;
	SetConsoleCursorInfo(hStdOutput,&CursorInfo);
}

