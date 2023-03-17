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
	virtual void draw(Coord) const = 0;
	virtual void redraw(Coord) const = 0;

	virtual const BoundingBox getBoundingBox() const = 0;
};

class BasicModel : public Model {
public:
	BasicModel(char, unsigned char);

	void draw(Coord) const;
	void redraw(Coord) const;
	const BoundingBox getBoundingBox() const;

	friend std::ostream& operator<<(std::ostream&, const BasicModel&);
private:
	const char model;
	const unsigned char color;
};


class ModelRenderer : public Renderer {
public:
	ModelRenderer(const Model*);

	const Model* getModel() const;
	void setModel(const Model*);

	BoundingBox getLastRegion() const;

	void draw() const;
	void redraw() const;
	void clear() const;

	bool dirty() const;
	void move(Coord);

protected:
	const Model *model;
	Coord pos;

	mutable Coord lastPos;
};

#endif
