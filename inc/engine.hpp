/*
 * THIS FILE MUST BE INCLUDED AFTER ALL OTHER INCLUDES
 * Do not include in header files
 *
 * Adds Engine namespace items based on already included files
 *
 * Engine constants and globals
 */

#include "engine_types.hpp"

namespace Engine {

/*
 * log.hpp
 *
 * Global log
 */
#ifdef _LOG_HPP_
#ifndef _ENGINE_LOG
#define _ENGINE_LOG
	extern Log log;
#endif
#endif

/*
 * input.hpp
 *
 * Global input state
 */
#ifdef _INPUT_HPP_
#ifndef _ENGINE_INPUT
#define _ENGINE_INPUT
	extern Input input;
#endif
#endif

/*
 * threads.hpp
 *
 * Default thread pool
 */
#ifdef _THREADS_HPP_
#ifndef _ENGINE_THREADS
#define _ENGINE_THREADS
	extern ThreadPool threadPool;
#endif
#endif

/*
 * level.hpp
 *
 * Default level
 */
#ifdef _LEVEL_HPP_
#ifndef _ENGINE_LEVEL
#define _ENGINE_LEVEL
	extern Level level;
#endif
#endif

/*
 * entity.hpp
 *
 * Player entity
 */
#ifdef _ENTITY_HPP_
#ifndef _ENGINE_PLAYER
#define _ENGINE_PLAYER
	extern Entity *player;
#endif
#endif

/*
 * window.hpp
 *
 * SDL window and renderer
 */
#ifdef _WINDOW_HPP_
#ifndef _ENGINE_WINDOW
#define _ENGINE_WINDOW
	extern Window window;
#endif
#endif

};
