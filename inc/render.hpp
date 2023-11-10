/*
 * render.hpp
 *
 * Draws scene and entities on the screen
 */

#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

/*
 * Interface for classes that handle rendering
 */
class Renderer {
public:
	virtual void draw(SDL_Renderer*, SDL_Rect*) const = 0;
};

class Surface {
public:
	virtual SDL_Surface* getSurface() const = 0;
};

class Texture {
public:
	virtual SDL_Texture* getTexture() const = 0;
};

#endif
