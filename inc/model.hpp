/*
 * model.hpp
 *
 * Contains color and model types
 */

#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "vector.hpp"

#include "render.hpp"

class Model {
public:
	Model(Texture* = nullptr, Vector2D = Vector2D(0,0));

	void setTexture(Texture*);
	Texture* getTexture() const;

	void setOrigin(Vector2D);
	Vector2D getOrigin() const;

	//Draw with SDL_RenderCopy

private:
	Texture *texture;
	Vector2D origin;
};

#endif
