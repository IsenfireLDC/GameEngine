/*
 * render.cpp
 *
 * Holds scene and entities; renders the screen
 */

#include "render.hpp"

#include "window.hpp"
#include "model.hpp"

Window::Window(RectArea area, Coord scale) : border('#', TermColor::GRAY), background(' ', TermColor::BLACK) {
	this->area = area;
	this->scale = scale;
};

Window::Window(RectArea area, Coord scale, BasicModel border, BasicModel background) : border('#', TermColor::GRAY), background(' ', TermColor::BLACK) {
	this->area = area;
	this->scale = scale;
};

void Window::setMsg(const char *msg) {
	this->msg = msg;
};


/*
 * Draw entire window
 */
void Window::draw() const {
	if(!this->visible) return;

	this->drawBorder();

	//IModelables (Entities)
	for(ModelRenderer *m : this->models) {
		m->draw();
	};


	//Info
	Renderer::resetTermColor();
	Renderer::setCursorPos(Coord(0, this->size().y+1));

	std::cout << this->size() << std::endl;

	Renderer::setTermColor(TermColor::BRIGHT_RED);
	if(this->msg) std::cout << this->msg << std::endl;
	Renderer::resetTermColor();
};

/*
 * Draw changes within window
 */
void Window::redraw() const {
	if(!this->visible) return;

	//IModelables (Entities)
	for(ModelRenderer *m : this->models) {
		if(m->dirty()) m->redraw();
	};


	//Info
	Renderer::resetTermColor();
	Renderer::setCursorPos(Coord(0, this->size().y+1));

	std::cout << this->size() << std::endl;

	Renderer::setTermColor(TermColor::BRIGHT_RED);
	if(this->msg) std::cout << this->msg << std::endl;
	Renderer::resetTermColor();
};

/*
 * Sets whether the window is shown
 */
void Window::show(bool visible) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cInfo;

	GetConsoleCursorInfo(hOut, &cInfo);

	if(!this->visible && visible) {
		//Disable cursor
		cInfo.bVisible = false;
		SetConsoleCursorInfo(hOut, &cInfo);
	} else if(this->visible && !visible) {
		//Enable cursor
		cInfo.bVisible = true;
		SetConsoleCursorInfo(hOut, &cInfo);
	};
};


void Window::drawBorder() const {
	Renderer::resetTermColor();

	BoundingBox bb = this->area.getBoundingBox() * this->scale;;

	for(short i = bb.low.x; i <= bb.high.x; ++i) {
		for(short j = bb.low.y; j <= bb.high.y; ++j) {
			Coord currentPos = { .x=i, .y=j };
			Renderer::setCursorPos(currentPos);

			if(i == bb.low.x || i == bb.high.x || j == bb.low.y || j == bb.high.y) {
				this->border.draw(currentPos);
			} else {
				this->background.draw(currentPos);
			};
		};
	};
};

