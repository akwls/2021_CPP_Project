#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"
#include "Small_Monster.h"
using namespace std;


int printGameOver() {
	CursorView(1);
	system("cls");
	gotoxy(60, 15);
	cout << " _____   ___  ___  ___ _____ ";
	gotoxy(60, 16);
	cout << "|  __ \\ / _ \\ |  \\/  ||  ___|";
	gotoxy(60, 17);
	cout << "| |  \\// /_\\ \\| .  . || |__  ";
	gotoxy(60, 18);
	cout << "| | __ |  _  || |\\/| ||  __| ";
	gotoxy(60, 19);
	cout << "| |_\\ \\| | | || |  | || |___ ";
	gotoxy(60, 20);
	cout << " \\____/\\_| |_/\\_|  |_/\\____/ ";

	gotoxy(60, 21);
	cout << " _____  _   _  _____ ______ ";
	gotoxy(60, 22);
	cout << "|  _  || | | ||  ___|| ___ \\";
	gotoxy(60, 23);
	cout << "| | | || | | || |__  | |_/ /";
	gotoxy(60, 24);
	cout << "| | | || | | ||  __| |    / ";
	gotoxy(60, 25);
	cout << "\\ \\_/ /\\ \\_/ /| |___ | |\\ \\ ";
	gotoxy(60, 26);
	cout << " \\___/  \\___/ \\____/ \\_| \\_|";

	gotoxy(56, 30);
	cout << "[ESC] 키를 누르면 메인 화면으로 넘어갑니다....";
	char key;
	while (true) {
		while (true) {
			key = _getch();
			if (key == 27) return -1;
		}
	}
}