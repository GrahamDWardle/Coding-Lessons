#ifndef CONSOLE_H
#define CONSOLE_H

/* Standard error macro for reporting API errors */ 
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

void SetupConsole(void);
void ClearConsole(void);
void OutputToConsole(char *msg);
void ConsoleXY(int x, int y);
void OutputToConsoleXY(int x, int y,char *msg);
void SetConsoleColour(WORD foreColour,WORD backColour);
void RestoreSavedSettings(void);
//Cursor functions
void ConsoleCursorOn(BOOL On);
void ConsoleCursorSize(int percent);

#endif