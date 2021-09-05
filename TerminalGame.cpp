/*
 * TerminalGame.cpp
 *
 *  Created on: Sep 4, 2021
 *      Author: Ben Klemp
 *
 *  Engine for creating game on the windows terminal
 */

//includes
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <random>
#include <ctime>

int main() {
	int kb_code = 0;

	while(true) {
		if(kbhit()) {
			kb_code = getch();

			std::cout << "Key hit: " << kb_code << std::endl;
		}
	}
}
