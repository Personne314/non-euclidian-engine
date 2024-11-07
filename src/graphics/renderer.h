#pragma once

#include <SDL2/SDL.h>

#include "objects/vao.h"
#include "objects/fbo.h"
#include "objects/shader.h"



// Class Renderer : Used to manage main FBOs. This is useful to simplify the implementation of post rendering.
// Rendering functions can also be build over this class to simplify the rendering process. 
class Renderer {
public:

	// Constructor, destructor.
	Renderer(SDL_Window *window, int w, int h);
	~Renderer();

	// Clear the current FBO.
	void clear();

	// Bind and unbind functions.
	void glBind();
	void glUnbind() const;

	// OpenGL swapWindow for rendering and buffer swapping function. 
	void glSwapWindow() const;
	void swapBuffers();

	// Getters.
	const Texture &getTexture() const;
	const Texture &getDepthTexture() const;
	int getWidth() const;
	int getHeight() const;

	// Returns the Renderer init state.
	bool getInitState() const;

private:

	// Init state.
	bool m_initState;

	// SDL_Window for rendering the content of an FBO.
	SDL_Window *m_window;

	// Main FBOs an id of the activated one.
	FBO m_fbos[2];
	int m_current;

	// Shader and VAO for rendering on the screen.
	Shader m_screen_shader;
	VAO m_screen_vao;

};
