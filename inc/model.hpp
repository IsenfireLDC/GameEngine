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

class Model : public Renderer {
public:
	Model(TermColor);

	virtual void draw(Coord) const = 0;
	virtual void redraw() const;
	//virtual void clear() const;

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
	void setPos(Coord);

protected:
	const Model &model;
	Coord pos;

	mutable bool changed = true;
};

class BasicModel : public Model {
public:
	BasicModel(char, TermColor);

	friend std::ostream& operator<<(std::ostream&, const Model&);
private:
	const char model;
};

#endif
