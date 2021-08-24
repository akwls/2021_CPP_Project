#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "shooting_star.h"

void printRanking() {
	int key;
	printf("이곳에 점수 순위가 나타납니다.\n\n\n\n\n\n\n");
	printf("<< 뒤로 가려면 [ESC] 키를 눌러주세요...    ");
	while (true) {
		key = _getch();
		if (key == 27) return;
	}
}