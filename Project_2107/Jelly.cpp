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
