/*
 * render.cpp
 *
 * Holds scene and entities; renders the screen
 */

#include "render.hpp"

#include <windows.h>

static void setPos(Coord pos) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD)pos);
};

static void setColor(Color color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
};

static void resetColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0b1111);
};

static void renderModel(const Model* model) {
	setColor(model->color);
	std::cout << model->model;
};

Window::Window() {
	this->field = nullptr;
	this->entities = nullptr;
};

Window::Window(Field *field, EntityManager *entities) {
	this->field = field;
	this->entities = entities;
};

void Window::setMsg(const char *msg) {
	this->msg = msg;
};

void Window::render() {
	this->render(this->firstRender);

	this->firstRender = false;
};

void Window::render(bool firstRender) const {
	//Disable cursor
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cInfo;

	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);

	Coord size = this->field->getArea()->getRect().c2;
	size = size * this->field->getScale();

	//Field
	if(firstRender) {
		for(short i = 0; i <= size.x; ++i) {
			for(short j = 0; j <= size.y; ++j) {
				setPos((Coord){i,j});
				if(i == 0 || i == size.x || j == 0 || j == size.y) {
					renderModel(this->mBorder);
				} else {
					renderModel(this->mBackground);
				};
			};
		};
	};

	//Entities
	std::vector<Entity*> entityList = this->entities->getEntities();
	for(unsigned int i = 0; i < entityList.size(); ++i) {
		Entity* entity = entityList[i];
		if(entity->changed()) {
			setPos(this->field->transform(entity->getLastPos()));
			std::cout << " ";

			setPos(this->field->transform(entity->getPos()));
			renderModel(entity->getModel());
		};
	};


	//Info
	resetColor();
	setPos(Coord(0, size.y+1));

	std::cout << size << std::endl;

	setColor(0b1001);
	if(this->msg) std::cout << this->msg << std::endl;
	resetColor();

	//Enable cursor
	cInfo.bVisible = true;
	SetConsoleCursorInfo(hOut, &cInfo);
};
