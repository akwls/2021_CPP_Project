#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "shooting_star.h"
#define LEFT   75      // 좌측방향키 
#define RIGHT  77      // 우측방향키 
#define UP     72      // 위쪽방향키 
#define DOWN   80      // 아래방향키
using namespace std;

/*
class small_monster {
public:
	double speed;
	int kill;
	void move() {

	}
	void setXY() {
		COORD pos = { this->x,this->y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	
};
*/

int main() {
	system("mode con cols=100 lines=50 | title Shooting Star★!!!!");
	
	while (true) {
		switch (printStartMenu()) {
		case 0:
			return 0;
		case 1:
			system("cls");
			mainGame();
			break;
		case 2:
			system("cls");
			printScript();
			break;
		case 3:
			system("cls");
			printRanking();
			break;
		}
	}
}