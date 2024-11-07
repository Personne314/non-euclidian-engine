#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "../textures/surface.h"



// Constants used to define font style.
enum FontStyle {
	FONT_NORMAL			= TTF_STYLE_NORMAL,
	FONT_BOLD			= TTF_STYLE_BOLD,
	FONT_ITALIC			= TTF_STYLE_ITALIC,
	FONT_UNDERLINE		= TTF_STYLE_UNDERLINE,
	FONT_STRIKETHROUGH	= TTF_STYLE_STRIKETHROUGH
};



// Class Font : Used to load/use a font.
class Font {
public:

	// Constructor, destructor.
	Font(const std::string& path, int size);
	~Font();

	// Function used to render text.
	Surface renderText(const std::string& text, const SDL_Color& color) const;
	Surface renderUTF8(const std::string& text, const SDL_Color& color) const;

	// Setters.
	void setFontSize(int size);
	void setFontStyle(int style);

	// Getters.
	int getFontStyle() const;
	void getSizeText(const std::string& text, int& x, int& y) const;
	void getSizeUTF8(const std::string& text, int& x, int& y) const;

	// Returns the Font state.
	bool getInitState() const;

private:

	// SDL_TTF font.
	TTF_Font* m_font;

};
