#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"

DWORD WINAPI myThread(void* lpParameter)
{
	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;
	while (counter < 20)
	{
		Sleep(1000);
		counter++;
		printf("\n Counter = %d", counter);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int z = 5;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(  // Создает поток для выполнения в виртуальном адресном пространстве вызывающего процесса
		0,           // Если lpThreadAttributes NULL, дескриптор не может быть унаследован
		0,           // Исходный размер стека в байтах умолчанию(1 мегабайт)
		myThread,    // Указатель на определенную приложением функцию, которую должен выполнить поток. Этот указатель представляет собой начальный адрес потока
		(void*)&z,  // Указатель на переменную, которая должна быть передана потоку
		0,           // Поток запускается сразу после создания
		&myThreadID  // Указатель на переменную, которая получает идентификатор потока
	);
	Sleep(5000);
	printf("\n Main Process sagt");
	TerminateThread(myHandle, 0);
	getchar();
	return 0;
}

