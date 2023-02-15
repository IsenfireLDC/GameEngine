#include "render.hpp"

/*
 * Sets the position of the cursor to pos
 */
void Renderer::setCursorPos(Coord pos) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD)pos);
};

/*
 * Sets the term color to color
 */
void Renderer::setTermColor(TermColor color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
};

/*
 * Sets the term color to light gray
 */
void Renderer::resetTermColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TermColor.GRAY);
};
