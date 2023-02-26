/*
 * model.hpp
 *
 * Contains color and model types
 */

#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "pos.hpp"
#include "area.hpp"

#include "render.hpp"

#include <iostream>
#include <vector>

class Model {
public:
	Model(TermColor);

	virtual void draw(Coord) const = 0;

	virtual const BoundingBox getBoundingBox() const = 0;

protected:
	TermColor color;
};

class ModelRenderer : public Renderer {
public:
	ModelRenderer(const Model&);

	void draw() const;
	void redraw() const;

	bool dirty() const;
	void move(Coord);

protected:
	const Model &model;
	Coord pos;

	mutable Coord lastPos;
};

class BasicModel : public Model {
public:
	BasicModel(char, TermColor);

	void draw(Coord) const;
	const BoundingBox getBoundingBox() const;

	friend std::ostream& operator<<(std::ostream&, const BasicModel&);
private:
	const char model;
};

#endif
