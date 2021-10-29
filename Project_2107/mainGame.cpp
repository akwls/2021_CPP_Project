#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <mutex>
#include <fstream>
#include <mmsystem.h>
#include "shooting_star.h"
using namespace std;
#pragma comment(lib,"winmm.lib")

#define LEFT   75      // ��������Ű 
#define RIGHT  77      // ��������Ű 
#define UP     72      // ���ʹ���Ű 
#define DOWN   80      // �Ʒ�����Ű 
#define END 40
#define Y_END 50
#define X_END 100

#define START_X 44
#define START_Y 45
#define MAX_MONSTER 10

#define LEVEL_1 80
#define LEVEL_2 60
#define LEVEL_3 40

#define LEVEL_1_MONSTER 5
#define LEVEL_2_MONSTER 8
#define LEVEL_3_MONSTER 10

int current_monster = 5;
int speed;
int life = 3; // ����
bool bEnded = false; // ���� ������ ������ ���� ����
string name = ""; // ���� ���۽� �Է¹޴� �̸�
fstream file; // ���Ͽ� �̸��� ������ �Է��ϱ� ���� ���� ����
std::condition_variable cv;
std::mutex g_mutex;
Small_Monster* monster[LEVEL_3_MONSTER];

int gameover = 0; // ������ ��� ����� �� 1�� �ٲٱ�

void printLevel(int level) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(110, 34);
	cout << "���� ���� : Level " << level;
}

