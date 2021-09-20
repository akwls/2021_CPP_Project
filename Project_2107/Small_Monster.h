#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "shooting_star.h"

using namespace std;

class Small_Monster {
public:
	int x, y;
	int color, score;
	void setter(int x, int y, int color);
	void print();
	void move();
	~Small_Monster();
};