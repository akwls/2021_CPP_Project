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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(60, 5);  cout << "                     _    ";
	gotoxy(60, 6);  cout << "                    | |   ";
	gotoxy(60, 7);  cout << " _ __   __ _  _ __  | | __";
	gotoxy(60, 8);  cout << "| '__| / _` || '_ \\ | |/ /";
	gotoxy(60, 9);  cout << "| |   | (_| || | | ||   < ";
	gotoxy(60, 10); cout << "|_|    \\__,_||_| |_||_|\\_\\";

	gotoxy(35, 14); cout << "순위\t\t\t이름\t\t\t\t\t\t점수";
	gotoxy(35, 15); cout << "===========================================================================";
	string data;
	string name[10];
	int score[10] = { 0, };
	int print_y = 17;
	int cnt = 1;
	int g_score;
	string g_name;

	// 최초 입력받기
	getline(f, data, '/');
	name[0] = data;
	getline(f, data, '/');
	score[0] = atoi(data.c_str());

	// 파일이 끝날때까지
	while(!f.eof()) {
		getline(f, data, '/');
		g_name = data;
		getline(f, data, '/');
		g_score = atoi(data.c_str());

		// 점수를 읽고 배열에 삽입정렬하기
		for (int i = 0; i < 10; i++) {
			if (g_score >= score[i]) {
				for (int j = 9; j > i; j--) {
					score[j] = score[j-1];
					name[j] = name[j-1];
				}
				score[i] = g_score;
				name[i] = g_name;
				break;
			}
		}
		
	}

	// 랭킹 출력
	for (int i = 0; i < 10; i++) {
		gotoxy(35, print_y++);
		if (name[i] != "" && score[i] != 0) {
			cout << i + 1 << "\t\t\t";
			cout << name[i] + "\t\t\t\t\t\t";
			cout << score[i];
			gotoxy(35, print_y++);
			cout << "---------------------------------------------------------------------------";

		}
	}
	f.close();
	
	gotoxy(0, 43); cout << "<< 뒤로 가려면 [ESC] 키를 눌러주세요...    ";
	while (true) {
		key = _getch();
		if (key == 27) return;
	}
}