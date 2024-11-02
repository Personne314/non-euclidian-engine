#include "window.h"

#include <iostream>
#include <GL/glew.h>

#include "utils/timer.h"



// Constructeur.
Window::Window(unsigned int w, unsigned int h, const std::string& name) : 
m_initState(false), m_context(), m_window(nullptr), m_events(), m_game() {
	std::cout << "Initialisation de la fenêtre..." << std::endl;

	// Enregistre les dimensions.
	m_width = w;
	m_height = h;

	// Crée la fenêtre.
	m_window = SDL_CreateWindow(
		name.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height,
		SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL
	);
	if (!m_window) {
		std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
		return;
	}

	// Initialise OpenGL.
	if (initGL()) {
		std::cout << "Fenêtre initialisée !" << std::endl;

		// Initialise le jeu.
		std::cout << "Initialisation du jeu..." << std::endl;
		m_game = std::make_unique<Game>(m_width, m_height);
		if (!m_game->getInitState()) return;
		else std::cout << "Jeu initialisé !" << std::endl;

		// Initialisation terminée.
		m_initState = true;

	}

}

// Destructeur.
Window::~Window() {
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}



// Lance le jeu si l'initialisation est complète.
void Window::start() {
	std::cout << "Lancement !" << std::endl;
	if (m_initState) loop();
}



// Initialise GLEW et le contexte OpenGL.
bool Window::initGL() {
	std::cout << "Initialisation d'OpenGL..." << std::endl;

	// Ajout des attributs OpenGL.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Création du contexte OpenGL.
	if (!(m_context = SDL_GL_CreateContext(m_window))) {
		std::cerr << "Erreur lors de la création du Context OpenGL : " << SDL_GetError() << std::endl;
		return false;   
	} 
	GLenum initGLEW(glewInit());
	if (initGLEW != GLEW_OK) {
		std::cout << "Erreur lors de l'initialisation de GLEW : "
			<< std::string(reinterpret_cast<const char*>(glewGetErrorString(initGLEW))) << std::endl;
		return false;
	}

	// Active le Depth Test, l'Alpha Blending et définit la couleur de nettoyage.
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	SDL_GL_SetSwapInterval(0);

	// Initialisation terminée.
	std::cout << "OpenGL Initialisée !" << std::endl;
	return true;

}



// Boucle principale du programme.
void Window::loop() {
	Timer timer;
	timer.start();
	while (!m_events.isCloseRequested()) {

		// Update du jeu.
		if (timer.getTime() > (1000.0 / 60)) {
			timer.start();
			m_events.pollEvents();
			m_game->update();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_game->render();
            SDL_GL_SwapWindow(m_window);
		}

		// Endort le thread principal lors des temps d'inactivité.
		SDL_Delay(1);

	}

}
