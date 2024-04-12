/*
 * field.hpp
 *
 * Contains game field information
 */

#ifndef _FIELD_HPP_
#define _FIELD_HPP_

#include "area.hpp"
#include "vector.hpp"


class Field {
public:
	//Exposed Constants
	static const RectArea defaultArea;
	static const Vector2D defaultScale;

	//Constructors
	Field();
	Field(Area&);
	Field(Area&, Vector2D);

	//Getters
	BoundingBox getBoundingBox() const;
	Vector2D getScale() const;

	//Setters
	void setScale(Vector2D);

	//Queries
	bool contains(Vector2D) const;

	//Operations
	Vector2D transform(Vector2D) const;

private:
	const Area &area;

	Vector2D scale;
};

#endif
