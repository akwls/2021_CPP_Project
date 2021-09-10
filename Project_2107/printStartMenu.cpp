#include "shooting_star.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
using namespace std;

int printStartMenu() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(50, 6); cout << " _____  _                    _    _               ";
	gotoxy(50, 7); cout << "/  ___|| |                  | |  (_)              ";
	gotoxy(50, 8); cout << "\\ `--. | |__    ___    ___  | |_  _  _ __    __ _ ";
	gotoxy(50, 9); cout << " `--. \\| '_ \\  / _ \\  / _ \\ | __|| || '_ \\  / _` |";
	gotoxy(50, 10); cout << "/\\__/ /| | | || (_) || (_) || |_ | || | | || (_| |";
	gotoxy(50, 11); cout << "\\____/ |_| |_| \\___/  \\___/  \\__||_||_| |_| \\__, |";
	gotoxy(50, 12); cout << "                                             __/ |";
	gotoxy(50, 13); cout << "                                            |___/ ";
	gotoxy(61, 14); cout << " _____  _                ";
	gotoxy(61, 15); cout << "/  ___|| |               ";
	gotoxy(61, 16); cout << "\\ `--. | |_   __ _  _ __ ";
	gotoxy(61, 17); cout << " `--. \\| __| / _` || '__|";
	gotoxy(61, 18); cout << "/\\__/ /| |_ | (_| || |   ";
	gotoxy(61, 19); cout << "\\____/  \\__| \\__,_||_|   ";

	gotoxy(66, 25);
	cout << "1. 게임 시작";
	gotoxy(66, 26);
	cout << "2. 게임 방법";
	gotoxy(66, 27);
	cout << "3. 순위 보기";
	gotoxy(66, 28);
	cout << "4. 게임 종료";

	char key;
	int x = 62;
	int y = 25;
	gotoxy(x, y);
	cout << ">> ";
	while (true) {
		key = _getch();
		switch (key) {
		case 72: 
			if (y > 25 && y <= 28) {
				gotoxy(x, y);
				cout << "   ";
				y--;
				gotoxy(x, y);
				cout << ">> ";
			}
			break;
		case 80:
			if (y < 28 && y >= 25) {
				gotoxy(x, y);
				cout << "   ";
				y++;
				gotoxy(x, y);
				cout << ">> ";
			}
			break;
		case 13:
			return y - 24;
		}
		
		
	}
	return 0;
}