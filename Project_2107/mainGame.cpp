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

class Small_Monster {
public:
	int x, y;
	void setter(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void print() {
		gotoxy(this->x-1, this->y); cout << " ■ ";
	}
	void move() {
		gotoxy(this->x, this->y); cout << " ";
		this->y++;
		gotoxy(this->x - 1, this->y); cout << " ■ ";
	}
	~Small_Monster() {
		gotoxy(this->x, this->y); cout << " ";
	}
};

void left(int my_x, int my_y, Small_Monster* monster[]) {
	for (int i = my_y - 1; i >= 1; i--) {
		gotoxy(my_x, i);
		for (int j = 0; j < 5; j++) {
			if (monster[j]->x == my_x && monster[j]->y + 1 == i) {
				i = -1;
				break;
			}
		}
		cout << " ";
	}
}
void center(int my_x, int my_y, Small_Monster* monster[]) {
	int target = -1;
	for (int i = my_y - 1; i >= 1; i--) {
		gotoxy(my_x + 1, i);
		for (int j = 0; j < 5; j++) {
			if (monster[j] != nullptr && monster[j]->x == my_x + 1 && monster[j]->y == i) {
				target = j;
				break;
			}
		}
		if (target != -1 && monster[target] != nullptr) {
			delete monster[target];
			monster[target] = new Small_Monster();
			monster[target]->setter(rand() % 61 + 20, rand() % 21 + 1);
			monster[target]->print();
			break;
		}
		cout << "★";
		// Sleep(1);
	}
	
}
void right(int my_x, int my_y, Small_Monster* monster[]) {
	for (int i = my_y - 1; i >= 1; i--) {
		gotoxy(my_x + 2, i);
		for (int j = 0; j < 5; j++) {
			if (monster[j]->x == my_x + 2 && monster[j]->y + 1 == i) {
				i = -1;
				break;
			}
		}
		cout << " ";
	}
}

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
			monster[i]->setter(rand() % 61 + 20, rand() % 21 + 1);
			monster[i]->print();
			life--;
			print_life();
		}
	}
	monster[rand() % 5]->move();
}

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

void mainGame() {
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
		monster[i]->setter(rand() % 71 + 10, rand() % 11 + 1);
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