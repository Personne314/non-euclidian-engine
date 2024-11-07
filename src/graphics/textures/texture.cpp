#include "texture.h"

#include <SDL2/SDL_image.h>

#include "../objects/fbo.h"



// Constructor.
Texture::Texture() : 
m_initState(false), m_id(0), m_width(0), m_height(0) {}

// Constructor.
Texture::Texture(const Surface& surface) : 
m_initState(false), m_id(0), m_width(0), m_height(0) {
	load(surface);
}

// Destructor.
Texture::~Texture() {
	if (m_initState) glDeleteTextures(1, &m_id);
}

// Load a texture from a file.
void Texture::load(const std::string& path) {
	
	// Load the texture on a surface.
	Surface surface;
	surface.load(path);

	// Formats it.
	Surface surface_format;
	SDL_Rect rect = {0,0, surface.getWidth(), surface.getHeight()};
	surface_format.createSurface(surface.getWidth(), surface.getHeight());
	surface_format.blitSurface(surface, rect, rect);

	// Then converts it into an OpenGL texture.
	load(surface_format.getWidth(), surface_format.getHeight(), surface_format.getPixels());

}

// Create a texture from a surface.
void Texture::load(const Surface& surface) {
	if (!surface.getInitState()) return;
	load(surface.getWidth(), surface.getHeight(), surface.getPixels());
}

// Clears the current texture.
void Texture::free() {
	if (m_initState) glDeleteTextures(1, &m_id);
	m_initState = false;
	m_id = 0; m_width = 0; m_height = 0;
}


// Saves the texture in a file.
void Texture::save(const std::string& path) const {

	// Gets texture pixels from VRAM.
	GLubyte* pixels = new GLubyte[m_width*m_height*4];
	glBind();
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glUnbind();

	// Converts this data into a surface, then save it in a file.
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
		pixels, m_width, m_height, 32, m_width*4, 
		0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
	);
	IMG_SavePNG(surface, path.c_str());

	// Cleans memory.
	SDL_FreeSurface(surface);
	delete [] pixels;

}


// Loading function from raw data.
void Texture::load(int width, int height, void* data) {
	free();

	// Save the dimensions.
	m_width = width;
	m_height = height;

	// Create the texture.
	glGenTextures(1, &m_id);
	glBind();

		// Save the prixels.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		// Sets the texture parameters.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// The texture is initialized.
	glUnbind();
	m_initState = true;

}



// Binds the texture.
void Texture::glBind() const {
	glBindTexture(GL_TEXTURE_2D, m_id);
}

// Unbinds the texture.
void Texture::glUnbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Returns texture width.
int Texture::getWidth() const {
	return m_width;
}

// Returns texture height.
int Texture::getHeight() const {
	return m_height;
}

// Returns the Texture init state.
bool Texture::getInitState() const {
	return m_initState;
}
