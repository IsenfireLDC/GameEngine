#ifndef _COLLIDER_HPP_
#define _COLLIDER_HPP_

#include "pos.hpp"

#include <unordered_set>


/*
 * Base class for colliders
 */
class Collider {
public:
	virtual bool isCollidingWith(const class RectCollider*) const = 0;
	virtual bool isCollidingWith(const class CircleCollider*) const = 0;
	virtual bool isCollidingWith(const class PolyCollider*) const = 0;
};


// TODO: How should these get the location?
class RectCollider : public Collider {
public:
	RectCollider(const Vector2D*, Vector2D);
	~RectCollider();

	bool isCollidingWith(const class RectCollider*) const;
	bool isCollidingWith(const class CircleCollider*) const;
	bool isCollidingWith(const class PolyCollider*) const;

private:
	const Vector2D *const position;
	const Vector2D size;
};


class CircleCollider : public Collider {
public:
	CircleCollider(Vector2D*, Vector2D);
	virtual ~CircleCollider();

	bool isCollidingWith(const class RectCollider*) const;
	bool isCollidingWith(const class CircleCollider*) const;
	bool isCollidingWith(const class PolyCollider*) const;
};


class PolyCollider : public Collider {
public:
	PolyCollider(Vector2D*, Vector2D);
	virtual ~PolyCollider();

	bool isCollidingWith(const class RectCollider*) const;
	bool isCollidingWith(const class CircleCollider*) const;
	bool isCollidingWith(const class PolyCollider*) const;
};

#endif
