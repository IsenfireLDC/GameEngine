/*
 * TerminalGame.cpp
 *
 *  Created on: Sep 4, 2021
 *      Author: Ben Klemp
 *
 *  Engine for creating game on the windows terminal
 */

//includes
#include "render.hpp"
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
	//Create entity
	Entity entity = Entity(Entity::origin);
	Model mEntity = Model('~', 0b1010);
	entity.setModel(&mEntity);

	//Create field
	Field field = Field(Coord(25, 20), Coord(2,1));

	//Create entity manager
	EntityManager manager = EntityManager(&field);

	//Create window
	Window window = Window(&field, &manager);

	//Add entity to manager
	manager.addEntity(&entity);

	//Render window
	window.render();

	//Attempt to move entity
	Coord testCoord = {2,5};
	manager.moveEntity(&entity, testCoord);

	if(manager.getEntityAt(testCoord) != nullptr) {
		window.setMsg("Moved entity succesfully");
	} else {
		window.setMsg("Failed to move entity");
	};

	Sleep(1000);

	//Render window
	window.render();

	//Print out list of entities
	std::vector<Entity*> entityList = manager.getEntities();

	std::cout << "Printing entities" << std::endl;
	for(unsigned int i = 0; i < entityList.size(); ++i) {
		std::cout << "\t" << *entityList[i] << std::endl;
	};

	return 0;
}
