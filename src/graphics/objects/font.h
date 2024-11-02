#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "../textures/surface.h"



// Permet de définir le style de la police.
// Redéfinition des constantes de SDL_TTF pour éviter d'avoir à l'inclure.
enum FontStyle {
	FONT_NORMAL			= TTF_STYLE_NORMAL,
	FONT_BOLD			= TTF_STYLE_BOLD,
	FONT_ITALIC			= TTF_STYLE_ITALIC,
	FONT_UNDERLINE		= TTF_STYLE_UNDERLINE,
	FONT_STRIKETHROUGH	= TTF_STYLE_STRIKETHROUGH
};



// Class Font : Permet de charger une police d'écriture TTF_Font et de la manipuler.
class Font {
public:

	// Constructeur, destructeur.
	Font(const std::string& path, int size);
	~Font();

	// Fonctions de rendu.
	Surface renderText(const std::string& text, const SDL_Color& color) const;
	Surface renderUTF8(const std::string& text, const SDL_Color& color) const;

	// Setters.
	void setFontSize(int size);
	void setFontStyle(int style);

	// Getters.
	int getFontStyle() const;
	void getSizeText(const std::string& path, int& x, int& y) const;
	void getSizeUTF8(const std::string& path, int& x, int& y) const;

private:

	// Police d'écriture SDL.
	TTF_Font* m_font;

};
