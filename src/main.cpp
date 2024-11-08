#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"



// Initializing SDL.
bool initSDL() {

	// Initialize all SDL modules.
	std::cout << "SDL2 initialization" << std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "SDL initialization error : " << SDL_GetError() << std::endl;
		return false;

	}
	atexit(SDL_Quit);

	// Initialize SDL_IMG.
	std::cout << "SDL_IMG initialization" << std::endl;
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cerr << "SDL_IMG initialization error : " << IMG_GetError() << std::endl;
		return false;
	}
	atexit(IMG_Quit);

	// Initialize SDL_Mix.
	std::cout << "SDL_Mix initialization" << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL_Mix initialization error : " << Mix_GetError() << std::endl;
		return false;
	}
	atexit(Mix_Quit);

	// Initialize SDL_TTF.
	std::cout << "SDL_TTF initialization" << std::endl;
	if (TTF_Init() < 0) {
		std::cerr << "SDL_TTF initialization error : " << TTF_GetError() << std::endl;
		return false;
	}
	atexit(TTF_Quit);

	// Initialization done.
	return true;

}


// Main function. Initialize SDL, the game and launch it.
int main(int argc, char* argv[]) {
	(void)argc; 
	(void)argv;

	// SDL Initialization.
	if (!initSDL()) return EXIT_FAILURE;
	
	// Recupère les dimensions de l'écran.
	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
		std::cerr << "Error while getting desktop dimensions : " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	// Crée la fenêtre et lance le jeu.
	Window window(dm.w, dm.h, "Non-Euclidian Engine");
	window.start();

}
