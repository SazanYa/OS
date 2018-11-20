#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"

int x;

DWORD WINAPI Reader(void* lpParameter)
{
	int* counterp = new int();
	counterp = (int*)lpParameter;
	while (true) {
		int counter = *counterp;
		printf("\n Read x = %d", counter);
		Sleep(400);
	}
	return 0;
}


DWORD WINAPI Writer(void* lpParameter)
{
	DWORD readerID;
	HANDLE readerHandle = CreateThread(0, 0, Reader, (void*)&x, CREATE_SUSPENDED, &readerID);

	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;
	
	while (counter < 5)
	{
		Sleep(300);
		counter++;
		x = counter;
		printf("\n Write x = %d", x);
		ResumeThread(readerHandle);
	}
	TerminateThread(readerHandle, 0);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int z = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, Writer, (void*)&z, 0, &myThreadID);
	Sleep(6000);
	printf("\n Main Process sagt");
	TerminateThread(myHandle, 0);
	getchar();
	return 0;
}
