#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"

DWORD WINAPI myThread(void* lpParameter)
{
	char id[2] = "1";
	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;

	if (counter == 5) strcpy(id, "2"); 

	while (counter < 20)
	{
		Sleep(1000);
		counter++;
		printf("\n Counter %s = %d", id, counter);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int z = 0;
	int z2 = 5;
	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)&z, 0, &myThreadID);
	Sleep(500);
	HANDLE myHandle2 = CreateThread(0, 0, myThread, (void*)&z2, 0, &myThreadID);
	Sleep(7000);
	printf("\n Main Process sagt");
	TerminateThread(myHandle, 0);
	TerminateThread(myHandle2, 0);
	getchar();
	return 0;
}
