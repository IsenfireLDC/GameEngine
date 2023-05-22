/*
 * pos.cpp
 *
 * Contains Coord datatype
 */

#include "pos.hpp"


Coord operator+(const Coord& c1, const Coord& c2) {
	return Coord(c1.x+c2.x, c1.y+c2.y);
};

Coord operator-(const Coord& c1, const Coord& c2) {
	return Coord(c1.x-c2.x, c1.y-c2.y);
};

Coord operator*(const Coord& c1, const Coord& c2) {
	return Coord(c1.x*c2.x, c1.y*c2.y);
};

bool operator==(const Coord& c1, const Coord& c2) {
	return c1.x == c2.x && c1.y == c2.y;
};

bool operator!=(const Coord& c1, const Coord& c2) {
	return c1.x != c2.x || c1.y != c2.y;
};


SDL_Rect operator*(const SDL_Rect& r, const Coord& c) {
	//Rudimentary scaling
	SDL_Rect rect = {
		.x = (int)(r.x * c.x),
		.y = (int)(r.y * c.y),
		.w = (int)(r.w * c.x),
		.h = (int)(r.h * c.y)
	};

	return rect;
};

SDL_Rect operator*=(SDL_Rect& r, const Coord& c) {
	//Rudimentary scaling
	r.x = (int)(r.x * c.x),
	r.y = (int)(r.y * c.y),
	r.w = (int)(r.w * c.x),
	r.h = (int)(r.h * c.y)

	return r;
};

SDL_FRect operator*(const SDL_FRect& r, const Coord& c) {
	//Rudimentary scaling
	SDL_FRect rect = {
		.x = r.x * c.x,
		.y = r.y * c.y,
		.w = r.w * c.x,
		.h = r.h * c.y
	};

	return rect;
};

SDL_FRect operator*=(SDL_FRect& r, const Coord& c) {
	//Rudimentary scaling
	r.x = r.x * c.x,
	r.y = r.y * c.y,
	r.w = r.w * c.x,
	r.h = r.h * c.y

	return r;
};
