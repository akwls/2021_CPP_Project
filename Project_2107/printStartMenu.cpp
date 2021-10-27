#include "shooting_star.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <mmsystem.h>
using namespace std;
#pragma comment(lib,"winmm.lib")

int printStartMenu() {
	system("cls");
	CursorView(1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	gotoxy(25, 6);	cout << "   ,-,--.  ,--.-,,-,--,   _,.---._       _,.---._    ,--.--------.  .=-.-..-._            _,---.  ";
	gotoxy(25, 7);	cout << " ,-.'-  _\\/==/  /|=|  | ,-.' , -  `.   ,-.' , -  `. /==/,  -   , -\\/==/_ /==/ \\  .-._ _.='.'-,  \\   ";
	gotoxy(25, 8);	cout << "/==/_ ,_.'|==|_ ||=|, |/==/_,  ,  - \\ /==/_,  ,  - \\\\==\\.-.  - ,-./==|, ||==|, \\/ /, /==.'-     /  ";
	gotoxy(25, 9);	cout << "\\==\\  \\   |==| ,|/=| _|==|   .=.     |==|   .=.     |`--`\\==\\- \\  |==|  ||==|-  \\|  /==/ -   .-'  ";
	gotoxy(25, 10); cout << " \\==\\ -\\  |==|- `-' _ |==|_ : ;=:  - |==|_ : ;=:  - |     \\==\\_ \\ |==|- ||==| ,  | -|==|_   /_,-.   ";
	gotoxy(25, 11); cout << " _\\==\\ ,\\ |==|  _     |==| , '='     |==| , '='     |     |==|- | |==| ,||==| -   _ |==|  , \\_.' )  ";
	gotoxy(25, 12); cout << "/==/\\/ _ ||==|   .-. ,\\\\==\\ -    ,_ / \\==\\ -    ,_ /      |==|, | |==|- ||==|  /\\ , \\==\\-  ,    (   ";
	gotoxy(25, 13); cout << "\\==\\ - , //==/, //=/  | '.='. -   .'   '.='. -   .'       /==/ -/ /==/. //==/, | |- |/==/ _  ,  /    ";
	gotoxy(25, 14); cout << " `--`---' `--`-' `-`--`   `--`--''       `--`--''         `--`--` `--`-` `--`./  `--``--`------'   ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(48, 16); cout << "   ,-,--.  ,--.--------.   ,---.                   ";
	gotoxy(48, 17); cout << " ,-.'-  _\\/==/,  -   , -\\.--.'  \\      .-.,.---.  ";
	gotoxy(48, 18); cout << "/==/_ ,_.'\\==\\.-.  - ,-./\\==\\-/\\ \\    /==/  `   \\  ";
	gotoxy(48, 19); cout << "\\==\\  \\    `--`\\==\\- \\   /==/-|_\\ |  |==|-, .=., | ";
	gotoxy(48, 20); cout << " \\==\\ -\\        \\==\\_ \\  \\==\\,   - \\|==|   '='  / ";
	gotoxy(48, 21); cout << " _\\==\\ ,\\       |==|- |  /==/ -   ,| |==|- ,   .'  ";
	gotoxy(48, 22); cout << "/==/\\/ _ |      |==|, | /==/-  /\\ - \\|==|_  . ,'.  ";
	gotoxy(48, 23); cout << "\\==\\ - , /      /==/ -/ \\==\\ _.\\=\\.-'/==/  /\\ ,  ) ";
	gotoxy(48, 24); cout << " `--`---'       `--`--`  `--`        `--`-`--`--'  ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(64, 26);
	cout << "☆ ★ 슈팅 스타 ☆ ★ ";
	gotoxy(68, 30);
	cout << "게임 시작";
	gotoxy(68, 31);
	cout << "게임 방법";
	gotoxy(68, 32);
	cout << "순위 보기";
	gotoxy(68, 33);
	cout << "게임 종료";

	char key;
	int x = 64;
	int y = 30;
	gotoxy(x, y);
	cout << ">> ";
	while (true) {
		key = _getch();
		switch (key) {
		case 72: 
			if (y > 30 && y <= 33) {
				gotoxy(x, y);
				cout << "   ";
				y--;
				gotoxy(x, y);
				cout << ">> ";
			}
			break;
		case 80:
			if (y < 33 && y >= 30) {
				gotoxy(x, y);
				cout << "   ";
				y++;
				gotoxy(x, y);
				cout << ">> ";
			}
			break;
		case 13:
			return y - 29;
		}
	}
	return 0;
}