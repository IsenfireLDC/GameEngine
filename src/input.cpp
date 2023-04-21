/*
 * input.cpp
 *
 * Controls input
 */

#include "input.hpp"

#include "log.hpp"

#include <sstream>

#include "engine.hpp"

Log Input::log{"Input", "./logs/input.log", LogLevel::Debug};

Input Engine::input{};


Input::Input() : scancodes(), keycodes(), modifiers(KMOD_NONE) {};

Input::~Input() {};


/*
 * Used to set the state of the key
 */
void Input::setState(SDL_Keysym &key, bool pressed) {
	this->scancodes[key.scancode] = pressed;
	this->keycodes[key.sym] = pressed;

	this->modifiers = (SDL_Keymod)key.mod;

	std::stringstream key_s;
	key_s << "Key " << key.scancode << " set to state " << pressed;

	Input::log << key_s.str();
};


/*
 * Gets the state of a key from the scancode
 */
bool Input::pressed(SDL_Scancode key) const {
	return this->scancodes.at(key);
};

/*
 * Gets the state of a key from the keycode
 */
bool Input::pressed(SDL_Keycode key) const {
	return this->keycodes.at(key);
};


/*
 * Get the current key modifiers (ctrl, alt, shift, etc.)
 */
SDL_Keymod Input::getModifiers() const {
	return this->modifiers;
};
