#pragma once
#include "Small_Monster.h"

void printScript();
void printRanking();
int printStartMenu();
void mainGame();
void CursorView(char);
void gotoxy(int, int);
void printRanking();
void left(int my_x, int my_y, Small_Monster* monster[]);
void center(int my_x, int my_y, Small_Monster* monster[]);
void right(int my_x, int my_y, Small_Monster* monster[]);
int printGameOver();
void printScore(int);
void setScore();
void thread_main();
void thread_move(int& my_x, int& my_y, char& key);
void thread_shoot(int &x, int &y, char& key, Small_Monster* monster[]);
int getScore();
void main_gotoxy(int, int);
void shoot_gotoxy(int, int);
