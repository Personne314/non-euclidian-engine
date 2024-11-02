#include "font.h"

#include <stdexcept>



// Constructeur.
// path : chemin vers le fichier ttf.
// size : taille de la police.
Font::Font(const std::string& path, int size) {
	m_font = TTF_OpenFont(path.c_str(), size);
	if (!m_font) throw(std::runtime_error("Impossible de charger la police \"" + path + "\""));
}

// Destructeur.
Font::~Font() {
	if (m_font) TTF_CloseFont(m_font);
}


// Permet de rendre un texte ASCII de la couleur color.
Surface Font::renderText(const std::string& text, const SDL_Color& color) const {
	SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.c_str(), color);
	SDL_Surface* glyph = SDL_ConvertSurface(surface, surface->format, SDL_PIXELFORMAT_RGBA8888);
	SDL_FreeSurface(surface);
	if (!glyph) throw std::runtime_error(
		"Impossible de rendre la texture correspondant au texte \"" + text + "\""
	);
	return Surface(glyph);
}

// Permet de rendre un texte UTF-8 de la couleur color.
Surface Font::renderUTF8(const std::string& text, const SDL_Color& color) const {
	SDL_Surface* surface = TTF_RenderUTF8_Blended(m_font, text.c_str(), color);
	SDL_Surface* glyph = SDL_ConvertSurface(surface, surface->format, SDL_PIXELFORMAT_RGBA8888);
	SDL_FreeSurface(surface);
	if (!glyph) throw std::runtime_error(
		"Impossible de rendre la texture correspondant au texte \"" + text + "\""
	);
	return Surface(glyph);
}


// Permet de redéfinir la taille de la police d'écriture.
void Font::setFontSize(int size) {
	TTF_SetFontSize(m_font, size);
}

// Permet de définir le style de la police d'écriture.
// Le style est défini par | entre les constantes de FontStyle.
void Font::setFontStyle(int style) {
	TTF_SetFontStyle(m_font, style);
}


// Renvoie le style de la police.
int Font::getFontStyle() const {
	return TTF_GetFontStyle(m_font);
}

// Renvoie la taille d'un texte format ASCII passé en paramètre s'il est rendu 
// via cette police.
void Font::getSizeText(const std::string& path, int& x, int& y) const {
	TTF_SizeText(m_font, path.c_str(), &x, &y);
}

// Renvoie la taille d'un texte format UTF-8 passé en paramètre s'il est rendu
// via cette police.
void Font::getSizeUTF8(const std::string& path, int& x, int& y) const {
	TTF_SizeUTF8(m_font, path.c_str(), &x, &y);
}
