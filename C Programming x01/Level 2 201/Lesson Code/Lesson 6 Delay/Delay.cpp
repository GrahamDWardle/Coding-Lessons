// Delay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define DELAY_TIME 250
#define TEST_TIME 50000
//Declare proytotype
int WaitKey(int maxDelay);
int main(int argc, char* argv[])
{
	/*int pressed;
	printf("Hello World!\n");
	do
	{
		printf(".");
		pressed = WaitKey(1000);
		if(pressed)
			if (pressed<255 && isprint(pressed))
				printf("%c",pressed);
			else
				printf("\nKey Code %04X\n",pressed);
	}while (27!=pressed);
	*/
    char tmpbuf[128], ampm[] = "AM";
    time_t ltime;
    struct _timeb tstruct,PostTime;
    struct tm *today, *gmt, xmas = { 0, 0, 12, 25, 11, 04 };

    /* Set time zone from TZ environment variable. If TZ is not set,
     * the operating system is queried to obtain the default value 
     * for the variable. 
     */
    _tzset();

    /* Display operating system-style date and time. */
    _strtime( tmpbuf );
    printf( "OS time:\t\t\t\t%s\n", tmpbuf );
    _strdate( tmpbuf );
    printf( "OS date:\t\t\t\t%s\n", tmpbuf );

    /* Get UNIX-style time and display as number and string. */
    time( &ltime );
    printf( "Time in seconds since UTC 1/1/70:\t%ld\n", ltime );
    printf( "UNIX time and date:\t\t\t%s", ctime( &ltime ) );

    /* Display UTC. */
    gmt = gmtime( &ltime );
    printf( "Coordinated universal time:\t\t%s", asctime( gmt ) );

    /* Convert to time structure and adjust for PM if necessary. */
    today = localtime( &ltime );
    if( today->tm_hour > 12 )
    {
   strcpy( ampm, "PM" );
   today->tm_hour -= 12;
    }
    if( today->tm_hour == 0 )  /* Adjust if midnight hour. */
   today->tm_hour = 12;

    /* Note how pointer addition is used to skip the first 11 
     * characters and printf is used to trim off terminating 
     * characters.
     */
    printf( "12-hour time:\t\t\t\t%.8s %s\n",
       asctime( today ) + 11, ampm );

    /* Print additional time information. */
    _ftime( &tstruct );
    printf( "Plus milliseconds:\t\t\t%u\n", tstruct.millitm );
    printf( "Zone difference in seconds from UTC:\t%u\n", 
             tstruct.timezone );
    printf( "Time zone name:\t\t\t\t%s\n", _tzname[0] );
    printf( "Daylight savings:\t\t\t%s\n", 
             tstruct.dstflag ? "YES" : "NO" );

    /* Make time for noon on Christmas, 1993. */
    if( mktime( &xmas ) != (time_t)-1 )
   printf( "Christmas\t\t\t\t%s\n", asctime( &xmas ) );

    /* Use time structure to build a customized time string. */
    today = localtime( &ltime );

    /* Use strftime to build a customized time string. */
    strftime( tmpbuf, 128,
         "Today is %A, day %d of %B in the year %Y.\n", today );
    printf( tmpbuf );
	printf("Time Wait for any key");
	
	_ftime( &tstruct );
    WaitKey(TEST_TIME);
	_ftime( &PostTime );
    long diff = (PostTime.time) - (tstruct.time);
	diff *= 1000;
	diff += PostTime.millitm - tstruct.millitm; 
    printf( "\nPre -POST test time: %d Ratio %8.6f\n", diff ,(double)diff/(double)TEST_TIME);
    //printf( "Post Time:     %d\n", lPost. );
	printf("Wait for any key");
	getch();
	return 0;

}

int WaitKey(int maxDelay)
{
	maxDelay  /=DELAY_TIME;
	int key = -1;
	do
	{
		if(maxDelay)
		{
			if(kbhit())
			{
				key = getch();
				if (key == 0 || key ==0xe0)
					key = getch()<<8;
			}
			maxDelay--;
			Sleep(DELAY_TIME);
		}
		else
			key = 0;
	}while (key<0);
	return key;
}
