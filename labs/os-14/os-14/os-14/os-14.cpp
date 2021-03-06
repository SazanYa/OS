// os-14.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "Windows.h"

int choose;

void CreateDir();
void Text();
void Copy();
void Deleted();
void Move();
void Read();
void Menu();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu();
	std::cout << "Ввод: ";
	do
	{
		std::cin >> choose;
		switch (choose)
		{
		case 1:
			CreateDir();
			break;
		case 2:
			Text();
			break;
		case 3:
			Copy();
			break;
		case 4:
			Deleted();
			break;
		case 5:
			Move();
			break;
		case 6:
			Read();
			break;
		case 7:
			Menu();
			break;
		}
		std::cout << "____________________________________________________________" << std::endl;
		std::cout << "Ввод: ";
	} while (choose != 0);

	return 0;
}

void Menu()
{
	std::cout << "1 - создание двух каталогов " << std::endl;
	std::cout << "2 - создание текстового файла в 1м каталоге" << std::endl;
	std::cout << "3 - копирование файла из 1го каталога во 2й " << std::endl;
	std::cout << "4 - удаление файла из 1го каталога " << std::endl;
	std::cout << "5 - переименование файла во 2м каталоге" << std::endl;
	std::cout << "6 - чтение его содержимого файла во 2м каталоге" << std::endl;
	std::cout << "7 - меню" << std::endl;
	std::cout << "0 - выход" << std::endl;
	std::cout << "____________________________________________________________" << std::endl;
}

void CreateDir() 
{
	TCHAR Buffer2[] = TEXT("d:\\temp\\1");
	TCHAR Buffer3[] = TEXT("d:\\temp\\2");

	CreateDirectory(Buffer2, NULL);
	CreateDirectory(Buffer3, NULL);
}

void Text()
{
	TCHAR Buffer[256] = TEXT("Created");
	HANDLE hOut;
	DWORD dwNumberOfBytes;

	TCHAR stdPath[30] = TEXT("d:\\temp\\1\\file.txt");
	hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOut == INVALID_HANDLE_VALUE) {
		std::cout << "Ошибка %x \n" << std::endl;
		getchar();
	}

	else
	{
		WriteFile(hOut, Buffer, 256, &dwNumberOfBytes, NULL);
		std::cout << "Создано и записано" << std::endl;
		getchar();
		CloseHandle(hOut);
	}
}

void Copy() 
{
	TCHAR Buffer[256];
	HANDLE hIn;
	DWORD dwNumberOfBytes;
	FILE* fp;

	TCHAR filea[30] = TEXT("d:\\temp\\1\\file.txt");
	TCHAR fileb[30] = TEXT("d:\\temp\\2\\file.txt");

	BOOL pr = CopyFile(filea, fileb, NULL);
	if (pr)
	{
		std::cout << "Скопировано" << std::endl;
		getchar();
	}
	else
	{
		std::cout << "Не скопировано" << std::endl;
		getchar();
	}
}

void Deleted() 
{
	TCHAR Buffer[256];
	HANDLE hIn;
	DWORD dwNumberOfBytes;

	TCHAR file[30] = TEXT("d:\\temp\\1\\file.txt");
	BOOL pr = DeleteFile(file);
	if (pr)
	{
		std::cout << "Удалено" << std::endl;
		getchar();
	}
	else
	{
		std::cout << "Не удалено" << std::endl;
		getchar();
	}
}

void Move() 
{
	TCHAR Buffer[256];
	HANDLE hIn;
	DWORD dwNumberOfBytes;
	FILE* fp;
	BOOL pr2 = 0;

	TCHAR fileA[30] = TEXT("d:\\temp\\2\\file.txt");
	TCHAR fileB[30] = TEXT("d:\\temp\\2\\newfile.txt");

	BOOL pr = MoveFile(fileA, fileB);
	if (pr)
	{
		std::cout << "Переименовано" << std::endl;
		getchar();

	}
	else
	{
		std::cout << "Не переименовано" << std::endl;
		getchar();
	}
}

void Read()
{
	TCHAR Buffer[256];
	HANDLE hIn;
	DWORD dwNumberOfBytes;
	FILE* fp;

	TCHAR file[30] = TEXT("d:\\temp\\2\\newfile.txt");

	hIn = CreateFile(file, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hIn == INVALID_HANDLE_VALUE) {
		std::cout << "Данные не прочитаны" << std::endl;
		getchar();
	}

	else
	{
		ReadFile(hIn, Buffer, 256, &dwNumberOfBytes, NULL);
		std::cout << "Данные успешно прочитаны: " << std::endl;
		std::wcout << Buffer << std::endl;
		getchar();
		CloseHandle(hIn);
	}
}

