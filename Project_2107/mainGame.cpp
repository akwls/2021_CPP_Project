#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "shooting_star.h"

void mainGame() {
	int x = 44, y = 40, i = 0;
	CursorView(0);
	char key;
	setCursorPos(x, y);
	printf("¢º¡Ý¢¸");

	do {
		key = _getch();
		switch (key) {
		case 77:
			if (x >= 0 && x < 94) {
				setCursorPos(x, y);
				printf("        ");
				x += 1;
				setCursorPos(x, y);
				printf("¢º¡Ý¢¸");
			}
			break;
		case 75:
			if (x > 0 && x <= 94) {
				setCursorPos(x, y);
				printf("        ");
				x -= 1;
				setCursorPos(x, y);
				printf("¢º¡Ý¢¸");
			}
			break;
		}
	} while (key != 27);//ESC =27
	CursorView(1);
	return;
}