// os-03.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void Print(int x, int y, char* str, int color = 0x1A)
{
	HANDLE consoleOutput;
	COORD cursorPos;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	cursorPos.X = x;
	cursorPos.Y = y;

	SetConsoleCursorPosition(consoleOutput, cursorPos);
	SetConsoleTextAttribute(consoleOutput, color);

	std::cout << str << std::endl;
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
				Print(width, 1, columns[k], 0x0F);
			else
				Print(width, l, lines[i - 1][k], 0x0F);
		}
	}

	std::cout << std::endl;

	delete[] line;
	delete[] column;
}

int main()
{
	setlocale(NULL, "");

	char columns[][10] = { "Фамилия", "Группа" };
	char lines[][10][10] = { { "Сазановец",  "4" } /*, { "Калишок",  "4" } */ };

	PrintTable(columns, 2, lines, 1 /*2*/);

	return 0;
}

