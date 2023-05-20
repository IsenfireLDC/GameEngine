/*
 * static_texture.hpp
 *
 * Class for static textures
 */
#ifndef _RENDER_STATIC_TEXTURE_HPP_
#define _RENDER_STATIC_TEXTURE_HPP_

#include "render.hpp"

#include <string>

class StaticTexture : public Texture {
public:
	StaticTexture(std::string);
	~StaticTexture();

	SDL_Texture* getTexture() const;

private:
	SDL_Texture *texture;
};

#endif
