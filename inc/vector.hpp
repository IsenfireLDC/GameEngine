/*
 * vector.hpp
 *
 * Contains Vector2D datatype
 */

#ifndef _POS_HPP_
#define _POS_HPP_

#include <iostream>

#include <SDL2/SDL_rect.h>

struct Vector2D {
	float x;
	float y;

	Vector2D() {
		this->x = 0;
		this->y = 0;
	};

	Vector2D(float x, float y) {
		this->x = x;
		this->y = y;
	};

	bool operator==(Vector2D a) {
		return this->x == a.x && this->y == a.y;
	};

	friend std::ostream& operator<<(std::ostream &out, const Vector2D &coord) {
		out << "(" << coord.x << ", " << coord.y << ")";
		return out;
	};
};

Vector2D operator+(const Vector2D&, const Vector2D&);
Vector2D operator-(const Vector2D&, const Vector2D&);
Vector2D operator*(const Vector2D&, const Vector2D&);
bool operator==(const Vector2D&, const Vector2D&);
bool operator!=(const Vector2D&, const Vector2D&);

Vector2D& operator+=(Vector2D&, const Vector2D&);
Vector2D& operator-=(Vector2D&, const Vector2D&);
Vector2D& operator*=(Vector2D&, const Vector2D&);

Vector2D operator*(const Vector2D&, const float&);
Vector2D& operator*=(Vector2D&, const float&);
Vector2D operator/(const Vector2D&, const float&);
Vector2D& operator/=(Vector2D&, const float&);

SDL_Rect operator*(const SDL_Rect&, const Vector2D&);
SDL_Rect& operator*=(SDL_Rect&, const Vector2D&);
SDL_FRect operator*(const SDL_FRect&, const Vector2D&);
SDL_FRect& operator*=(SDL_FRect&, const Vector2D&);


#endif
