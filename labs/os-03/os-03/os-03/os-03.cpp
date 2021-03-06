// os-03.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

using namespace std;

void Print(int x, int y, char* str, int color = 0xD4)
{
	HANDLE consoleOutput;
	COORD cursorPos;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	cursorPos.X = x;
	cursorPos.Y = y;

	SetConsoleCursorPosition(consoleOutput, cursorPos);
	SetConsoleTextAttribute(consoleOutput, color);

	std::cout << str << std::endl;

	SetConsoleTextAttribute(consoleOutput, 0x0F);
}

void PrintTable(char columns[][10], int count_columns, char lines[][10][10], int count_lines)
{
	char* line = new char[64]{ "\t\t\t\t" };
	char* column = new char[20]{ "  " };

	int column_width = 15;
	int table_width = column_width * count_columns;

	Print(0, 0, line);

	for (int i = 0, l = 1; i < count_lines + 1; i++, l+=2)
	{
		Print(0, l + 1, line);
		Print(table_width, l, column);

		for (int k = 0, width = 5; k < count_columns; k++, width += column_width)
		{
			Print(width - 5, l, column);

			if ((l -1) == 0)
				Print(width, 1, columns[k], 0x04);
			else
				Print(width, l, lines[i - 1][k], 0x04);
		}
	}

	std::cout << std::endl;

	delete[] line;
	delete[] column;
}

void PrintRhombus()
{
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;

	for (int i = 1, x = 15, y = 5; i <= 8; i += 2, y++, x--)
	{
		cursor.X = x;
		cursor.Y = y;
		SetConsoleCursorPosition(consoleOutput, cursor);
		SetConsoleTextAttribute(consoleOutput, 0x2B);

		std::cout << std::setfill(' ') << std::setw(i) << '\n';
	}

	for (int i = 6, x = 12, y = 8; i >= 2; i -= 2, y++, x++)
	{
		cursor.X = x;
		cursor.Y = y;
		SetConsoleCursorPosition(consoleOutput, cursor);
		SetConsoleTextAttribute(consoleOutput, 0x2B);

		std::cout << std::setfill(' ') << std::setw(i + 1) << '\n';
	}

	SetConsoleTextAttribute(consoleOutput, 0x0F);
}

int main()
{
	setlocale(NULL, "");

	char columns[][10] = { "Фамилия", "Группа" };
	char lines[][10][10] = { { "Сазановец",  "4" } /*, { "Калишок",  "4" } */ };

	 PrintTable(columns, 2, lines, 1 /*2*/);
	 PrintRhombus();

	return 0;
}

