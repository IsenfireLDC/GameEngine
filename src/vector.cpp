/*
 * pos.cpp
 *
 * Contains Vector2D datatype
 */

#include "vector.hpp"


Vector2D operator+(const Vector2D& c1, const Vector2D& c2) {
	return Vector2D(c1.x+c2.x, c1.y+c2.y);
};

Vector2D operator-(const Vector2D& c1, const Vector2D& c2) {
	return Vector2D(c1.x-c2.x, c1.y-c2.y);
};

Vector2D operator*(const Vector2D& c1, const Vector2D& c2) {
	return Vector2D(c1.x*c2.x, c1.y*c2.y);
};

bool operator==(const Vector2D& c1, const Vector2D& c2) {
	return c1.x == c2.x && c1.y == c2.y;
};

bool operator!=(const Vector2D& c1, const Vector2D& c2) {
	return c1.x != c2.x || c1.y != c2.y;
};


Vector2D& operator+=(Vector2D &c1, const Vector2D &c2) {
	c1.x += c2.x;
	c1.y += c2.y;
	return c1;
};

Vector2D& operator-=(Vector2D &c1, const Vector2D &c2) {
	c1.x -= c2.x;
	c1.y -= c2.y;
	return c1;
};

Vector2D& operator*=(Vector2D &c1, const Vector2D &c2) {
	c1.x *= c2.x;
	c1.y *= c2.y;
	return c1;
};


Vector2D operator*(const Vector2D &c, const float &f) {
	return Vector2D(c.x * f, c.y * f);
};

Vector2D& operator*=(Vector2D &c, const float &f) {
	c.x *= f;
	c.y *= f;
	return c;
};

Vector2D operator/(const Vector2D &c, const float &f) {
	return Vector2D(c.x / f, c.y / f);
};

Vector2D& operator/=(Vector2D &c, const float &f) {
	c.x /= f;
	c.y /= f;
	return c;
};


SDL_Rect operator*(const SDL_Rect& r, const Vector2D& c) {
	//Rudimentary scaling
	SDL_Rect rect = {
		.x = (int)(r.x * c.x),
		.y = (int)(r.y * c.y),
		.w = (int)(r.w * c.x),
		.h = (int)(r.h * c.y)
	};

	return rect;
};

SDL_Rect& operator*=(SDL_Rect& r, const Vector2D& c) {
	//Rudimentary scaling
	r.x = (int)(r.x * c.x);
	r.y = (int)(r.y * c.y);
	r.w = (int)(r.w * c.x);
	r.h = (int)(r.h * c.y);

	return r;
};

SDL_FRect operator*(const SDL_FRect& r, const Vector2D& c) {
	//Rudimentary scaling
	SDL_FRect rect = {
		.x = r.x * c.x,
		.y = r.y * c.y,
		.w = r.w * c.x,
		.h = r.h * c.y
	};

	return rect;
};

SDL_FRect& operator*=(SDL_FRect& r, const Vector2D& c) {
	//Rudimentary scaling
	r.x = r.x * c.x;
	r.y = r.y * c.y;
	r.w = r.w * c.x;
	r.h = r.h * c.y;

	return r;
};
