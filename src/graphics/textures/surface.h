#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



// Class Surface : This is used to create and use a SDL_Surface.
class Surface {

public :

	// Constructor, destructor.
	Surface(SDL_Surface* surface);
	Surface(Surface& surface);
	Surface();
	~Surface();

	// Create and clean functions.
	void free();
	void createSurface(
		int width, int height, int depth = 32,
		int rmask = 0x000000FF, int gmask = 0x0000FF00, 
		int bmask = 0x00FF0000, int amask = 0xFF000000, int flags = 0
	);

	// Surface operations.
	void convertSurface(Uint32 format = SDL_PIXELFORMAT_RGBA8888);
	void blitSurface(const Surface& surface, SDL_Rect& src, SDL_Rect& dst);
	void fillRect(const SDL_Rect& rect, const SDL_Color& color);

	// Save and load functions.
	void load(const std::string& path);
	void save(const std::string& path) const;

	// Returns the pixels of the Surface.
	void* getPixels() const;

	// Returns the dimensions of the Surface.
	SDL_Rect getRect() const;
	int getWidth() const;
	int getHeight() const;

	// Returns the Surface init state.
	bool getInitState() const;

private :

	// Pointer to the SDL_Surface.
	SDL_Surface* m_surface;

};
