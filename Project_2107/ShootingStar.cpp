#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"
using namespace std;

int main() {
	system("mode con cols=150 lines=50 | title Shooting Star★!!!!");
	srand((unsigned int)time(NULL));
	
	while (true) {
		switch (printStartMenu()) {
		case 4:
			return 0;
		case 1:
			system("cls");
			thread_main();
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