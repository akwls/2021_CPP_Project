#include "shooting_star.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

int printStartMenu() {
	system("cls");
	gotoxy(25, 6); cout << " _____  _                    _    _               " << endl;
	gotoxy(25, 7); cout << "/  ___|| |                  | |  (_)              " << endl;
	gotoxy(25, 8); cout << "\\ `--. | |__    ___    ___  | |_  _  _ __    __ _ " << endl;
	gotoxy(25, 9); cout << " `--. \\| '_ \\  / _ \\  / _ \\ | __|| || '_ \\  / _` |" << endl;
	gotoxy(25, 10); cout << "/\\__/ /| | | || (_) || (_) || |_ | || | | || (_| |" << endl;
	gotoxy(25, 11); cout << "\\____/ |_| |_| \\___/  \\___/  \\__||_||_| |_| \\__, |" << endl;
	gotoxy(25, 12); cout << "                                             __/ |" << endl;
	gotoxy(25, 13); cout << "                                            |___/ " << endl;
	gotoxy(36, 14); cout << " _____  _                " << endl;
	gotoxy(36, 15); cout << "/  ___|| |               " << endl;
	gotoxy(36, 16); cout << "\\ `--. | |_   __ _  _ __ " << endl;
	gotoxy(36, 17); cout << " `--. \\| __| / _` || '__|" << endl;
	gotoxy(36, 18); cout << "/\\__/ /| |_ | (_| || |   " << endl;
	gotoxy(36, 19); cout << "\\____/  \\__| \\__,_||_|   " << endl;

	cout << endl;
	cout << "					  1. ���� ����						  " << endl;
	cout << "					  2. ���� ���						  " << endl;
	cout << "					  3. ����						      " << endl;
	cout << "					  0. ����						      " << endl;
	int menu;
	while (true) {
		cout << endl << ">> ";
		cin >> menu;
		if (menu >= 0 && menu <= 3) break;
		printf("�ٽ� �Է����ּ���!");
		Sleep(800); // 1�� ����
		for (int i = 0; i < 2; ++i) { // �� ��� ���� �����
			//printf("%c[2K",27);
			cout << "\33[2K"; //line clear
			cout << "\x1b[A"; //up line (ESC [ A) must be support VT100 escape seq
			cout << "\b\b\b\b\b\b\b\b\b\b\b";
		}
	}
	return menu;
}