#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"

static int score;

void printScore(int point) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	score += point;
	gotoxy(124, 20);
	cout << score << "Á¡";
}

void setScore() {
	score = 0;
}