/*
 * input.cpp
 *
 * Controls input
 */

#include "input.hpp"

#include "log.hpp"

#include <sstream>

#include <SDL2/SDL_timer.h>

#include "engine.hpp"

static void quitHandler(SDL_KeyboardEvent*);

Log __attribute__((init_priority(160))) Input::log{"Input", "./logs/input.log", LogLevel::Debug};

Input Engine::input{true};


Input::Input(bool defaultQuit) {
	if(!Engine::instance.good()) {
		Input::log.log("SDL not initialized", LogLevel::Fatal, "Input");
		return;
	};

	Input::log.log("Input initialized");

	SDL_AddEventWatch((SDL_EventFilter)Input::listener, this);

	if(defaultQuit)
		this->setHandler(SDL_SCANCODE_ESCAPE, quitHandler);
};

Input::~Input() {
	Input::log.log("Input uninitialized");

	SDL_DelEventWatch(Input::listener, this);
};


/*
 * Sets the handler for a given key
 */
Input& Input::setHandler(SDL_Scancode key, Handler handler) {
	this->handlers[key] = handler;

	return *this;
};


/*
 * Gets the state of a key from the scancode
 */
bool Input::pressed(SDL_Scancode key) {
	if(this->keys.count(key) == 0) {
		int keymax;
		const Uint8 *keyboard = SDL_GetKeyboardState(&keymax);

		if(key > keymax) return false;

		this->keys[key] = keyboard[key];
	};

	if(this->keys.at(key)) {
		std::stringstream key_s;
		key_s << "Key " << key << " pressed";
		Input::log.log(key_s.str());
	} else {
		std::stringstream key_s;
		key_s << "Key " << key << " not pressed";
		Input::log.log(key_s.str());
	};

	return this->keys.at(key);
};

/*
 * Gets the state of a key from the keycode
 */
bool Input::pressed(SDL_Keycode key) {
	return this->pressed(SDL_GetScancodeFromKey(key));
};


/*
 * Get the current key modifiers (ctrl, alt, shift, etc.)
 */
SDL_Keymod Input::getModifiers() const {
	return SDL_GetModState();
};


/*
 * Listener for SDL event watch
 */
int SDLCALL Input::listener(void *v_this, SDL_Event *event) {
	Input::log.log("Key event listener called");

	if(event->type != SDL_KEYDOWN && event->type != SDL_KEYUP) return 1;

	Input *self = (Input*)v_this;

	if(self->keys.count(event->key.keysym.scancode) > 0)
		self->keys[event->key.keysym.scancode] = event->key.state;

	if(self->handlers.count(event->key.keysym.scancode) > 0)
		self->handlers[event->key.keysym.scancode](&event->key);

	std::stringstream key_s;
	key_s << "Key event for " << event->key.keysym.scancode << ":" << event->key.state;

	Input::log.log(key_s.str());

	return 0;
};

/*
 * Gets the state of a key from the scancode
 */
bool Input::isPressed(SDL_Scancode key) const {
	int keymax;
	const Uint8 *keyboard = SDL_GetKeyboardState(&keymax);

	if(key > keymax) return false;

	return keyboard[key];
};



/*************** DEFAULT HANDLERS ***************/

//TODO: Non-functional
static void quitHandler(SDL_KeyboardEvent *event) {
	SDL_QuitEvent quit = {
		.type = SDL_QUIT,
		.timestamp = SDL_GetTicks()
	};

	SDL_PushEvent((SDL_Event*)&quit);
};
