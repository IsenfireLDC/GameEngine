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

#include <random>

static bool running = true;

static void aExit(Entity *target, int input) {
	if(input == Input::Key::Escape) running = false;
};

static int exHandler(Entity *target, EntityAction action) {
	EntityData d = action.sender->getData();
	d.state += 1;
	action.sender->setData(d);

	d = target->getData();
	d.state += 2;
	target->setData(d);

	return 0;
};

std::random_device rd;
std::default_random_engine gen;
std::uniform_int_distribution<int> randMove(0, 3);
int inputs[4] = {Input::Key::W, Input::Key::A, Input::Key::S, Input::Key::D};

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
	gen.seed(rd());

	//Create player
	const char nEntType[20] = "Entity";
	EntityType tEntity = EntityType(0, nEntType);
	tEntity.handlers[1] = exHandler;
	const char nPlayer[20] = "Player";
	Entity player = Entity(&tEntity, Entity::origin, nPlayer);
	Model mPlayer = Model('~', 0b1010);
	player.setModel(&mPlayer);

	//Create non-player
	const char nNPC[20] = "NPC";
	Entity npc = Entity(&tEntity, {3,4}, nNPC);
	Model mNPC = Model('!', 0b1111100);
	npc.setModel(&mNPC);

	//Create field
	Field field = Field(Coord(25, 20), Coord(2,1));

	//Create player manager
	EntityManager manager = EntityManager(&field);

	//Create window
	Window window = Window(&field, &manager);

	//Create input
	Input input = Input();
	Action ExitAction = aExit;
	input.addActionMapping(Input::Key::Escape, ExitAction);

	//Add player to manager
	manager.registerEntity(&player);
	manager.registerEntity(&npc);

	//Render window
	window.render();

	//Print out manager
	std::cout << manager << std::endl;

	//Attempt to move player
	Coord testCoord = {2,5};
	manager.moveEntity(&player, testCoord);


	if(manager.getEntityAt(testCoord)) {
		window.setMsg("Moved player succesfully");
	} else {
		window.setMsg("Failed to move player");
	};

	Sleep(1000);

	//Render window
	window.render();

	//Print out list of entities
	std::vector<Entity*> playerList = manager.getEntities();

	std::cout << "Printing entities" << std::endl;
	for(unsigned int i = 0; i < playerList.size(); ++i) {
		std::cout << "\t" << *playerList[i] << std::endl;
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

		input.callAction(&player, inScan);

		input.callAction(&npc, inputs[randMove(gen)]);
		window.render();

		Sleep(100);
	};

	return 0;
}
