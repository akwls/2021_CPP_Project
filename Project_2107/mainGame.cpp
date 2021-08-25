#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"
using namespace std;
#define LEFT   75      // 좌측방향키 
#define RIGHT  77      // 우측방향키 
#define UP     72      // 위쪽방향키 
#define DOWN   80      // 아래방향키
// 12 => RED
// 15 => WHITE
// 6 => DARK YELLOW

/*
class Monster {
public:
	int kill[3] = { 10, 15, 20 };
	string shape[3] = { "■■\n■■", "■■■\n■■■\n■■■", "■■■■■\n■■■■■\n■■■■■\n■■■■■\n■■■■■" };
	Monster() {

	}
};
*/

void mainGame() {
	gotoxy(92, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("♥ ♥ ♥");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	int x = 44, y = 40, i = 0;
	CursorView(0);
	char key = 0;
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("▶◎◀");
	// Monster monster;

	do {
		key = _getch();
		switch (key) {
		case 77:
			if (x >= 0 && x < 97) {
				gotoxy(x, y);
				printf("        ");
				x += 1;
				gotoxy(x, y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				for (int i = y-1; i >=0; i--) {
					gotoxy(x, i);
					cout << " ★  ";
					// Sleep(1);
				}
			}
			break;
		case 75:
			if (x > 0 && x <= 97) {
				gotoxy(x, y);
				printf("        ");
				x -= 1;
				gotoxy(x, y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				for (int i = y-1; i >= 0; i--) {
					gotoxy(x, i);
					cout << " ★  ";
					// Sleep(1);
				}
			}
			break;
		}
	} while (key != 27); //ESC = 27
	CursorView(1);
	return;
}