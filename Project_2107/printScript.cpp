#include "shooting_star.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

void printScript() {
	int key;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\t\t\t\t\tSHOOTING STAR\n\n\n\n");
	printf("ĵ�𳪶� ��� �ִ� \"�Ѹ�\", \n");
	printf("��� ��, ĵ����� �������� ���ѱ� ���� ���͵��� �������� �����ߴ�!\n");
	printf("ĵ����� ���Ϳ� ������ ���� ���� ���� ���������ž� �Ф�\n");
	printf("\"�Ѹ�\"�� ������ ��Ƽ� ���͵��� ����ġ��!\n\n\n\n");
	printf("[���� �÷��� ���]\n\n");
	printf("Ű���带 ���������� ������ ���� ���͵��� �����ɴϴ�!\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("�������� �ּ�ȭ�ϸ鼭 ���͸� ���̴°� �ٽ�!!!!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��, �� ȭ��ǥ�� ĳ���͸� ������ ������ ��� ���͸� �����ּ���.\n");
	printf("������ ���� ���ʹ� ������ϴ�.\n\n\n\n");
	printf("[����]\n\n");
	printf("���Ͱ� �Ķ��� ������ �������� ������ ���̰� �˴ϴ�. �־��� ������ 3��!\n");
	printf("ȭ�� ���� ��ܿ��� ������ Ȯ���� �� �ֽ��ϴ�.\n\n\n\n");
	printf("[����]\n\n");
	printf("������ ũ�⿡ ���� ������ �޶����ϴ�. \n");
	printf("�г����� �Է��ϰ� ����ȭ�鿡�� \"���� ����\"�� ���� ��ŷ�� Ȯ���غ�����!\n\n\n\n\n\n\n\n\n");
	printf("<< �ڷ� ������ [ESC] Ű�� �����ּ���...    ");
	while (true) {
		key = _getch();
		if (key == 27) return;
	}
}
