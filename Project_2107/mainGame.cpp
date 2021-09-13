#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <mutex>
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


/*
void monster_move(Small_Monster* monster[]) {
	for (int i = 0; i < 5; i++) {
		if (monster[i]->y >= END) {
			delete monster[i];
			monster[i] = new Small_Monster();
			monster[i]->setter(rand() % 61 + 20, rand() % 6 + 1);
			monster[i]->print();
			life--;
			print_life();
		}
	}
	monster[rand() % 5]->move();
}
*/


/*
void mainGame() {
	life = 5;
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " : 5점";
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
		gotoxy(i, Y_END-1);
		cout << "-";
	}
	print_life();
	int my_x = 44, my_y = 45, i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = 2; i < X_END - 1; i++) {
		gotoxy(i, my_y + 1);
		cout << "◆";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	char key = 0;
	gotoxy(my_x, my_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("▶◎◀");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	CursorView(0);
	Small_Monster* monster[5];
	for (int i = 0; i < 5; i++) {
		monster[i] = new Small_Monster();
		monster[i]->setter(rand() % 71 + 10, rand() % 6+ 1);
		monster[i]->print();
	}
	center(my_x, my_y, monster);
	// Monster monster;

	do {
		monster_move(monster);
		if (life <= 0) {
			if(printGameOver() == -1) return;
		}
		key = _getch();
		switch (key) {
		case RIGHT:
			if (my_x >= 2 && my_x < 97) {
				gotoxy(my_x, my_y);
				printf("   ");
				my_x += 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				left(my_x, my_y, monster);
				center(my_x, my_y, monster);
				right(my_x, my_y, monster);
			}
			break;
		case LEFT:
			if (my_x > 2 && my_x <= 97) {
				gotoxy(my_x, my_y);
				printf("   ");
				my_x -= 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				left(my_x, my_y, monster);
				center(my_x, my_y, monster);
				right(my_x, my_y, monster);
			}
			break;
		default:
			break;
		}
	} while (key != 27); //ESC = 27
	CursorView(1);
	return;
}
*/

/*
void thread_shoot(int& x, int& y, char& key, Small_Monster* monster[]) {
	while (key != 27) {
		int shoot_x = x + 1;
		if (key == 32) {
			for (int i = y-1; i > 0; i--) {
				gotoxy(shoot_x, i-1);
				cout << "♠";
				gotoxy(shoot_x, i);
				cout << " ";
				g_mutex.lock();
				for (int j = 0; j < 5; j++) {
					if (x == monster[j]->x && i == monster[j]->y) {
						delete monster[j];
						printScore(5);
						monster[j] = new Small_Monster();
						monster[j]->setter(rand() % 61 + 20, rand() % 6 + 1);
						monster[j]->print();
						i = -1;
						break;
					}
				}
				g_mutex.unlock();
				Sleep(5);
			}
			continue;
		}
	}
}

void thread_move(int &my_x, int &my_y, char &key) {
	do {
		if (life <= 0) {
			if (printGameOver() == -1) return;
		}
		key = _getch();
		switch (key) {
		case RIGHT:
			if (my_x >= 2 && my_x < 97) {
				gotoxy(my_x, my_y);
				printf("   ");
				my_x += 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
			}
			break;
		case LEFT:
			if (my_x > 2 && my_x <= 97) {
				gotoxy(my_x, my_y);
				printf("   ");
				my_x -= 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
			}
			break;
		default:
			break;
		}
	} while (key != 27); //ESC = 27
	return;
}

void thread_monster(char& key, Small_Monster* monster[]) {
	do {
		for (int i = 0; i < 5; i++) {
			if (monster[i]->y >= START_Y) {
				delete monster[i];
				monster[i] = new Small_Monster();
				monster[i]->setter(rand() % 61 + 20, rand() % 6 + 1);
				monster[i]->print();
				life--;
				print_life();
			}
		}
		monster[rand() % 5]->move();
		Sleep(500);
	} while (key != 27);
	return;
}
*/

int life = 5;
bool bEnded = false;

void print_life() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	int x = X_END + 3;
	gotoxy(x, 1);
	cout << "                  ";
	if (life <= 0) {
		bEnded = true;
		printGameOver();
	}
	for (int i = 0; i < life; i++) {
		gotoxy(x, 1);
		cout << "♥ ";
		x += 2;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void thread_main() {
	
	mutex g_mutex;
	
	
	life = 5;
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " : 5점";
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

	Small_Monster* monster[5];
	for (int i = 0; i < 5; i++) {
		monster[i] = new Small_Monster();
		monster[i]->setter(rand() % 71 + 10, rand() % 6 + 1);
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
			for (int i = 0; i < 5; i++) {
				if (monster[i]->y >= START_Y) {
					delete monster[i];
					monster[i] = new Small_Monster();
					monster[i]->setter(rand() % 61 + 20, rand() % 6 + 1);
					monster[i]->print();
					life--;
					print_life();
				}
			}
			monster[rand() % 5]->move();
			Sleep(100);
		}
	});

	while(true) {
		key = _getch();
		if (key == 27) {
			bEnded = true;
			thread_monster.join();
			return;
		}
		if (life <= 0) {
			bEnded = true;
			printGameOver();
			thread_monster.join();
			return;
		}
		switch (key) {
		case RIGHT:
			if (my_x >= 2 && my_x < 97) {
				g_mutex.lock();
				gotoxy(my_x, my_y);
				printf("   ");
				my_x += 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				g_mutex.unlock();
			}
			break;
		case LEFT:
			if (my_x > 2 && my_x <= 97) {
				g_mutex.lock();
				gotoxy(my_x, my_y);
				printf("   ");
				my_x -= 1;
				gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("▶◎◀");
				g_mutex.unlock();
			}
			break;
		default:
			break;
		}
	}
	return;
}