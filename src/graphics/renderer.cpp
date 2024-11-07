#include "renderer.h"



// Constructor.
Renderer::Renderer(SDL_Window *window, int w, int h) : 
m_initState(false), m_window(window), m_fbos{FBO(w,h), FBO(w,h)}, m_current(0), 
m_screen_shader(
	"GameData/shaders/screen.vert", "GameData/shaders/screen.frag", 
	{{0,"in_coord"}, {1,"in_tex_coord"}}
) {

	// Build the VAO for screen rendering.
	float vertices[12] = {-1,-1, 1,1, -1,1, -1,-1, 1,-1, 1,1};
	float tex_vertices[12] = {0,1, 1,0, 0,0, 0,1, 1,1, 1,0};
	void* data[2] = {vertices, tex_vertices};
	int sizes[2] = {2,2};
	int array_ids[2] = {0,1};
	int gl_types[2] = {GL_FLOAT, GL_FLOAT};
	m_screen_vao.pushData(data, sizes, array_ids, gl_types, 6,2);

	// The renderer is build.
	m_initState = m_fbos[0].getInitState() && m_fbos[1].getInitState();

}

// Destructor.
Renderer::~Renderer() {}


// Clears the current bound FBO.
// Binds the active FBO but doesn't unbind it.
void Renderer::clear() {
	glBind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// Binds the active FBO.
void Renderer::glBind() {
	m_fbos[m_current].glBind();
}

// Unbinds the active FBO.
void Renderer::glUnbind() const {
	m_fbos[m_current].glUnbind();
}

// Renders the active FBO on the screen.
// Unbinds the active FBO.
void Renderer::glSwapWindow() const {
	
	// Unbinds the active FBO and clears the screen.
	glUnbind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
	// Renders the content of the FBO on the screen.
	m_screen_shader.glUse();
		m_screen_vao.glBind();
			m_fbos[m_current].getTexture().glBind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			m_fbos[m_current].getTexture().glUnbind();
		m_screen_vao.glUnbind();
	m_screen_shader.glUnuse();

	// Swaps the window buffers.
	SDL_GL_SwapWindow(m_window);

}

// Swaps the active and unactive FBOs.
void Renderer::swapBuffers() {
	m_current = (m_current + 1) % 2; 
}


// Returns the active FBO texture. 
const Texture &Renderer::getTexture() const {
	return m_fbos[m_current].getTexture();
}

// Returns the active FBO depth buffer texture.
const Texture &Renderer::getDepthTexture() const {
	return m_fbos[m_current].getDepthTexture();
}

// Returns the active FBO width.
int Renderer::getWidth() const {
	return m_fbos[m_current].getWidth();
}

// Returns the active FBO height.
int Renderer::getHeight() const {
	return m_fbos[m_current].getHeight();
}


// Returns the Renderer init state.
bool Renderer::getInitState() const {
	return m_initState;
}
