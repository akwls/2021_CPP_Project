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

	printf("\t캔디나라에 살고 있는 \"롤리\", \n");
	printf("\t어느 날, 캔디들의 달콤함을 빼앗기 위해 몬스터들이 내려오기 시작했다!\n");
	printf("\t캔디들은 몬스터와 닿으면 몸에 금이 가서 깨져버릴거야 ㅠㅠ\n");
	printf("\t\"롤리\"의 젤리를 쏘아서 몬스터들을 물리치자!\n\n\n\n");
	printf("\t[게임 플레이 방법]\n\n");
	printf("\t위에서 사탕 몬스터들이 내려옵니다!\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	printf("\t←, → 화살표로 롤리를 움직이고 스페이스바를 눌러 젤리를 쏘아주세요!!!!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	printf("\t몬스터의 색깔에 따라 점수는 달라집니다. 점수는 게임 플레이 화면 우측을 확인하세요.\n");
	printf("\t무작위로 나타나는 아이템들을 맞춰보세요! 좋은걸까, 나쁜걸까?\n");
	printf("\t젤리를 맞은 몬스터는 사라지고 새로운 몬스터가 내려옵니다.\n\n\n\n");
	printf("\t[생명]\n\n");
	printf("\t몬스터가 파란선 밑으로 내려오면 생명이 깎이게 됩니다. 주어진 생명은 3개!\n");
	printf("\t화면 우측 상단에서 생명을 확인할 수 있습니다.\n\n\n\n");
	printf("\t[점수]\n\n");
	printf("\t젤리의 색깔에 따라 점수가 달라집니다. \n");
	printf("\t게임 시작할 때 닉네임을 입력하고 시작화면에서 \"순위 보기\"를 눌러 랭킹을 확인해보세요!\n\n\n\n\n");
	printf("<< 뒤로 가려면 [ESC] 키를 눌러주세요...    ");
	while (true) {
		key = _getch();
		if (key == 27) return;
	}
}
