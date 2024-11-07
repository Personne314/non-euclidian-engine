#pragma once

#include <GL/glew.h>

#include "../textures/texture.h"



// Class FBO : Used to create an FBO containing buffers for a rendered
// image and its corresponding depth buffer.
class FBO {
public:

	// Constructor, destructor.
	FBO(int width, int height);
	~FBO();

	// OpenGL clear function.
	void clear();

	// OpenGL binding functions.
	void glBind();
	void glUnbind() const;

	// Getters.
	int getWidth() const;
	int getHeight() const;
	const Texture &getTexture() const;
	const Texture &getDepthTexture() const;
	
	// Returns the FBO state.
	bool getInitState() const;

private:

	// FBO state.
	bool m_initState;

	// FBO id, color and depth texture.
	GLuint m_fbo;
	Texture m_texture;
	Texture m_depth;

	// Buffers dimentions.
	int m_width;
	int m_height;

};
