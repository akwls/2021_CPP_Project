#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"

void Small_Monster::print() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color);
	shoot_gotoxy(this->x, this->y); cout << "бс";
}
void Small_Monster::setter(int x, int y, int color) {
	this->x = x;
	this->y = y;
	if (color == 0) {
		this->color = 1;
		this->score = 3;
	}
	else if(color == 1) {
		this->color = 13;
		this->score = 5;
	}
	else if(color == 2 ) {
		this->color = 8;
		this->score = 7;
	}
}

void Small_Monster::move() {
	shoot_gotoxy(this->x, this->y); printf(" ");
	this->y++;
	shoot_gotoxy(this->x, this->y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color);
	printf("бс");
}
Small_Monster::~Small_Monster() {
	shoot_gotoxy(this->x, this->y); printf(" ");
}