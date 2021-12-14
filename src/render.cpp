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
	this->modelableList = nullptr;
};

Window::Window(Field *field, const std::vector<IModelable*> *modelableList) {
	this->field = field;
	this->modelableList = modelableList;
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

	//IModelables (Entities)
	for(unsigned int i = 0; i < this->modelableList->size(); ++i) {
		IModelable* modelable = this->modelableList->at(i);
		if(modelable->isDirty()) {
			setPos(this->field->transform(modelable->getLastPos()));
			std::cout << " ";

			setPos(this->field->transform(modelable->getPos()));
			renderModel(modelable->getModel());
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
