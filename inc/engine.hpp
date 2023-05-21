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
 * events.hpp
 *
 * Global event bus
 */
#ifdef _EVENTS_HPP_
#ifndef _ENGINE_EVENTS
#define _ENGINE_EVENTS
	extern Events eventBus;
#endif
#endif

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
 * ???.hpp
 *
 * SDL Window; SDL Renderer
 */
//#ifdef _???_HPP_
#ifdef SDL_video_h_
#ifndef _ENGINE_WINDOW
#define _ENGINE_WINDOW
	extern SDL_Window *window;
#endif
#endif

#ifdef SDL_render_h_
#ifndef _ENGINE_RENDERER
#define _ENGINE_RENDERER
	extern SDL_Renderer *renderer;
#endif
#endif
//#endif

};
