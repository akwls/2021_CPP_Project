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
#define END 40
#define Y_END 50
#define X_END 100
// 12 => RED
// 15 => WHITE
// 6 => DARK YELLOW

static int life = 3;


void print_life() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	int x = X_END + 3;
	gotoxy(x, 1);
	cout << "      ";
	for (int i = 0; i < life; i++) {
		gotoxy(x, 1);
		cout << "♥ ";
		x += 2;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void monster_move(Small_Monster* monster[]) {
	for (int i = 0; i < 5; i++) {
		if (monster[i]->y >= END) {
			delete monster[i];
			monster[i] = new Small_Monster();
			monster[i]->setter(rand() % 61 + 20, rand() % 6 + 1);
			monster[i]->print();
			life--;
			print_life();
		}
	}
	monster[rand() % 5]->move();
}



void mainGame() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(110, 15);
	cout << " ___   ___   ___   _ __   ___ ";
	gotoxy(110, 16);
	cout << "/ __| / __| / _ \\ | '__| / _ \\";
	gotoxy(110, 17);
	cout << "\\__ \\| (__ | (_) || |   |  __/";
	gotoxy(110, 18);
	cout << "|___/ \\___| \\___/ |_|    \\___|";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printScore(0);
	for (int i = 1; i <= X_END; i++) {
		gotoxy(i, 0);
		cout << "-";
	}
	for (int i = 1; i < Y_END; i++) {
		gotoxy(1, i);
		cout << "|";
	}
	for (int i = 1; i < Y_END; i++) {
		gotoxy(X_END, i);
		cout << "|";
	}
	for (int i = 1; i <= X_END; i++) {
		gotoxy(i, Y_END-1);
		cout << "-";
	}
	print_life();
	int my_x = 44, my_y = 45, i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = 2; i < X_END - 1; i++) {
		gotoxy(i, my_y + 1);
		cout << "◆";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	char key = 0;
	gotoxy(my_x, my_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("▶◎◀");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	CursorView(0);
	Small_Monster* monster[5];
	for (int i = 0; i < 5; i++) {
		monster[i] = new Small_Monster();
		monster[i]->setter(rand() % 71 + 10, rand() % 6+ 1);
		monster[i]->print();
	}
	center(my_x, my_y, monster);
	// Monster monster;

	do {
		monster_move(monster);
		if (life <= 0) {
			if(printGameOver() == -1) return;
		}
		key = _getch();
		switch (key) {
		case RIGHT:
			if (my_x >= 2 && my_x < 97) {
				gotoxy(my_x, my_y);
				printf("   ");
				my_x += 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				left(my_x, my_y, monster);
				center(my_x, my_y, monster);
				right(my_x, my_y, monster);
			}
			break;
		case LEFT:
			if (my_x > 2 && my_x <= 97) {
				gotoxy(my_x, my_y);
				printf("   ");
				my_x -= 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				left(my_x, my_y, monster);
				center(my_x, my_y, monster);
				right(my_x, my_y, monster);
			}
			break;
		default:
			break;
		}
	} while (key != 27); //ESC = 27
	CursorView(1);
	return;
}