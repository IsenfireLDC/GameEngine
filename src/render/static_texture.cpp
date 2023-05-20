#include "render/static_texture.hpp"

#include "image.h"

StaticTexture::StaticTexture(std::string filename) {
	//Get image extension
	//Attempt to load module
	//If successful, load file and convert to texture
	//Otherwise, texture = nullptr
};

StaticTexture::~StaticTexture() {
	//Free texture
};


SDL_Texture* StaticTexture::getTexture() const {
	return this->texture;
};
