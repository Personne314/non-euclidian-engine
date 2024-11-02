#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "utils/events.h"
#include "game.h"



// Class Window : Permet la création et gestion d'une fenêtre.
class Window {

public :

	// Constructeur, destructeur.
	Window(unsigned int w, unsigned int h, const std::string& name);
	~Window();

	// Lance le jeu si l'initialisation est complète.
	void start();

private :

	// Fonction d'initialisation d'OpenGL.
	bool initGL();

	// Boucle principale.
	void loop();

	// Etat d'initialisation.
	bool m_initState;

	// Attributs de la fenêtre.
	SDL_GLContext m_context;
	SDL_Window* m_window;
	int m_width;
	int m_height;

	// Jeu et gestionnaire d'évènements.
	EventManager m_events;
	std::unique_ptr<Game> m_game;

};
