#include "render.hpp"

/*
 * Sets the position of the cursor to pos
 */
void Renderer::setCursorPos(Coord pos) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD)pos);
};

/*
 * Sets the position of the cursor to pos
 */
Coord Renderer::getCursorPos() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	return Coord(info.dwCursorPosition);
};

/*
 * Sets the term color to color
 */
void Renderer::setTermColor(unsigned char color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
};

/*
 * Sets the term color to light gray
 */
void Renderer::resetTermColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TermColor::GRAY);
};


//Default coordinate scaling
Coord Renderer::defaultScale{2,1};

/*
 * Sets the background drawing function for the renderer
 */
void Renderer::setBackground(std::function<void(BoundingBox)> bgFunc) {
	this->bgFunc = bgFunc;
};

/*
 * Sets the coordinate scaling for the renderer
 */
void Renderer::setScaling(Coord scale) {
	this->scale = scale;
};


/*
 * Provides default background function
 */
void Renderer::defaultBGFunc(BoundingBox bb) {
	Renderer::resetTermColor();

	for(short i = bb.low.x; i <= bb.high.x; ++i) {
		for(short j = bb.low.y; j <= bb.high.y; ++j) {
			Coord currentPos = { .x=i, .y=j };
			Renderer::setCursorPos(currentPos);

			std::cout << ' ';
		};
	};
};
