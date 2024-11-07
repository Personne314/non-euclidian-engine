#include "font.h"

#include <iostream>
#include <stdexcept>



// Constructor.
Font::Font(const std::string& path, int size) {
	m_font = TTF_OpenFont(path.c_str(), size);
	if (!m_font) std::cerr << "Unable to load font \"" << path << "\"" << std::endl;
}

// Destructor.
Font::~Font() {
	if (m_font) TTF_CloseFont(m_font);
}


// Renders a string on a surface.
Surface Font::renderText(const std::string& text, const SDL_Color& color) const {
	SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.c_str(), color);
	if (!surface) throw std::runtime_error("Unable to render the string \"" + text + "\" surface to RGBA8888");
	SDL_Surface* glyph = SDL_ConvertSurface(surface, surface->format, SDL_PIXELFORMAT_RGBA8888);
	SDL_FreeSurface(surface);
	if (!glyph) throw std::runtime_error("Unable to render the string \"" + text + "\"");
	return Surface(glyph);
}

// Renders a UTF-8 string on a surface.
Surface Font::renderUTF8(const std::string& text, const SDL_Color& color) const {
	SDL_Surface* surface = TTF_RenderUTF8_Blended(m_font, text.c_str(), color);
	if (!surface) throw std::runtime_error("Unable to render the UTF-8 string \"" + text + "\"");
	SDL_Surface* glyph = SDL_ConvertSurface(surface, surface->format, SDL_PIXELFORMAT_RGBA8888);
	SDL_FreeSurface(surface);
	if (!glyph) throw std::runtime_error("Unable to convert the UTF-8 string \"" + text + "\" surface to RGBA8888");
	return Surface(glyph);
}


// Sets the font size.
void Font::setFontSize(int size) {
	TTF_SetFontSize(m_font, size);
}

// Sets the font style.
// style is a combinaison of FontStyle constants.
void Font::setFontStyle(int style) {
	TTF_SetFontStyle(m_font, style);
}


// Returns the current font style.
int Font::getFontStyle() const {
	return TTF_GetFontStyle(m_font);
}

// Returns the size in pixel needed to render the string.
void Font::getSizeText(const std::string& text, int& x, int& y) const {
	TTF_SizeText(m_font, text.c_str(), &x, &y);
}

// Returns the size in pixel needed to render the UTF-8 string. 
void Font::getSizeUTF8(const std::string& text, int& x, int& y) const {
	TTF_SizeUTF8(m_font, text.c_str(), &x, &y);
}


// Returns the Font state.
bool Font::getInitState() const {
	return !m_font;
}
