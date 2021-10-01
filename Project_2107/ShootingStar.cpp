#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"
using namespace std;

int main() {
	system("mode con cols=150 lines=50 | title SHOOTING STAR★★★★★★");
	srand((unsigned int)time(NULL));
	int ret = 0;
	
	while (true) {
		switch (printStartMenu()) {
		case 4:
			return 0;
		case 1:
			system("cls");
			ret = thread_main();
			if (ret == 1) printGameOver();
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