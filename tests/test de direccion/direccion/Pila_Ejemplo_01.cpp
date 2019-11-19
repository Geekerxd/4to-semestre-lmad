#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#define _SECOND 10000000

typedef struct _MYDATA {
	TCHAR *szText;
	DWORD dwValue;
} MYDATA;


VOID CALLBACK TimerAPCProc(
	LPVOID lpArg,               // Data value.
	DWORD dwTimerLowValue,      // Timer low value.
	DWORD dwTimerHighValue) {  // Timer high value.

	MYDATA *pMyData = (MYDATA *)lpArg;

	printf("Message: %s\nValue: %d\n\n", pMyData->szText,
		pMyData->dwValue);
	MessageBeep(0);

}


void main(void) {

	HANDLE          hTimer;
	BOOL            bSuccess;
	__int64         qwDueTime;
	LARGE_INTEGER   liDueTime;
	MYDATA          MyData;
	TCHAR           szError[255];

	char data[18]= "This is my data." ;
	MyData.szText = { data };
	MyData.dwValue = 100;

	if (hTimer = CreateWaitableTimer(NULL,FALSE,"MyTimer")) { 
			// Create a negative 64-bit integer that will be used to
			// signal the timer 5 seconds from now.
			qwDueTime = -5 * _SECOND;
			// Copy the relative time into a LARGE_INTEGER.
			liDueTime.LowPart = (DWORD)(qwDueTime & 0xFFFFFFFF);
			liDueTime.HighPart = (LONG)(qwDueTime >> 32);
			bSuccess = SetWaitableTimer(
				hTimer,                 // Handle to the timer object.
				&liDueTime,             // When timer will become signaled.
				2000,                   // Periodic timer interval of 2 seconds.
				TimerAPCProc,           // Completion routine.
				&MyData,                // Argument to the completion routine.
				FALSE);                // Do not restore a suspended system.

			if (bSuccess) {

				for (; MyData.dwValue < INFINITE; MyData.dwValue += 100) {

					SleepEx(
						INFINITE,           // Wait forever.
						TRUE);             // IMPORTANT!!! The thread must be in an
											// alertable state to process the APC.
				}

			}
			

		

	}
	

}











