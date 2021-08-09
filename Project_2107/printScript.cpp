#include "shooting_star.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

void printScript() {
	int key;
	printf("\t\t\t\t\tSHOOTING STAR\n\n\n\n");
	printf("캔디나라에 살고 있는 \"롤리\", \n");
	printf("어느 날, 캔디들의 달콤함을 빼앗기 위해 몬스터들이 내려오기 시작했다!\n");
	printf("캔디들은 몬스터와 닿으면 몸에 금이 가서 깨져버릴거야 ㅠㅠ\n");
	printf("\"롤리\"의 젤리를 쏘아서 몬스터들을 물리치자!\n\n\n\n");
	printf("[게임 플레이 방법]\n\n");
	printf("위에서 사탕 몬스터들이 내려옵니다!\n\n");
	printf("←, → 화살표로 캐릭터를 움직여 젤리를 쏘아 몬스터를 맞춰주세요.\n");
	printf("젤리를 많이 맞은 몬스터는 사라집니다.\n\n\n\n");
	printf("[생명]\n\n");
	printf("몬스터와 캐릭터가 닿으면 생명이 깎이게 됩니다. 주어진 생명은 3개!\n");
	printf("화면 우측 상단에서 생명을 확인할 수 있습니다.\n\n\n\n");
	printf("[점수]\n\n");
	printf("젤리의 크기에 따라 점수가 달라집니다. \n");
	printf("닉네임을 입력하고 시작화면에서 3번을 눌러 랭킹을 확인해보세요!\n\n\n\n\n\n\n\n\n");
	printf("<< 뒤로 가려면 [ESC] 키를 눌러주세요...    ");
	key = _getch();
	if (key == 27) return;
}
