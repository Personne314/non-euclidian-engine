#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "utils/events.h"
#include "game.h"



// Class Window : Creates a windows with an OpenGL context.
class Window {

public :

	// Constructor, destructor.
	Window(unsigned int w, unsigned int h, const std::string& name);
	~Window();

	// Launch the game.
	void start();

private :

	// OpenGL initialization function.
	bool initGL();

	// Main loop.
	void loop();

	// Init state.
	bool m_initState;

	// Window attributes.
	SDL_GLContext m_context;
	SDL_Window* m_window;
	int m_width;
	int m_height;

	// Game and event manager.
	EventManager m_events;
	std::unique_ptr<Game> m_game;

};
