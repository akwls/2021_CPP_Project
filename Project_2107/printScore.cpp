#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"

static int score;

void printScore(int point) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	score += point;
	gotoxy(124, 20);
	cout << score << "??";
}

void setScore() {
	score = 0;
}

int getScore() {
	return score;
}