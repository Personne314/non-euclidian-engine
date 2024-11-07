#include "surface.h"

#include <iostream>



// Constructor.
// The deallocation of the surface passed as a parameter is managed by the object
// and should not be done outside of it.
Surface::Surface(SDL_Surface* surface) : m_surface(surface) {}

// Copy constructor.
// Moves the surface pointer to the new object. The old one is no longer usable.
Surface::Surface(Surface& surface) : m_surface(surface.m_surface) {
	surface.m_surface = nullptr;
}

// Constructor.
Surface::Surface() : m_surface(nullptr) {}

// Destructor.
Surface::~Surface() {
	free();
}


// Clears the surface.
void Surface::free() {
	if (!m_surface) return;
	SDL_FreeSurface(m_surface);
	m_surface = nullptr;
}

// Allows creating an empty surface with predefined masks and parameters.
void Surface::createSurface(int width, int height, int depth, int rmask, int gmask, 
int bmask, int amask, int flags) {
	free();
	m_surface = SDL_CreateRGBSurface(
		flags, width, height, depth, 
		rmask, gmask, bmask, amask
	);
	if (!m_surface) {
		std::cerr << "Error during surface creation (w:" << width << ", h:"
		<< height << ", d:" << depth << ", R:" << rmask << ", G:" << gmask << ", B:" 
		<< bmask << ", A:" << amask << ") : " << IMG_GetError() << std::endl;
	}
}


// Allows converting the surface to a given format.
void Surface::convertSurface(Uint32 format) {
	SDL_Surface* temp = SDL_ConvertSurface(m_surface, m_surface->format, format);
	if (!temp) {
		std::cerr << "Error during surface conversion : " << SDL_GetError() << std::endl;
		return;
	} 
	delete m_surface;
	m_surface = temp;
}

// Blits a surface onto this one.
void Surface::blitSurface(const Surface& surface, SDL_Rect& src, SDL_Rect& dst) {
	if (!surface.getInitState() || !m_surface) return;
	if (SDL_BlitSurface(surface.m_surface, &src, m_surface, &dst)) {
		std::cerr << "Error during surface blit :" << SDL_GetError() << std::endl;
	}
}

// Fills the surface with a color.
void Surface::fillRect(const SDL_Rect& rect, const SDL_Color& color) {
	SDL_FillRect(
		m_surface, &rect, 
		SDL_MapRGBA(m_surface->format, color.r, color.g, color.b, color.a)
	);
}


// Allows loading a surface from an image file.
void Surface::load(const std::string& path) {
	free();
	m_surface = IMG_Load(path.c_str());
	if (!m_surface) {
		std::cerr << "Error during surface loading from the file \"" 
			<< path << "\" : " << IMG_GetError() << std::endl;
	}
}

// Saves a surface as an image file.
void Surface::save(const std::string& path) const {
	IMG_SavePNG(m_surface, path.c_str());
}


// Returns a pointer to the pixels of the surface.
void* Surface::getPixels() const {
	return m_surface->pixels;
}


// Returns the rect of the surface.
SDL_Rect Surface::getRect() const {
	return {0,0, m_surface->w, m_surface->h};
}

// Returns the width of the surface.
int Surface::getWidth() const {
	return m_surface->w;
}

// Returns the height of the surface.
int Surface::getHeight() const {
	return m_surface->h;
}

// Returns the Surface init state.
bool Surface::getInitState() const {
	return m_surface != nullptr;
}
