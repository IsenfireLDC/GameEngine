/*
 * TerminalGame.cpp
 *
 *  Created on: Sep 4, 2021
 *      Author: Ben Klemp
 *
 *  Engine for creating game on the windows terminal
 */

//includes
#include "entity.hpp"

#include <windows.h>
#include <iostream>
#include <conio.h>
//#include <random>
//#include <ctime>

void getKBCodes() {
	int kb_code = 0;

	std::cout << "Hit a key" << std::endl;

	while(true) {
		if(kbhit()) {
			std::cout << "Key hit: ";
			kb_code = getch();

			std::cout << kb_code << std::endl << std::flush;

			//Break after hitting escape
			if (kb_code == 27) break;
		}
		Sleep(100);
	}
}

int main() {
	getKBCodes();
}
