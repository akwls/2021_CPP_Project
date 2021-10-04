#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <mutex>
#include <fstream>
#include "shooting_star.h"
using namespace std;

#define LEFT   75      // 좌측방향키 
#define RIGHT  77      // 우측방향키 
#define UP     72      // 위쪽방향키 
#define DOWN   80      // 아래방향키 
#define END 40
#define Y_END 50
#define X_END 100
// 12 => RED
// 15 => WHITE
// 6 => DARK YELLOW
#define START_X 44
#define START_Y 45
#define MAX_MONSTER 5

int life = 3; // 생명
bool bEnded = false; // 몬스터 스레드 정지를 위한 변수
string name = ""; // 게임 시작시 입력받는 이름
fstream file; // 파일에 이름과 점수를 입력하기 위한 파일 변수
std::condition_variable cv;
std::mutex g_mutex;

int gameover = 0; // 생명이 모두 닳았을 때 1로 바꾸기

void print_life() { // 생명 출력 함수
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	int x = X_END + 3;
	gotoxy(x, 1);
	cout << "                  ";
	if (life <= 0) {
		bEnded = true; // 몬스터 함수 종료
		file.open("ranking.txt", ios_base::app | ios_base::in);
		string data = name + "/" + to_string(getScore()) + "/";
		file.write(data.c_str(), data.size());
		file.close();
		gameover = 1;
	}
	for (int i = 0; i < life; i++) {
		gotoxy(x, 1);
		cout << "♥ ";
		x += 2;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void getName() { // 게임 시작시 이름 입력받는 함수
	system("cls");
	CursorView(1);
	gotoxy(20, 20); cout << " _   _   ___  ___  ___ _____ ";
	gotoxy(20, 21); cout << "| \\ | | / _ \\ |  \\/  ||  ___|";
	gotoxy(20, 22); cout << "|  \\| |/ /_\\ \\| .  . || |__  ";
	gotoxy(20, 23); cout << "| . ` ||  _  || |\\/| ||  __| ";
	gotoxy(20, 24); cout << "| |\\  || | | || |  | || |___ ";
	gotoxy(20, 25); cout << "\\_| \\_/\\_| |_/\\_|  |_/\\____/ ";
	gotoxy(51, 25);
	cout << " : ";
	cin >> name;
	CursorView(0);
	system("cls");
}

int thread_main() {
	getName(); // 이름 입력받는 함수 호출
	// 게임시 필요한 변수 초기화
	life = 3;
	gameover = 0;
	bEnded = false;
	setScore();
	mutex m_mutex;
	int isShoot = 0;

	// SCORE 글씨 출력
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(110, 15);
	cout << " ___   ___   ___   _ __   ___ ";
	gotoxy(110, 16);
	cout << "/ __| / __| / _ \\ | '__| / _ \\";
	gotoxy(110, 17);
	cout << "\\__ \\| (__ | (_) || |   |  __/";
	gotoxy(110, 18);
	cout << "|___/ \\___| \\___/ |_|    \\___|";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	printScore(0);

	// 색깔별 점수 출력
	gotoxy(110, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : 3점";
	gotoxy(110, 24);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PINK);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : 5점";
	gotoxy(110, 25);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : 7점";
	
	// 게임판 경계선 출력
	for (int i = 1; i <= X_END; i++) {
		gotoxy(i, 0);
		cout << "-";
	}
	for (int i = 1; i < Y_END; i++) {
		gotoxy(1, i);
		cout << "|";
	}
	for (int i = 1; i < Y_END; i++) {
		gotoxy(X_END, i);
		cout << "|";
	}
	for (int i = 1; i <= X_END; i++) {
		gotoxy(i, Y_END - 1);
		cout << "-";
	}

	// 생명 출력
	print_life();

	int my_x = 44, my_y = 45, i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MINT);
	for (int i = 2; i < X_END - 1; i++) { // 몬스터 닿으면 죽는 경계션 출력
		gotoxy(i, START_Y + 1);
		cout << "◆";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	char key;

	CursorView(0); // 커서 안보이게

	// 최초 몬스터 생성
	Small_Monster* monster[MAX_MONSTER];
	for (int i = 0; i < MAX_MONSTER; i++) {
		monster[i] = new Small_Monster();
		monster[i]->setter(rand() % 71 + 10, rand() % 6 + 1, rand()%3);
		monster[i]->print();
	}

	gotoxy(my_x, my_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "▶◎◀";

	thread thread_monster([&]() { // 몬스터 내려오는 함수
		// std::unique_lock<std::mutex> lock(g_mutex);
		std::unique_lock<std::mutex> lock(g_mutex);
		
		while (bEnded == false) // true이면 스레드 실행 종료
		{
			cv.wait(lock, [&]() { return isShoot == 0; });
			for (int i = 0; i < MAX_MONSTER; i++) {
				// 경계선에 닿았는지 체크
				if (monster[i]->y >= START_Y) {
					delete monster[i];
					monster[i] = new Small_Monster();
					monster[i]->setter(rand() % 61 + 20, rand() % 6 + 1, rand() % 3);
					monster[i]->print();
					life--; // 생명 감소
					print_life();
				}
			}
			monster[rand() % MAX_MONSTER]->move(); // 몬스터 배열 중 랜덤으로 내려올 몬스터 지정
			Sleep(100); // 0.1초마다 반복
		}
	});

	// unique_lock<std::mutex> lock(g_mutex);
	// int current_y[MAX_MONSTER];
	int shoot_x = 0;
	cv.notify_one();
	
	while(!gameover) { // 목숨이 남아있을 때까지 반복
		CursorView(0);
		//g_controller.notify_one();
		key = _getch();
		cv.notify_one();
		switch (key) {
		case RIGHT:
			cv.notify_one();
			if (my_x >= 2 && my_x < 97) {
				//g_mutex.lock();
				main_gotoxy(my_x, my_y);
				printf("   ");
				my_x += 1;
				main_gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				printf("▶◎◀");
				//g_mutex.unlock();
			}
			break;
		case LEFT:
			cv.notify_one();
			if (my_x > 2 && my_x <= 97) {
				//g_mutex.lock();
				main_gotoxy(my_x, my_y);
				printf("   ");
				my_x -= 1;
				main_gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				printf("▶◎◀");
				//g_mutex.unlock();
			}
			break;
		case 27: // ESC
			bEnded = true;
			thread_monster.join();
			return 0;
		case 32: // SPACE BAR
			shoot_x = my_x + 1;
			isShoot = 1;
			for (int i = my_y - 1; i > 1; i--) { // 캐릭터 위치부터 게임판 경계선까지
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				main_gotoxy(shoot_x, i - 1);
				cout << "♠";
				main_gotoxy(shoot_x, i);
				cout << " ";
				if (i % 10 == 0) {
					monster[rand()%MAX_MONSTER]->move();
				}
				// g_mutex.lock();
				int j = 0;
				for (j = 0; j < MAX_MONSTER; j++) {
					if (shoot_x == monster[j]->x && i == monster[j]->y +1) { // 총은 쏜 x좌표와 일치하는 몬스터와 총알이 닿았을 때
						printScore(monster[j]->score);
						delete monster[j];
						monster[j] = new Small_Monster();
						monster[j]->setter(rand() % 61 + 20, rand() % 6 + 1, rand() % 3);
						monster[j]->print();
						main_gotoxy(shoot_x, i+1);
						cout << " ";
						i = -1;
						break;
					}
				}
				//g_mutex.unlock();
				Sleep(10);
			}
			main_gotoxy(shoot_x, 1); cout << " ";
			isShoot = 0;
			cv.notify_one();
			
			break;
		default:
			break;
		}
		if (gameover == 1) {
			bEnded = true;
			thread_monster.join();
			return 1;
		}
	}
	return 0;
}