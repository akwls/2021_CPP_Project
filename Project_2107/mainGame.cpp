#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <mutex>
#include <fstream>
#include "shooting_star.h"
using namespace std;

#define LEFT   75      // ��������Ű 
#define RIGHT  77      // ��������Ű 
#define UP     72      // ���ʹ���Ű 
#define DOWN   80      // �Ʒ�����Ű 
#define END 40
#define Y_END 50
#define X_END 100
// 12 => RED
// 15 => WHITE
// 6 => DARK YELLOW
#define START_X 44
#define START_Y 45
#define MAX_MONSTER 5

int life = 3; // ����
bool bEnded = false; // ���� ������ ������ ���� ����
string name = ""; // ���� ���۽� �Է¹޴� �̸�
fstream file; // ���Ͽ� �̸��� ������ �Է��ϱ� ���� ���� ����
std::condition_variable cv;
std::mutex g_mutex;

int gameover = 0; // ������ ��� ����� �� 1�� �ٲٱ�

void print_life() { // ���� ��� �Լ�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	int x = X_END + 3;
	gotoxy(x, 1);
	cout << "                  ";
	if (life <= 0) {
		bEnded = true; // ���� �Լ� ����
		file.open("ranking.txt", ios_base::app | ios_base::in);
		string data = name + "/" + to_string(getScore()) + "/";
		file.write(data.c_str(), data.size());
		file.close();
		gameover = 1;
	}
	for (int i = 0; i < life; i++) {
		gotoxy(x, 1);
		cout << "�� ";
		x += 2;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void getName() { // ���� ���۽� �̸� �Է¹޴� �Լ�
	system("cls");
	CursorView(1);
	gotoxy(30, 25);
	cout << "�̸� �Է� : ";
	cin >> name;
	CursorView(0);
	system("cls");
}

int thread_main() {
	getName(); // �̸� �Է¹޴� �Լ� ȣ��
	// ���ӽ� �ʿ��� ���� �ʱ�ȭ
	life = 3;
	gameover = 0;
	bEnded = false;
	setScore();

	// SCORE �۾� ���
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

	// ���� ���� ���
	gotoxy(110, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " : 3��";
	gotoxy(110, 24);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " : 5��";
	gotoxy(110, 25);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " : 7��";
	
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

	// ���� ���
	print_life();

	int my_x = 44, my_y = 45, i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = 2; i < X_END - 1; i++) { // ���� ������ �״� ���� ���
		gotoxy(i, START_Y + 1);
		cout << "��";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	char key;

	CursorView(0); // Ŀ�� �Ⱥ��̰�

	// ���� ���� ����
	Small_Monster* monster[MAX_MONSTER];
	for (int i = 0; i < MAX_MONSTER; i++) {
		monster[i] = new Small_Monster();
		monster[i]->setter(rand() % 71 + 10, rand() % 6 + 1, rand()%3);
		monster[i]->print();
	}

	gotoxy(my_x, my_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "���ݢ�";

	thread thread_monster([&]() { // ���� �������� �Լ�
		// std::unique_lock<std::mutex> lock(g_mutex);
		while (bEnded == false) // true�̸� ������ ���� ����
		{
			for (int i = 0; i < MAX_MONSTER; i++) {
				// ��輱�� ��Ҵ��� üũ
				if (monster[i]->y >= START_Y) {
					delete monster[i];
					monster[i] = new Small_Monster();
					monster[i]->setter(rand() % 61 + 20, rand() % 6 + 1, rand() % 3);
					monster[i]->print();
					life--; // ���� ����
					print_life();
				}
			}
			monster[rand() % MAX_MONSTER]->move(); // ���� �迭 �� �������� ������ ���� ����
			Sleep(100); // 0.1�ʸ��� �ݺ�
		}
	});

	// unique_lock<std::mutex> lock(g_mutex);
	// int current_y[MAX_MONSTER];
	int shoot_x;
	
	while(!gameover) { // ����� �������� ������ �ݺ�
		CursorView(0);
		//g_controller.notify_one();
		key = _getch();
		
		switch (key) {
		case RIGHT:
			if (my_x >= 2 && my_x < 97) {
				//g_mutex.lock();
				main_gotoxy(my_x, my_y);
				printf("   ");
				my_x += 1;
				main_gotoxy(my_x, my_y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("���ݢ�");
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
				printf("���ݢ�");
				//g_mutex.unlock();
			}
			break;
		case 27: // ESC
			bEnded = true;
			thread_monster.join();
			return 0;
		case 32: // SPACE BAR
			shoot_x = my_x + 1;
			for (int i = my_y - 1; i > 1; i--) { // ĳ���� ��ġ���� ������ ��輱����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				main_gotoxy(shoot_x, i - 1);
				cout << "��";
				main_gotoxy(shoot_x, i);
				cout << " ";
				// g_mutex.lock();
				for (int j = 0; j < MAX_MONSTER; j++) {
					if (shoot_x == monster[j]->x && i == monster[j]->y -1) { // ���� �� x��ǥ�� ��ġ�ϴ� ���Ϳ� �Ѿ��� ����� ��
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
			main_gotoxy(shoot_x, 2); cout << " ";
			// g_controller.notify_one();
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