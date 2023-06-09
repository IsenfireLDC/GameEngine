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
#include "window.hpp"
#include "entity.hpp"
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

#include "engine.hpp"

static bool running = true;
static Entity *primary;

static std::string message;
/*
static void aExit(Entity *target, int input) {
	if(input == Input::Key::Escape) running = false;
};*/

static void inputHandler(Event *event) {
	InputEvent *inputEvent = (InputEvent*)event;

	message.append(std::to_string(inputEvent->key)+" ");
};

static void actionHandler(Event *event) {
	ActionEvent *actionEvent = (ActionEvent*)event;

	actionEvent->action(primary, actionEvent->input);
};

static void quitHandler(Event *event) {
	QuitEvent *quitEvent = (QuitEvent*)event;

	char strbuf[100];
	sprintf(strbuf, "Received QuitEvent from %p\n", quitEvent->input);
	Engine::log.log(strbuf, LogLevel::Info, "Main");
	quitEvent->input->runThread(false);

	running = false;
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


struct Ticker : ITick {
	std::function<void(void)> tf;

	void tick(Engine::Units::Time t) {
		tf();
	};
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

int gameTest() {
	Engine::log.log("-------------------- Log Start --------------------");
	gen.seed(rd());

	//Create player
	const char nEntType[20] = "Entity";
	EntityType tEntity = EntityType(0, nEntType);
	tEntity.handlers[1] = exHandler;
	const char nPlayer[20] = "Player";
	Entity player = Entity(Entity::origin, &tEntity, nPlayer);
	BasicModel mPlayer = BasicModel('~', TermColor::LIME);
	player.setModel(&mPlayer);

	//Set player as primary
	primary = &player;

	//Create non-player
	const char nNPC[20] = "NPC";
	Entity npc = Entity({3,4}, &tEntity, nNPC);
	BasicModel mNPC = BasicModel('!', TermColor::LIGHT_BLUE | TermColor::BG_GRAY);
	npc.setModel(&mNPC);

	//Create field
	RectArea fieldArea{Coord(), Coord(25, 20)};
	Field field = Field(fieldArea, Coord(2,1));

	//Create player manager
	EntityManager manager = EntityManager(&field);

	//Create window
	//std::vector<const ModelRenderer*> renderers = manager.getRenderers();
	//const std::vector<IModelable*> *modelable = reinterpret_cast<const std::vector<IModelable*>*>(manager.getEntitiesList());
	//Window window = Window(&field, modelable);

	RectArea windowArea = RectArea(Coord(0,0), Coord(25, 20));
	Window window = Window(windowArea, Coord(2,1));

	window.addRenderer(&manager);

	//Create input
	Input input = Input();
	//Action ExitAction = aExit;
	//input.addActionMapping(Input::Key::Escape, ExitAction);

	//Add player to manager
	manager.registerEntity(&player);
	manager.registerEntity(&npc);

	//Render window
	window.show(true);
	window.draw();

	//Test log
	Log testLog{"Test", "./logs/test.log"};
	LogLevel testLogLevel = LogLevel::Debug;
	testLog.log("Testing nested log", LogLevel::Info, "Main");
	testLog << "Testing log insertion operator for message";
	Log::Entry testLogEntry = Log::makeEntry("BaseEntry", testLogLevel, "Main");
	testLog << Log::makeEntry(testLogEntry, "Test log insertion operator for Entry");
	Engine::log.log("Initialization complete", LogLevel::Info, "Main");

	//Print out manager
	std::stringstream sstr{};
	sstr << manager;
	testLog.log(sstr.str(), testLogLevel, "Manager");

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
	window.redraw();

	//Print out list of entities
	std::vector<Entity*> playerList = manager.getEntities();

	testLog.log("Printing entities", testLogLevel, "Main");
	for(unsigned int i = 0; i < playerList.size(); ++i) {
		sstr.str("\t");
		sstr << *playerList[i];
		testLog.log(sstr.str(), testLogLevel, "Main");
	};

	//Get inputs
	testLog.log("Spawning thread...", LogLevel::Info, "Main");
	if(!input.spawnThread()) {
		testLog.log("Failed, exiting", LogLevel::Fatal, "Main");
		return 1;
	};

	//Setup event handling
	//InputEvent
	InputEvent ieType = InputEvent(Input::Key::Null);
	int typeIEID = Engine::eventBus.registerEventType(&ieType);
	Engine::eventBus.registerEventHandler(typeIEID, &inputHandler);
	//ActionEvent
	ActionEvent aeType = ActionEvent(0, 0);
	int typeAEID = Engine::eventBus.registerEventType(&aeType);
	Engine::eventBus.registerEventHandler(typeAEID, &actionHandler);
	//QuitEvent
	QuitEvent qeType = QuitEvent(0);
	int typeQEID = Engine::eventBus.registerEventType(&qeType);
	Engine::eventBus.registerEventHandler(typeQEID, &quitHandler);

	Ticker ticker;
	ticker.tf = [&window, &input, &npc](){
		Engine::eventBus.handleEvents();

		window.setMsg(message.c_str());

		input.callAction(&npc, inputs[randMove(gen)]);
		window.redraw();
	};
	Game game;
	game.add(&ticker);
	game.run(true);

	//Stall main until the game is done
	while(running) std::this_thread::yield();
	game.run(false);

	/*
	while(running) {
		//Event* first = Engine::eventBus.getFirstEvent();
		//const char* info = 0;
		//if(first) info = first->getInfo().c_str();

		Engine::eventBus.handleEvents();
		//if(info) window.setMsg(info);
		window.setMsg(message.c_str());

		input.callAction(&npc, inputs[randMove(gen)]);
		window.render();

		Sleep(100);
	};
	*/

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

int main() {
	int ret = 0;

	ret = gameTest();
	//threadTest2();

	return ret;
}
