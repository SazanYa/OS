// Lab_6_Process.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include <tlhelp32.h>т
#include "string.h"
#include <iostream>

using namespace std;

void search()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR filesearch[] = TEXT("C:\\Program Files (x86)\\Google\\Chrome\\Application\\c*.exe");
	// Find the first file in directory
	hFind = FindFirstFile(filesearch, &FindFileData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		printf("Invalid file handle. Error is %u. \n", GetLastError());
	}
	else
	{
		std::wcout << "Found: " << FindFileData.cFileName << '\n';
		// List all the other files in diretory
		while (FindNextFile(hFind, &FindFileData) != 0) 
		{
			std::wcout << "Found: " << FindFileData.cFileName << '\n';
		}
		FindClose(hFind);
	}
	getchar();
	return;
}

void create()
{
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO)); 
	PROCESS_INFORMATION pi; 
	TCHAR buf[] = TEXT("mspaint.exe");
	TCHAR process[] = TEXT("mspaint.exe");
	if (CreateProcess(
		NULL,   
		buf,   
		NULL,   
		NULL,   
		FALSE, 
		0,      
		NULL,   
		NULL,  
		&cif,   
		&pi    
	))
	{
		std::wcout << "Process " << process << " is running!" << endl;
		std::cout << endl;
	}
	else std::wcout << "Error " << '\n';
	getchar();
	return;
}

void findCreate()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	TCHAR buf[] = TEXT("mspaint.exe");
	TCHAR process[] = TEXT("mspaint.exe");
	hFind = FindFirstFile(buf, &FindFileData);
	std::wcout << "Founded process: " << FindFileData.cFileName << '\n';
	if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0,
		NULL, NULL, &cif, &pi))
		std::wcout << "Running with PID:" << pi.dwProcessId << '\n';
	else std::wcout << "Error while creating process" << '\n';

	HANDLE hProcess = GetCurrentProcess(); //Получает псевдо-дескриптор для текущего процесса

	//Get the Process name
	if(NULL != hProcess)
	{
		cout << "Done, closing in 2 seconds" << endl;
		Sleep(2000);
		BOOL result = TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
	}
	else
	{
		std::wcout << "Error while terminating " << '\n';
	}
	getchar();
	return;
}

void processList()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN);
	// Делает снимок указанных процессов, а также кучи, модули и потоки, используемые этими процессами
	HANDLE hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS, // Включает все процессы в системе в моментальном снимке
		0                   // текущий процесс
	); 
	if (hSnapshot)
	{
			PROCESSENTRY32 pe32; // Описывает запись из списка процессов, находящихся в системном адресном пространстве при съемке моментального снимка
			pe32.dwSize = sizeof(PROCESSENTRY32); // Размер структуры в байтах
			if (Process32First(hSnapshot, &pe32)) // Получает информацию о первом процессе, обнаруженном в системном снимке
		{
				do
			{
				std::wcout << "Running ProcName: " << pe32.szExeFile << '\n';
			} while (Process32Next(hSnapshot, &pe32)); // Получает информацию о следующем процессе, записанном в системном снимке
		}
		CloseHandle(hSnapshot);
	}
	getchar();
	return;
}

bool AreaEqual(const TCHAR *a, const TCHAR *b)
{
	while(*a == *b)
	{
		if (*a == TEXT('\0'))
			return true;
		a++; b++;
	}
	return false;
}

bool IsProcessRun(TCHAR* process)
{
	bool RUN;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe);
	if (AreaEqual(pe.szExeFile, process))
	{
		RUN = true;
		return RUN;
	}
	else
		RUN = false;
	while(Process32Next(hSnapshot, &pe))
	{
		if (AreaEqual(pe.szExeFile, process))
		{
			RUN = true;
			return RUN;
		}
		else
			RUN = false;
	}
	return RUN;
}

void check(TCHAR* process)
{
	if(IsProcessRun(process))
	{
		wcout << "Process " << process << " is running " << endl;
	}
	else
	{
		wcout << "Process " << process << " is NOT running " << endl;
	}
	cout << endl;
	return;
}

void findCreateCheck() {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	TCHAR buf[] = TEXT("C:\\Windows\\system32\\mspa*.exe");
	hFind = FindFirstFile(buf, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("File is not found. Error is %u. \n", GetLastError());
	}
	else
	{
		std::wcout << "Found: " << FindFileData.cFileName << '\n';
		if (CreateProcess(NULL, FindFileData.cFileName, NULL, NULL, FALSE, 0,
			NULL, NULL, &cif, &pi))
		{
			if (IsProcessRun(FindFileData.cFileName))
			{
				wcout << "Process " << FindFileData.cFileName << " is running with PID:" << pi.dwProcessId << endl;
			}
			else
			{
				wcout << "Process " << FindFileData.cFileName << " is running NOT running" << endl;

			}
		}	
		else std::wcout << "Error while creating process" << endl;
		// List all the other files in diretory
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			std::wcout << "Found: " << FindFileData.cFileName << endl;
		}
		FindClose(hFind);
	}
	cout << endl;
	getchar();
	return;
}

int main()
{
	TCHAR processName[] = TEXT("chrome.exe");
	int choice;
	while(true)
	{
		cout << "1 - Find process" << endl;
		cout << "2 - Create process" << endl;
		cout << "3 - Find & create process" << endl;
		cout << "4 - List of process" << endl;
		cout << "5 - Is process running?" << endl;
		cout << "6 - Find & create & check" << endl;
		cout << "0 - Exit" << endl;
		cout << "Choose: ";
		cin >> choice;

		switch(choice)
		{
		case 0: exit(0); break;
		case 1: search(); break;
		case 2: create(); break;
		case 3: findCreate(); break;
		case 4: processList(); break;
		case 5: check(processName); break;
		case 6: findCreateCheck(); break;
		}

	}
}

