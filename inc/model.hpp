/*
 * model.hpp
 *
 * Contains color and model types
 */

#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "pos.hpp"
#include "area.hpp"

#include "field.hpp"

#include <iostream>
#include <vector>

typedef char TermColor;

class Model {
public:
	Model(TermColor);

	virtual void draw(Coord) const = 0;
	virtual Area getBoundingBox() const = 0;

	 void clear() const;

protected:
	//Model helper methods
	static void setCursorPos(Coord);
	static void setTermColor(TermColor);
	static void resetTermColor();

	TermColor color;
};

class BasicModel : public Model {
public:
	BasicModel(char, TermColor);

	friend std::ostream& operator<<(std::ostream&, const Model&);
private:
	const char model;
};

class FieldModel : public Model {
public:
	FieldModel(const Field&, const BasicModel&, const BasicModel&);

private:
	const Field &field;
	const BasicModel &border;
	const BasicModel &background;
};

#endif
