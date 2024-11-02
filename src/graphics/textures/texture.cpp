#include "texture.h"

#include <SDL2/SDL_image.h>

#include "../objects/fbo.h"



// Constructeur.
Texture::Texture() : 
m_initState(false), m_id(0), m_width(0), m_height(0) {}

// Constructeur.
Texture::Texture(const Surface& surface) : 
m_initState(false), m_id(0), m_width(0), m_height(0) {
	load(surface);
}

// Destructeur.
Texture::~Texture() {
	if (m_initState) glDeleteTextures(1, &m_id);
}

#include <iostream>
// Crée une texture à partir d'un fichier image.
void Texture::load(const std::string& path) {
	
	// Charge l'image.
	Surface surface;
	surface.load(path);

	// S'assure qu'elle est au bon format.
	Surface surface_format;
	SDL_Rect rect = {0,0, surface.getWidth(), surface.getHeight()};
	surface_format.createSurface(surface.getWidth(), surface.getHeight());
	surface_format.blitSurface(surface, rect, rect);

	// La converti en texture.
	load(surface_format.getWidth(), surface_format.getHeight(), surface_format.getPixels());

}

// Crée une texture à partir d'une surface.
void Texture::load(const Surface& surface) {
	if (!surface.getInitState()) return;
	load(surface.getWidth(), surface.getHeight(), surface.getPixels());
}

// Vide la texture actuelle.
void Texture::free() {
	if (m_initState) glDeleteTextures(1, &m_id);
	m_initState = false;
	m_id = 0; m_width = 0; m_height = 0;
}


// Fonction d'enregistrement de la texture.
void Texture::save(const std::string& path) const {

	// Récupère les pixels de l'image depuis la VRAM.
	GLubyte* pixels = new GLubyte[m_width*m_height*4];
	glBind();
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glUnbind();

	// Enregistre l'image.
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
		pixels, m_width, m_height, 32, m_width*4, 
		0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
	);
	IMG_SavePNG(surface, path.c_str());

	// Libère la mémoire.
	SDL_FreeSurface(surface);
	delete [] pixels;

}


// Fonction de chargement d'une texture depuis ses dimensions et données brutes.
void Texture::load(int width, int height, void* data) {
	free();

	// Enregistre les dimensions.
	m_width = width;
	m_height = height;

	// Génère la texture.
	glGenTextures(1, &m_id);
	glBind();

		// Enregistre les pixels.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		// Enregistre les paramètres.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Texture initialisée.
	glUnbind();
	m_initState = true;

}
