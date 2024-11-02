#include "surface.h"

#include <iostream>



// Constructeur.
// Le free de la surface passé en paramètre est géré par l'objet et ne 
// doit pas être fait en dehors de celle-ci.
Surface::Surface(SDL_Surface* surface) : m_surface(surface) {}

// Constructeur de copie.
// Déplace le pointeur de surface vers le nouvel objet. L'ancien n'est
// plus utilisable.
Surface::Surface(Surface& surface) : m_surface(surface.m_surface) {
	surface.m_surface = nullptr;
}

// Constructeur.
Surface::Surface() : m_surface(nullptr) {}

// Destructeur.
Surface::~Surface() {
	free();
}


// Vide la surface.
void Surface::free() {
	if (!m_surface) return;
	SDL_FreeSurface(m_surface);
	m_surface = nullptr;
}

// Permet de créer une surface vide avec des masques et paramètres prédéfinis.
void Surface::createSurface(int width, int height, int depth, int rmask, int gmask, 
int bmask, int amask, int flags) {
	free();
	m_surface = SDL_CreateRGBSurface(
		flags, width, height, depth, 
		rmask, gmask, bmask, amask
	);
	if (!m_surface) {
		std::cerr << "Erreur lors de la création d'une surface (w:" << width << ", h:"
		<< height << ", d:" << depth << ", R:" << rmask << ", G:" << gmask << ", B:" 
		<< bmask << ", A:" << amask << ") : " << IMG_GetError() << std::endl;
	}
}


// Permet de convertir la surface dans un format donné.
void Surface::convertSurface(Uint32 format) {
	SDL_Surface* temp = SDL_ConvertSurface(m_surface, m_surface->format, format);
	if (!temp) {
		std::cerr << "Erreur lors de la conversion d'une surface : " 
			<< SDL_GetError() << std::endl;
		return;
	} 
	delete m_surface;
	m_surface = temp;
}

// Blit une surface sur celle-ci.
void Surface::blitSurface(const Surface& surface, SDL_Rect& src, SDL_Rect& dst) {
	if (!surface.getInitState() || !m_surface) return;
	if (SDL_BlitSurface(surface.m_surface, &src, m_surface, &dst)) {
		std::cerr << "Erreur lors d'un blit de surfaces :" << SDL_GetError() << std::endl;
	}
}


// Remplit la surface avec une couleur.
void Surface::fillRect(const SDL_Rect& rect, const SDL_Color& color) {
	SDL_FillRect(
		m_surface, &rect, 
		SDL_MapRGBA(
			m_surface->format,
			color.r, color.g, color.b, color.a
		)
	);
}


// Permet de charger une surface depuis un fichier image.
void Surface::load(const std::string& path) {
	free();
	m_surface = IMG_Load(path.c_str());
	if (!m_surface) {
		std::cerr << "Erreur lors du chargement d'une surface depuis le fichier \"" 
			<< path << "\" : " << IMG_GetError() << std::endl;
	}
}
