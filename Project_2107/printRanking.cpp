#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"
using namespace std;

void printRanking() {
	int key;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(60, 5);  cout << "                     _    ";
	gotoxy(60, 6);  cout << "                    | |   ";
	gotoxy(60, 7);  cout << " _ __   __ _  _ __  | | __";
	gotoxy(60, 8);  cout << "| '__| / _` || '_ \\ | |/ /";
	gotoxy(60, 9);  cout << "| |   | (_| || | | ||   < ";
	gotoxy(60, 10); cout << "|_|    \\__,_||_| |_||_|\\_\\";
	gotoxy(0, 20); cout << "<< 뒤로 가려면 [ESC] 키를 눌러주세요...    ";
	while (true) {
		key = _getch();
		if (key == 27) return;
	}
}