#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "shooting_star.h"

void setCursorPos(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}