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
};

int main() {
	//Create default entity
	Entity* entity = new Entity();

	//Create default field
	Field* field = new Field();

	//Create entity manager
	EntityManager manager = EntityManager(field);

	manager.addEntity(entity);

	Coord testCoord = {2,5};
	manager.moveEntity(entity, testCoord);

	if(manager.getEntityAt(testCoord) != nullptr) {
		std::cout << "Moved entity succesfully" << std::endl;
	} else {
		std::cout << "Failed to move entity" << std::endl;
	};

	Entity *const * entityList = manager.getEntities();

	std::cout << "Printing entities" << std::endl;
	for(int i = 0; i < manager.size(); ++i) {
		std::cout << "\t" << *entityList[i] << std::endl;
	};

	return 0;
}
