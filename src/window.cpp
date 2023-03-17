/*
 * window.cpp
 *
 * Holds scene and entities; renders the screen
 */

#include "render.hpp"

#include "window.hpp"
#include "model.hpp"

#include "log.hpp"
#include "engine.hpp"

BasicModel Window::defaultBorder{'#', TermColor::GRAY};
BasicModel Window::defaultBackground{' ', TermColor::BG_BLACK};

Window::Window(RectArea area, Coord scale, BasicModel *border, BasicModel *background) : border(border), background(background) {
	this->area = area;
	this->scale = scale;

	this->windowBB = this->area.getBoundingBox() * this->scale;

	this->Renderer::setBackground(std::bind(Window::drawBackground, this, std::placeholders::_1));
};


/*
 * Get window size
 */
Coord Window::size() const {
	return this->area.getBoundingBox().high;
};

/*
 * Get window scale
 */
Coord Window::getScale() const {
	return this->scale;
};

/*
 * Get border model
 */
BasicModel* Window::getBorderModel() const {
	return this->border;
};

/*
 * Get background model
 */
BasicModel* Window::getBackgroundModel() const {
	return this->background;
};

void Window::setMsg(const char *msg) {
	this->msg = msg;
};


/*
 * Changes the size of the window
 *
 * Takes Coord with new width and height
 */
void Window::resize(Coord size) {
	this->area = RectArea(Coord(0,0), size);

	this->windowBB = this->area.getBoundingBox() * this->scale;
};

/*
 * Changes the scaling of the window
 */
void Window::setScale(Coord scale) {
	this->scale = scale;

	this->windowBB = this->area.getBoundingBox() * this->scale;
};


/*
 * Changes model for the border
 */
void Window::setBorderModel(BasicModel *border) {
	this->border = border;
};

/*
 * Changes model for the background
 */
void Window::setBackgroundModel(BasicModel *background) {
	this->background = background;
};


/*
 * Adds a renderer to the window
 */
void Window::addRenderer(Renderer *renderer) {
	renderer->setBackground(this->bgFunc);

	this->models.insert(renderer);
};

/*
 * Removes a renderer from the window
 */
void Window::removeRenderer(Renderer *renderer) {
	this->models.erase(renderer);
};

/*
 * Adds all renderers in a vector
 */
void Window::addRenderers(std::vector<Renderer*> &renderers) {
	for(Renderer *renderer : renderers) {
		renderer->setBackground(this->bgFunc);

		this->models.insert(renderer);
	};
};


/*
 * Draw entire window
 */
void Window::draw() const {
	if(!this->visible) return;

	Engine::log.log("Drawing window");

	this->drawBackground(this->windowBB);

	//IModelables (Entities)
	for(const Renderer *m : this->models) {
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

	Engine::log.log("Redrawing window");

	//IModelables (Entities)
	for(const Renderer *m : this->models) {
		m->redraw();
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
 * Clear the window
 */
void Window::clear() const {
	this->bgFunc(this->windowBB);
};


/*
 * Returns the background drawing function
 */
std::function<void(BoundingBox)> Window::getBackground() const {
	return this->bgFunc;
};


/*
 * Sets whether the window is shown
 *
 * TODO: Clear window area
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

	this->visible = visible;
};


void Window::drawBackground(BoundingBox bb) const {
	Renderer::resetTermColor();

	for(short i = bb.low.x; i <= bb.high.x; ++i) {
		for(short j = bb.low.y; j <= bb.high.y; ++j) {
			Coord currentPos = { .x=i, .y=j };
			Renderer::setCursorPos(currentPos);

			if(
				i == this->windowBB.low.x ||
				i == this->windowBB.high.x ||
				j == this->windowBB.low.y ||
				j == this->windowBB.high.y
			) {
				this->border->draw(currentPos);
			} else {
				this->background->draw(currentPos);
			};
		};
	};
};

