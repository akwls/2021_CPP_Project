#include "shooting_star.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

int printStartMenu() {
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "		 #####  #    #   ####   ####  ##### ##### #####  #   #   #### " << endl;
	cout << "		#       #    #  #    # #    #   #     #     #    ##  #  #     " << endl;
	cout << "		 #####  ######  #    # #    #   #     #     #    # # #  #  ###" << endl;
	cout << "		      # #    #  #    # #    #   #     #     #    #  ##  #    #" << endl;
	cout << "		 #####  #    #   ####   ####    #     #   #####  #   #   #### " << endl;
	cout << "																	  " << endl;
	cout << "			           #####  #####   ####    ####                    " << endl;
	cout << "			          #         #    #    #   #   #                   " << endl;
	cout << "			           #####    #    ######   #  #                    " << endl;
	cout << "			                #   #    #    #   #####                   " << endl;
	cout << "			           #####    #    #    #   #    #                  " << endl;
	cout << endl;
	cout << "					  1. ���� ����						  " << endl;
	cout << "					  2. ���� ���						  " << endl;
	cout << "					  3. ����						      " << endl;
	cout << "					  0. ����						      " << endl;
	int menu;
	while (true) {
		cout << endl << ">> ";
		cin >> menu;
		if (menu >= 0 && menu <= 3) break;
		printf("�ٽ� �Է����ּ���!");
		Sleep(800); // 1�� ����
		for (int i = 0; i < 2; ++i) { // �� ��� ���� �����
			//printf("%c[2K",27);
			cout << "\33[2K"; //line clear
			cout << "\x1b[A"; //up line (ESC [ A) must be support VT100 escape seq
			cout << "\b\b\b\b\b\b\b\b\b\b\b";
		}
	}
	return menu;
}