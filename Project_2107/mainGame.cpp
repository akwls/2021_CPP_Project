#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"
using namespace std;

void mainGame() {
	gotoxy(92, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("¢¾¢¾¢¾");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	int x = 44, y = 40, i = 0;
	CursorView(0);
	char key;
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("¢º¡Ý¢¸");

	do {
		key = _getch();
		switch (key) {
		case 77:
			if (x >= 0 && x < 94) {
				gotoxy(x, y);
				printf("        ");
				x += 1;
				gotoxy(x, y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("¢º¡Ý¢¸");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			break;
		case 75:
			if (x > 0 && x <= 94) {
				gotoxy(x, y);
				printf("        ");
				x -= 1;
				gotoxy(x, y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("¢º¡Ý¢¸");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			break;
		}
	} while (key != 27);//ESC =27
	CursorView(1);
	return;
}