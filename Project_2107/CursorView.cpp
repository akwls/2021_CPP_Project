#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "shooting_star.h"

void CursorView(char show) //Ä¿¼­¼û±â±â
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show; // 0 = invisible, 1 = visible
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}