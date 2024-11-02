#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <string>

#include "surface.h"


class FBO;


// Class Texture : Charge une texture OpenGL depuis un fichier image.
class Texture {
public:

	// Constructeur, destructeur.
	Texture();
	Texture(const Surface& surface);
	~Texture();

	// Fonctions de chargement et de nettoyage de la texture.
	void load(const std::string& path);
	void load(const Surface& surface);
	void free();

	// Fonctions de bind et d'unbind.
	void glBind() const;
	void glUnbind() const;

	// Fonction d'enregistrement de la texture.
	void save(const std::string& path) const;

	// Getters.
	int getWidth() const;
	int getHeight() const;

	// Renvoie l'état d'initialisation.
	bool getInitState() const;

	// Autorise l'accès au FBO.
	friend class FBO;

protected:

	// Fonction de chargement depuis des données brutes.
	void load(int width, int height, void* data);

	// Etat d'initialisation.
	bool m_initState;
	
	// Données de la texture.
	GLuint m_id;
	int m_width;
	int m_height;

};



// Bind la texture.
inline void Texture::glBind() const {
	glBindTexture(GL_TEXTURE_2D, m_id);
}

// Unbind la texture.
inline void Texture::glUnbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Renvoie la largeur de la texture.
inline int Texture::getWidth() const {
	return m_width;
}

// Renvoie la hauteur de la texture.
inline int Texture::getHeight() const {
	return m_height;
}

// Renvoie l'état d'initialisation.
inline bool Texture::getInitState() const {
	return m_initState;
}
