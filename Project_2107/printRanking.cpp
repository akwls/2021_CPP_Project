#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "shooting_star.h"

void printRanking() {
	int key;
	printf("�̰��� ���� ������ ��Ÿ���ϴ�.\n\n\n\n\n\n\n");
	printf("<< �ڷ� ������ [ESC] Ű�� �����ּ���...    ");
	while (true) {
		key = _getch();
		if (key == 27) return;
	}
}