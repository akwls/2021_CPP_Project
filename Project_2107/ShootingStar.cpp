#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "shooting_star.h"
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
	srand((unsigned int)time(NULL));
	
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