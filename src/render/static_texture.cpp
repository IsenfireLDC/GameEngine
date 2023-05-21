#include "render/static_texture.hpp"

#include "log.hpp"

#include "image.h"

#include "engine.hpp"

StaticTexture::StaticTexture(std::string filename) {
	//Get image extension
	int ext_p = filename.find_last_of(".") + 1;
	std::string ext = filename.substr(ext_p);

	//Use builtin .bmp handling
	if(ext == "bmp") {
		SDL_Surface *surface = SDL_LoadBMP(filename.c_str());

		if(!surface) {
			Engine::log.log("Failed to load bmp", LogLevel::Error, "StaticTexture");
			return;
		};
		this->texture = SDL_CreateTextureFromSurface(Engine::renderer, surface);

		//Free temporary surface
		SDL_FreeSurface(surface);
	//Attempt to load module
	} else {
		ImageModule mod = loadModule(ext.c_str());

		//If no module exists, return
		if(!mod.read) {
			//TODO: Add extension
			Engine::log.log("No module found to load texture file", LogLevel::Error, "StaticTexture");
			return;
		};

		//Load data
		ImageData data = mod.read(filename.c_str());
		ImageSurface isurface = image_toSurface(data);
		deleteImageData(data);

		if(!isurface.surface) {
			Engine::log.log("Failed to load other file", LogLevel::Error, "StaticTexture");
			return;
		};
		this->texture = SDL_CreateTextureFromSurface(Engine::renderer, isurface.surface);

		//Free temporary surface
		SDL_FreeSurface(isurface.surface);
		deleteImageData(isurface.data);
	};
};

StaticTexture::~StaticTexture() {
	//Free texture
	if(this->texture) {
		SDL_DestroyTexture(this->texture);
	};
};


SDL_Texture* StaticTexture::getTexture() const {
	return this->texture;
};
