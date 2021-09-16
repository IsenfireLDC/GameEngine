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
#include "input.hpp"

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdio>
//#include <random>
//#include <ctime>

static bool running = true;

static void aExit(Entity *target, int input) {
	if(input == Input::Key::Escape) running = false;
};

void getKBCodes() {
	int kb_code = 0;

	std::cout << "Hit a key" << std::endl;

	while(true) {
		kb_code = Input::getInputKey();

		if(kb_code != 0) std::cout << kb_code << std::endl;

		if(kb_code == 27) break;

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

	//Create input
	Input input = Input();
	Action ExitAction = aExit;
	input.addActionMapping(Input::Key::Escape, ExitAction);

	//Add entity to manager
	manager.registerEntity(&entity);

	//Render window
	window.render();

	//Print out manager
	std::cout << manager << std::endl;

	//Attempt to move entity
	Coord testCoord = {2,5};
	manager.moveEntity(&entity, testCoord);


	if(manager.getEntityAt(testCoord)) {
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

	//Get inputs
	char keyMsg[20];
	while(running) {
		int inKey = Input::getInputKey();
		int inScan = Input::getInputScan();
		if(inScan != 0) {
			sprintf(keyMsg, "%c : %08d", inKey, inScan);
			window.setMsg(keyMsg);
		};

		input.callAction(&entity, inScan);
		window.render();

		Sleep(100);
	};

	return 0;
}
