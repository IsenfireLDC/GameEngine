/*
 * pos.hpp
 *
 * Contains Coord datatype
 */

#ifndef _POS_HPP_
#define _POS_HPP_

#include <iostream>

#include <SDL2/SDL_rect.h>

struct Coord {
	float x;
	float y;

	Coord() {
		this->x = 0;
		this->y = 0;
	};

	Coord(float x, float y) {
		this->x = x;
		this->y = y;
	};

	bool operator==(Coord a) {
		return this->x == a.x && this->y == a.y;
	};

	friend std::ostream& operator<<(std::ostream &out, const Coord &coord) {
		out << "(" << coord.x << ", " << coord.y << ")";
		return out;
	};
};

Coord operator+(const Coord&, const Coord&);
Coord operator-(const Coord&, const Coord&);
Coord operator*(const Coord&, const Coord&);
bool operator==(const Coord&, const Coord&);
bool operator!=(const Coord&, const Coord&);

SDL_Rect operator*(const SDL_Rect&, const Coord&);
SDL_Rect operator*=(SDL_Rect&, const Coord&);
SDL_FRect operator*(const SDL_FRect&, const Coord&);
SDL_FRect operator*=(SDL_FRect&, const Coord&);


#endif
