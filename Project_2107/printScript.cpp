#include "shooting_star.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
void printScript() {
	int key;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(46, 2);  cout << " _   _                 _         ______ _            ___  ";
	gotoxy(46, 3); cout << "| | | |               | |        | ___ \\ |          |__ \\ ";
	gotoxy(46, 4); cout << "| |_| | _____      __ | |_ ___   | |_/ / | __ _ _   _  ) |";
	gotoxy(46, 5); cout << "|  _  |/ _ \\ \\ /\\ / / | __/ _ \\  |  __/| |/ _` | | | |/ / ";
	gotoxy(46, 6); cout << "| | | | (_) \\ V  V /  | || (_) | | |   | | (_| | |_| |_|  ";
	gotoxy(46, 7); cout << "\\_| |_/\\___/ \\_/\\_/    \\__\\___/  \\_|   |_|\\__,_|\\__, (_)  ";
	gotoxy(46, 8); cout << "                                                 __/ |    ";
	gotoxy(46, 9); cout << "                                                |___/     ";
	cout << endl << endl;

	printf("\tĵ�𳪶� ��� �ִ� \"�Ѹ�\", \n");
	printf("\t��� ��, ĵ����� �������� ���ѱ� ���� ���͵��� �������� �����ߴ�!\n");
	printf("\tĵ����� ���Ϳ� ������ ���� ���� ���� ���������ž� �Ф�\n");
	printf("\t\"�Ѹ�\"�� ������ ��Ƽ� ���͵��� ����ġ��!\n\n\n\n");
	printf("\t[���� �÷��� ���]\n\n");
	printf("\t������ ���� ���͵��� �����ɴϴ�!\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	printf("\t��, �� ȭ��ǥ�� �Ѹ��� �����̰� �����̽��ٸ� ���� ������ ����ּ���!!!!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	printf("\t������ ���� ���� ������ �޶����ϴ�. ������ ���� �÷��� ȭ�� ������ Ȯ���ϼ���.\n");
	printf("\t�������� ��Ÿ���� �����۵��� ���纸����! �����ɱ�, ���۰ɱ�?\n");
	printf("\t������ ���� ���ʹ� ������� ���ο� ���Ͱ� �����ɴϴ�.\n\n\n\n");
	printf("\t[����]\n\n");
	printf("\t���Ͱ� �Ķ��� ������ �������� ������ ���̰� �˴ϴ�. �־��� ������ 3��!\n");
	printf("\tȭ�� ���� ��ܿ��� ������ Ȯ���� �� �ֽ��ϴ�.\n\n\n\n");
	printf("\t[����]\n\n");
	printf("\t������ ���� ���� ������ �޶����ϴ�. \n");
	printf("\t���� ������ �� �г����� �Է��ϰ� ����ȭ�鿡�� \"���� ����\"�� ���� ��ŷ�� Ȯ���غ�����!\n\n\n\n\n");
	printf("<< �ڷ� ������ [ESC] Ű�� �����ּ���...    ");
	while (true) {
		key = _getch();
		if (key == 27) return;
	}
}
