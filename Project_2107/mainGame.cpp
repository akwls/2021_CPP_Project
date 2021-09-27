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

int life = 3;
bool bEnded = false;
string name = "";
ifstream fin;
fstream file;
std::condition_variable cv;
std::mutex cv_m;


void print_life() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	int x = X_END + 3;
	gotoxy(x, 1);
	cout << "                  ";
	if (life <= 0) {
		bEnded = true;
		file.open("ranking.txt", ios_base::app | ios_base::in);
		string data = name + "/" + to_string(getScore()) + "/";
		file.write(data.c_str(), data.size());
		printGameOver();
		
	}
	for (int i = 0; i < life; i++) {
		gotoxy(x, 1);
		cout << "♥ ";
		x += 2;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void getName() {
	system("cls");
	CursorView(1);
	gotoxy(30, 25);
	cout << "이름 입력 : ";
	cin >> name;
	CursorView(0);
	system("cls");
}

condition_variable g_controller;
void thread_main() {
	getName();
	mutex g_mutex;
	life = 3;
	bEnded = false;
	setScore();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(110, 15);
	cout << " ___   ___   ___   _ __   ___ ";
	gotoxy(110, 16);
	cout << "/ __| / __| / _ \\ | '__| / _ \\";
	gotoxy(110, 17);
	cout << "\\__ \\| (__ | (_) || |   |  __/";
	gotoxy(110, 18);
	cout << "|___/ \\___| \\___/ |_|    \\___|";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printScore(0);

	gotoxy(110, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " : 3점";
	gotoxy(110, 24);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " : 5점";
	gotoxy(110, 25);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " : 7점";
	

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
	print_life();

	int my_x = 44, my_y = 45, i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = 2; i < X_END - 1; i++) {
		gotoxy(i, START_Y + 1);
		cout << "◆";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	char key;

	CursorView(0);

	Small_Monster* monster[MAX_MONSTER];
	for (int i = 0; i < MAX_MONSTER; i++) {
		monster[i] = new Small_Monster();
		monster[i]->setter(rand() % 71 + 10, rand() % 6 + 1, rand()%3);
		monster[i]->print();
	}

	gotoxy(my_x, my_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "▶◎◀";

	/*
	thread t1(thread_move, ref(my_x), ref(my_y), ref(key));
	thread t2(thread_monster, ref(key), monster);
	thread t3(thread_shoot, ref(my_x), ref(my_y), ref(key), monster);

	t1.join();
	t2.join();
	t3.join();
	*/
	
	thread thread_monster([&]() {
		while (bEnded == false) // true이면 스레드 실행 종료
		{
			unique_lock<std::mutex> lk(cv_m);
			for (int i = 0; i < MAX_MONSTER; i++) {
				if (monster[i]->y >= START_Y) {
					delete monster[i];
					monster[i] = new Small_Monster();
					monster[i]->setter(rand() % 61 + 20, rand() % 6 + 1, rand()%3);
					monster[i]->print();
					life--;
					print_life();
				}
			}
			monster[rand() % MAX_MONSTER]->move();
			Sleep(150);
		}
	});

	// unique_lock<std::mutex> lock(g_mutex);
	// int current_y[MAX_MONSTER];
	int shoot_x;
	while(true) {
		//g_controller.notify_one();
		key = _getch();
		if (life <= 0) {
			bEnded = true;
			thread_monster.join();
			if (printGameOver() == 0) return;
		}
		switch (key) {
		case RIGHT:
			if (my_x >= 2 && my_x < 97) {
				//g_mutex.lock();
				main_gotoxy(my_x, my_y);
				printf("   ");
				my_x += 1;
				main_gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				//g_mutex.unlock();
			}
			break;
		case LEFT:
			if (my_x > 2 && my_x <= 97) {
				//g_mutex.lock();
				main_gotoxy(my_x, my_y);
				printf("   ");
				my_x -= 1;
				main_gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				//g_mutex.unlock();
			}
			break;
		case 27:
			bEnded = true;
			thread_monster.join();
			system("cls");
			return;
		case 32:
			shoot_x = my_x + 1;
			for (int i = my_y - 1; i > 1; i--) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				main_gotoxy(shoot_x, i-1);
				cout << "♠";
				main_gotoxy(shoot_x, i);
				cout << " ";
				// g_mutex.lock();
				for (int j = 0; j < MAX_MONSTER; j++) {
					if (shoot_x == monster[j]->x && i == monster[j]->y -1) {
						delete monster[j];
						monster[j] = new Small_Monster();
						monster[j]->setter(rand() % 61 + 20, rand() % 6 + 1, rand() % 3);
						monster[j]->print();
						main_gotoxy(shoot_x, i);
						cout << " ";
						i = -1;
						printScore(monster[j]->score);
						break;
					}
				}
				//g_mutex.unlock();
				Sleep(5);
			}
			// g_controller.notify_one();
			break;
		default:
			break;
		}
	}
	return;
}