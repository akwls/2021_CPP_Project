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

class Small_Monster {
public:
	int x, y;
	int kill = 10;
	void setter(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void print() {
		gotoxy(this->x, this->y); cout << " ■ ";
		//gotoxy(this->x, this->y+1); cout << "■■■";
		//gotoxy(this->x, this->y+2); cout << "■■■";
	}
	~Small_Monster() {
		gotoxy(this->x + 1, this->y); cout << " ";
	}
};


void mainGame() {

	gotoxy(92, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("♥ ♥ ♥");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	int my_x = 44, my_y = 40, i = 0;
	CursorView(0);
	char key = 0;
	gotoxy(my_x, my_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("▶◎◀");
	Small_Monster* monster[5];
	// monster = new Small_Monster[5];
	for (int i = 0; i < 5; i++) {
		monster[i] = new Small_Monster();
		monster[i]->setter(rand() % 61 + 20, rand() % 21 + 1);
		monster[i]->print();
	}
	// Monster monster;

	do {
		key = _getch();
		switch (key) {
		case RIGHT:
			if (my_x >= 0 && my_x < 97) {
				gotoxy(my_x, my_y);
				printf("        ");
				my_x += 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				for (int i = my_y - 1; i >= 0; i--) {
					gotoxy(my_x, i); 
					for (int j = 0; j < 5; j++) {
						if (monster[j]->x == my_x - 1 && monster[j]->y + 1 == i) {
							i = -1;
							break;
						}
					}
					cout << " ";
				}
				for (int i = my_y - 1; i >= 0; i--) {
					gotoxy(my_x+1, i);
					for (int j = 0; j < 5; j++) {
						if (monster[j] != nullptr && monster[j]->x == my_x && monster[j]->y == i) {
							delete monster[j];
							i = -1;
							break;
						}
					}
					cout << "★";
					// Sleep(1);
				}
				for (int i = my_y - 1; i >= 0; i--) {
					gotoxy(my_x + 2, i); 
					for (int j = 0; j < 5; j++) {
						if (monster[j]->x == my_x + 1 && monster[j]->y + 1 == i) {
							i = -1;
							break;
						}
					}
					cout << " ";
				}
			}
			break;
		case LEFT:
			if (my_x > 0 && my_x <= 97) {
				gotoxy(my_x, my_y);
				printf("        ");
				my_x -= 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				for (int i = my_y - 1; i >= 0; i--) {
					gotoxy(my_x, i); 
					for (int j = 0; j < 5; j++) {
						if (monster[j]->x == my_x-1 && monster[j]->y + 1 == i) {
							i = -1;
							break;
						}
					}
					cout << " ";
				}
				for (int i = my_y - 1; i >= 0; i--) {
					gotoxy(my_x+1, i);
					for (int j = 0; j < 5; j++) {
						if (monster[j] != nullptr && monster[j]->x == my_x && monster[j]->y == i) {
							delete monster[j];
							i = -1;
							break;
						}
					}
					cout << "★";
					// Sleep(1);
				}
				for (int i = my_y - 1; i >= 0; i--) {
					gotoxy(my_x+2, i);
					for (int j = 0; j < 5; j++) {
						if (monster[j]->x == my_x + 1 && monster[j]->y + 1 == i) {
							i = -1;
							break;
						}
					}
					cout << " ";
				}
			}
			break;
		}
	} while (key != 27); //ESC = 27
	CursorView(1);
	return;
}