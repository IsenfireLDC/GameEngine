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
#include "render/static_texture.hpp"
#include "model.hpp"
#include "window.hpp"

#include "entity.hpp"
#include "components/basic_movement.hpp"

#include "level.hpp"
#include "input.hpp"
#include "events.hpp"
#include "log.hpp"

#include "game.hpp"

#include "threads.hpp"

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdio>

#include <string>

#include <sstream>

#include <random>

#include <SDL2/SDL.h>

#include "engine.hpp"

static bool running = true;

static std::string message;

//std::random_device rd;
//std::default_random_engine gen;
//std::uniform_int_distribution<int> randMove(0, 3);
//int inputs[4] = {Input::Key::W, Input::Key::A, Input::Key::S, Input::Key::D};

int gameTest() {
	//Engine::log.setMinLevel(LogLevel::Debug);
	Engine::log.setMinLevel(LogLevel::Info);

	Engine::log.log("-------------------- Log Start --------------------");
	//gen.seed(rd());

	if(!Engine::instance.good()) return 1;

	//Create player
	Entity player{"Player"};

	//TODO: This is kind of wordy; maybe try to streamline?
	StaticTexture playerTexture{"assets/player.tga"};
	Model playerModel{&playerTexture};
	player.createComponent<ModelComponent>(&playerModel);
	player.createComponent<BasicMovementComponent>();

	//Set player entity as the player
	Engine::player = &player;

	//Create non-player
	Entity npc{"NPC", {3,4}};

	StaticTexture npcTexture{"assets/npc.tga"};
	Model npcModel{&npcTexture};
	npc.createComponent<ModelComponent>(&npcModel);


	UpdateController<Update> controller{};

	//Action ExitAction = aExit;
	//input.addActionMapping(Input::Key::Escape, ExitAction);

	//Render window
	Engine::window.show(true);
	Engine::window.draw();

	//Attempt to move player
	Coord testCoord = {20,50};
	Engine::player->pos = testCoord;

	SDL_Delay(1000);

	//Render window
	Engine::window.draw();

	Engine::threadPool.start();

	bool go = true;
	while(go) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) go = false;
		};

		controller.update(0.018f);

		Engine::window.draw();

		SDL_Delay(18);
	};

	//Print out list of entities
	std::vector<std::string> playerList = {
		"Player",
		"NPC"
	};

	std::stringstream sstr;
	Engine::log.log("Printing entities", LogLevel::Info, "Main");
	for(unsigned int i = 0; i < playerList.size(); ++i) {
		sstr.str("\t");
		sstr << Engine::level.findEntity(playerList[i]);
		Engine::log.log(sstr.str(), LogLevel::Info, "Main");
	};

	return 0;
};

void threadTest() {
	ThreadPool tp1{5};

	std::mutex lock;
	ThreadPool::Task task = [&lock](){
		static int x=0, y=0;

		lock.lock();
		if(x > y) ++y;
		else ++x;

		std::cout << "x=" << x << ", y=" << y << std::endl;
		lock.unlock();
	};

	for(int i = 0; i < 10; ++i)
		tp1.add(task);

	tp1.start();

	tp1.join();
};

void threadTest2() {
	//Create thread pool
	ThreadPool tp1{2};

	//Create scheduler
	TaskScheduler<> ts{&tp1};

	using sys_clk = std::chrono::system_clock;
	using time_us = std::chrono::microseconds;

	//Prototype for ticking function (variable, recorded rate)
	int x = 20; //Limit iterations
	ThreadPool::Task task;
	task = [&ts, &task, &x](){
		static time_us period = time_us(1000);
		static sys_clk::time_point lastTime = sys_clk::now();

		sys_clk::time_point time = sys_clk::now();
		time_us time_passed = std::chrono::duration_cast<time_us>(time - lastTime);

		lastTime = time;

		std::cout << "time passed: " << time_passed.count() << "us" << std::endl;

		//As tick sched: Either run tick function or spawn a thread to do so

		for(int i = 0; i < 10000; ++i); //Use time


		//Re-add this to the queue
		int schedP = 2*period.count() - time_passed.count();
		if(schedP < 0) schedP = 0;
		time_us sched_period = time_us(schedP);
		if(x-- > 0) ts.scheduleIn(task, sched_period);
		//Move repetition out of thread pool?
		//Refactor thread pool to repeat items?
	};

	//for(int i=x;i>0;--i) tp1.add(task);
	tp1.add(task);

	tp1.start();

	while(x>0) std::this_thread::yield();

	tp1.join();
};

int main(int argc, char* argv[]) {
	int ret = 0;

	ret = gameTest();
	//threadTest2();

	return ret;
}
