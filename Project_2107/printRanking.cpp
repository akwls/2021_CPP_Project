#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "shooting_star.h"
using namespace std;

void printRanking() {
	fstream file;
	ifstream f("ranking.txt");
	int key;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(60, 5);  cout << "                     _    ";
	gotoxy(60, 6);  cout << "                    | |   ";
	gotoxy(60, 7);  cout << " _ __   __ _  _ __  | | __";
	gotoxy(60, 8);  cout << "| '__| / _` || '_ \\ | |/ /";
	gotoxy(60, 9);  cout << "| |   | (_| || | | ||   < ";
	gotoxy(60, 10); cout << "|_|    \\__,_||_| |_||_|\\_\\";

	gotoxy(25, 14); cout << "순위\t\t\t이름\t\t\t\t\t\t점수";
	string data;
	string name[5];
	int score[5];
	int print_y = 17;
	for (int i = 0; i < 5; i++) {
		getline(f, data, '/');
		name[i] = data;
		getline(f, data, '/');
		score[i] = atoi(data.c_str());
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i-1; j++) {
			if (score[j] < score[j + 1]) {
				int tmp = score[j];
				score[j] = score[j + 1];
				score[j + 1] = tmp;
				string t = name[i];
				name[j] = name[j + 1];
				name[j + 1] = t;
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		gotoxy(25, print_y + i);
		if (name[i] != "" && score[i] != 0) {
			cout << i + 1 << "\t\t\t";
			cout << name[i] + "\t\t\t\t\t\t";
			cout << score[i];

		}

	}

	

	gotoxy(0, 40); cout << "<< 뒤로 가려면 [ESC] 키를 눌러주세요...    ";
	while (true) {
		key = _getch();
		if (key == 27) return;
	}
}