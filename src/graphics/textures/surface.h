#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



// Class Surface : Permet de manipuler une surface SDL.
class Surface {

public :

	// Constructeur, destructeur.
	Surface(SDL_Surface* surface);
	Surface(Surface& surface);
	Surface();
	~Surface();

	// Fonction de création et de nettoyage.
	void free();
	void createSurface(
		int width, int height, int depth = 32,
		int rmask = 0x000000FF, int gmask = 0x0000FF00, 
		int bmask = 0x00FF0000, int amask = 0xFF000000, int flags = 0
	);

	// Fonctions de manipulation de la surface.
	void convertSurface(Uint32 format = SDL_PIXELFORMAT_RGBA8888);
	void blitSurface(const Surface& surface, SDL_Rect& src, SDL_Rect& dst);
	void fillRect(const SDL_Rect& rect, const SDL_Color& color);

	// Fonctions de chargement et d'enregistrement.
	void load(const std::string& path);
	void save(const std::string& path) const;

	// Renvoie les pixels.
	void* getPixels() const;

	// Renvoie les dimensions de la surface et son rect.
	SDL_Rect getRect() const;
	int getWidth() const;
	int getHeight() const;

	// Renvoie l'état d'initialisation.
	bool getInitState() const;

private :

	// Surface.
	SDL_Surface* m_surface;

};



// Enregistre une surface en fichier image.
inline void Surface::save(const std::string& path) const {
	IMG_SavePNG(m_surface, path.c_str());
}

// Renvoie un pointeur vers les pixels de la surface.
inline void* Surface::getPixels() const {
	return m_surface->pixels;
}

// Renvoie le rect de la surface.
inline SDL_Rect Surface::getRect() const {
	return {0,0, m_surface->w, m_surface->h};
}

// Renvoie la largeur de la surface.
inline int Surface::getWidth() const {
	return m_surface->w;
}

// Renvoie la hauteur de la surface.
inline int Surface::getHeight() const {
	return m_surface->h;
}

// Renvoie l'état d'initialisation.
inline bool Surface::getInitState() const {
	return m_surface != nullptr;
}
