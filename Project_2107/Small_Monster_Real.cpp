#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"

void Small_Monster::print() {
	gotoxy(this->x - 1, this->y); cout << " �� ";
}
void Small_Monster::setter(int x, int y) {
	this->x = x;
	this->y = y;
}

void Small_Monster::move() {
	gotoxy(this->x, this->y); cout << " ";
	this->y++;
	gotoxy(this->x - 1, this->y); cout << " �� ";
}
Small_Monster::~Small_Monster() {
	gotoxy(this->x, this->y); cout << " ";
}