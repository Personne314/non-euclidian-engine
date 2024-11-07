#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <string>

#include "surface.h"


class FBO;


// Class Texture : Load an OpenGL texture from a file.
class Texture {
public:

	// Constructor, destructor.
	Texture();
	Texture(const Surface& surface);
	~Texture();

	// Load and clean functions.
	void load(const std::string& path);
	void load(const Surface& surface);
	void free();

	// Bind and Unbind function.
	void glBind() const;
	void glUnbind() const;

	// Save function.
	void save(const std::string& path) const;

	// Getters.
	int getWidth() const;
	int getHeight() const;

	// Returns the Texture init state.
	bool getInitState() const;

	// Gives acces to the FBO class. This is used to initialise the pixel 
	// and depth buffers in the FBO but still have access the the Texture wrapper.
	friend class FBO;

protected:

	// Loading function from raw data.
	void load(int width, int height, void* data);

	// Texture init state.
	bool m_initState;
	
	// Texture data.
	GLuint m_id;
	int m_width;
	int m_height;

};
