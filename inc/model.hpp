/*
 * model.hpp
 *
 * Contains color and model types
 */

#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "pos.hpp"

#include "render.hpp"
#include "component.hpp"

class Model {
public:
	Model(Texture* = nullptr, Coord = Coord(0,0));

	void setTexture(Texture*);
	Texture* getTexture() const;

	void setOrigin(Coord);
	Coord getOrigin() const;

	//Draw with SDL_RenderCopy

private:
	Texture *texture;
	Coord origin;
};

class ModelComponent : public Component<ModelComponent> {
public:
	ModelComponent(Model*);

	void setModel(Model*);
	Model* getModel() const;

private:
	Model *model;
};

#endif