void print_life() { // ���� ��� �Լ�
	int x = X_END + 3;
	gotoxy(x, 1);
	cout << "                  ";
	if (life <= 0) {
		bEnded = true; // ���� �Լ� ����
		file.open("../ranking.txt", ios_base::app | ios_base::in);
		string data = name + "/" + to_string(getScore()) + "/";
		file.write(data.c_str(), data.size());
		file.close();
		gameover = 1;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	for (int i = 0; i < life; i++) {
		gotoxy(x, 1);
		cout << "�� ";
		x += 2;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void getName() { // ���� ���۽� �̸� �Է¹޴� �Լ�
	system("cls");
	CursorView(1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	gotoxy(20, 20); cout << " _   _   ___  ___  ___ _____ ";
	gotoxy(20, 21); cout << "| \\ | | / _ \\ |  \\/  ||  ___|";
	gotoxy(20, 22); cout << "|  \\| |/ /_\\ \\| .  . || |__  ";
	gotoxy(20, 23); cout << "| . ` ||  _  || |\\/| ||  __| ";
	gotoxy(20, 24); cout << "| |\\  || | | || |  | || |___ ";
	gotoxy(20, 25); cout << "\\_| \\_/\\_| |_/\\_|  |_/\\____/ ";
	gotoxy(51, 25);
	cout << " : ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cin >> name;
	CursorView(0);
	system("cls");
}

int monster_x_rand() {
	return rand() % 71 + 10;
}

int monster_y_rand() {
	return rand() % 6 + 1;
}

int isItemShown = 0;
int current_item = 0;

class Item {
public:
	int x, y;
	int color;
	int current_score;
	virtual void print() {
		gotoxy(110, 38);
		cout << "print �׽�Ʈ";
	};
	virtual void func() {
		gotoxy(110, 38);
		cout << "func �׽�Ʈ";
	};
	virtual void setter(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

class bonus_life : public Item {
public:
	void print() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		shoot_gotoxy(x, y);
		cout << "��";
	}
	void func() {
		gotoxy(this->x, this->y);
		cout << " ";
		isItemShown = 0;
		life++;
		print_life();
		gotoxy(110, 37);
		cout << "���� �׽�Ʈ";
	}
};


class monster_delete_2 : public Item {
public:
	void print() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		shoot_gotoxy(x, y);
		cout << "��";
	}
	void func() {
		gotoxy(this->x, this->y);
		cout << " ";
		isItemShown = 0;

		int rand1 = rand() % current_monster;
		int rand2 = rand() % current_monster;
		while (rand1 == rand2) {
			rand2 = rand() % current_monster;
		}

		printScore(monster[rand1]->score);
		printScore(monster[rand2]->score);

		delete monster[rand1];
		delete monster[rand2];

		Sleep(500);
		monster[rand1] = new Small_Monster();
		monster[rand1]->setter(monster_x_rand(), monster_y_rand(), rand() % 5);
		monster[rand1]->print();
		monster[rand2] = new Small_Monster();
		monster[rand2]->setter(monster_x_rand(), monster_y_rand(), rand() % 5);
		monster[rand2]->print();

		gotoxy(110, 37);
		cout << "���� �׽�Ʈ";
	}
};

class monster_to_10 : public Item {
public:
	void print() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		shoot_gotoxy(x, y);
		cout << "@";
	}
	void func() {
		gotoxy(this->x, this->y);
		cout << " ";
		isItemShown = 0;
		for (int k = 0; k < current_monster; k++) {
			monster[k]->color = 14;
			monster[k]->score = 10;
		}
		gotoxy(110, 37);
		cout << "10�� �׽�Ʈ";
	}
};

class monster_to_1 : public Item {
public:
	void print() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		shoot_gotoxy(x, y);
		cout << "@";
	}
	void func() {
		gotoxy(this->x, this->y);
		cout << " ";
		isItemShown = 0;
		for (int k = 0; k < current_monster; k++) {
			monster[k]->color = 11;
			monster[k]->score = 1;
		}
		gotoxy(110, 37);
		cout << "1�� �׽�Ʈ";
	}

};

int thread_main() {
	getName(); // �̸� �Է¹޴� �Լ� ȣ��
	// ���ӽ� �ʿ��� ���� �ʱ�ȭ
	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("../start.wav"), 0, SND_FILENAME | SND_ASYNC);
	life = 3;
	speed = LEVEL_1;
	gameover = 0;
	bEnded = false;
	setScore();
	mutex m_mutex;
	int isShoot = 0;
	bonus_life bonus;
	monster_delete_2 mDelete;
	monster_to_10 to10;
	monster_to_1 to1;
	Item *item[4] = { &bonus, &mDelete, &to10, &to1 };
	
	current_monster = LEVEL_1_MONSTER;

	// SCORE �۾� ���
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

	// ���� ���� ���
	gotoxy(110, 22);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : 1��";
	gotoxy(110, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : 3��";
	gotoxy(110, 24);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PINK);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : 5��";
	gotoxy(110, 25);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : 7��";
	gotoxy(110, 26);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : 10��";
	gotoxy(110, 27);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : ���� 2�� ���̱�";
	gotoxy(110, 28);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : ���� 1�� ȸ��";
	gotoxy(110, 29);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "@";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : ��� ���� 1������ �����";
	gotoxy(110, 30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "@";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " : ��� ���� 10������ �����";
	
	// ������ ��輱 ���
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

	printLevel(1);

	// ���� ���
	print_life();

	int my_x = 44, my_y = 45, i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MINT);
	for (int i = 2; i < X_END - 1; i++) { // ���� ������ �״� ���� ���
		gotoxy(i, START_Y + 1);
		cout << "��";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	char key;

	CursorView(0); // Ŀ�� �Ⱥ��̰�

	// ���� ���� ����
	for (int i = 0; i < current_monster; i++) {
		monster[i] = new Small_Monster();
		monster[i]->setter(monster_x_rand(), monster_y_rand(), rand() % 5);
		monster[i]->print();
	}

	gotoxy(my_x, my_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "���ݢ�";

	thread thread_monster([&]() { // ���� �������� �Լ�
		std::unique_lock<std::mutex> lock(g_mutex);
		
		while (bEnded == false) // true�̸� ������ ���� ����
		{
			cv.wait(lock, [&]() { return isShoot == 0; });
			
			for (int i = 0; i < current_monster; i++) {
				// ��輱�� ��Ҵ��� üũ
				if (monster[i]->y >= START_Y) {
					PlaySound(TEXT("../minus_life.wav"), 0, SND_FILENAME | SND_ASYNC);
					delete monster[i];
					monster[i] = new Small_Monster();
					monster[i]->setter(monster_x_rand(), monster_y_rand(), rand() % 5);
					monster[i]->print();
					life--; // ���� ����
					print_life();
				}
			}
			monster[rand() % current_monster]->move(); // ���� �迭 �� �������� ������ ���� ����
			/*
			if (isItemShown == 1) {
				item[current_item]->print();
				if (item[current_item]->current_score + 30 < getScore()) {
					gotoxy(item[current_item]->x, item[current_item]->y);
					cout << " ";
					isItemShown = 0;
				}
			}
			*/
			Sleep(speed); // 0.1�ʸ��� �ݺ�
		}
	});

	int shoot_x = 0;
	
	
	while(!gameover) { // ����� �������� ������ �ݺ�
		CursorView(0);
		int rand_item = rand() % 10;
		if (rand_item == getScore() % 10 && isItemShown == 0) {
			int rand_index = rand() % 4;
			current_item = rand_index;
			item[rand_index]->setter(monster_x_rand(), rand() % 11 + 20);
			item[rand_index]->print();
			isItemShown = 1;
			item[rand_index]->current_score = getScore();
		}
		key = _getch();
		switch (key) {
		case RIGHT:
			isShoot = 1;
			if (my_x >= 2 && my_x < 97) {
				main_gotoxy(my_x, my_y);
				printf("         ");
				my_x += 1;
				main_gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				printf("���ݢ�");
			}
			isShoot = 0;
			cv.notify_one();
			break;
		case LEFT:
			isShoot = 1;
			if (my_x > 2 && my_x <= 97) {
				main_gotoxy(my_x, my_y);
				printf("           ");
				my_x -= 1;
				main_gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				printf("���ݢ�");
			}
			isShoot = 0;
			cv.notify_one();
			break;
		case 27: // ESC
			bEnded = true;
			thread_monster.join();
			return 0;
		case 32: // SPACE BAR
			PlaySound(TEXT("../jelly_sound.wav"), 0, SND_FILENAME | SND_ASYNC);
			shoot_x = my_x + 1;
			isShoot = 1;
			for (int i = my_y - 1; i > 1; i--) { // ĳ���� ��ġ���� ������ ��輱����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				main_gotoxy(shoot_x, i - 1);
				cout << "��";
				main_gotoxy(shoot_x, i);
				cout << " ";
				if (i % (40/current_monster) == 0) {
					monster[rand() % current_monster]->move();
				}
				int j = 0;
				if (shoot_x == item[current_item]->x && i == item[current_item]->y + 1 && isItemShown == 1) {
					item[current_item]->func();
					gotoxy(shoot_x, i+1);
					cout << " ";
					isItemShown = 0;
					break;
				}
				for (j = 0; j < current_monster; j++) {
					if (shoot_x == monster[j]->x && i == monster[j]->y +1) { // ���� �� x��ǥ�� ��ġ�ϴ� ���Ϳ� �Ѿ��� ����� ��
						printScore(monster[j]->score);
						delete monster[j];
						monster[j] = new Small_Monster();
						monster[j]->setter(monster_x_rand(), monster_y_rand(), rand() % 5);
						monster[j]->print();
						main_gotoxy(shoot_x, i+1);
						cout << " ";
						i = -1;
						break;
					}
				}
				Sleep(10);
			}
			if (getScore() >= 80 && current_monster < LEVEL_3_MONSTER) {
				PlaySound(TEXT("../levelup.wav"), 0, SND_FILENAME | SND_ASYNC);
				speed = LEVEL_3;
				current_monster = LEVEL_3_MONSTER;
				for (int k = LEVEL_2_MONSTER; k < LEVEL_3_MONSTER; k++) {
					monster[k] = new Small_Monster();
					monster[k]->setter(monster_x_rand(), monster_y_rand(), rand() % 5);
					monster[k]->print();
				}
				printLevel(3);
			}
			else if (getScore() >= 50 && current_monster < LEVEL_2_MONSTER) {
				PlaySound(TEXT("../levelup.wav"), 0, SND_FILENAME | SND_ASYNC);
				speed = LEVEL_2;
				current_monster = LEVEL_2_MONSTER;
				for (int k = LEVEL_1_MONSTER; k < LEVEL_2_MONSTER; k++) {
					monster[k] = new Small_Monster();
					monster[k]->setter(monster_x_rand(), monster_y_rand(), rand() % 5);
					monster[k]->print();
				}
				printLevel(2);
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
		
		cv.notify_one();
	}
	return 0;
}