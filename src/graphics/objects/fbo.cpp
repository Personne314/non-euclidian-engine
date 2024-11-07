#include "fbo.h"

#include <iostream>



// Constructor.
FBO::FBO(int width, int height) : m_initState(false),
m_fbo(0), m_texture(), m_depth(), m_width(width), m_height(height) {

	// Creates the FBO.
	glGenFramebuffers(1, &m_fbo);
	glBind();

		// Creates the color texture and binds it.
		glGenTextures(1, &m_texture.m_id);
		m_texture.m_width = width;
		m_texture.m_height = height;
		m_texture.m_initState = true;
		glBindTexture(GL_TEXTURE_2D, m_texture.m_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.m_id, 0);

		// Creates the depth texture and binds it.
		glGenTextures(1, &m_depth.m_id);
		m_depth.m_width = width;
		m_depth.m_height = height;
		m_depth.m_initState = true;
		glBindTexture(GL_TEXTURE_2D, m_depth.m_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth.m_id, 0);

		// Checks if the FBO is well initilized.
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cerr << "Framebuffer is not complete!" << std::endl;	
		} else m_initState = true;

	glUnbind();

}

// Destructor.
FBO::~FBO() {
	glDeleteFramebuffers(1, &m_fbo);
}


// Call to glClear. 
// The FBO must have been previously bind.
void FBO::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// Bind the FBO.
// Must be called before using an FBO.
void FBO::glBind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);  
}

// Unbind the FBO.
void FBO::glUnbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	glDrawBuffer(GL_BACK); 
}


// Returns the buffer width.
int FBO::getWidth() const {
	return m_width;
}

// Returns the buffer height.
int FBO::getHeight() const {
	return m_height;
}

// Returns a const reference to the buffer texture.
const Texture &FBO::getTexture() const {
	return m_texture;
}

// Returns a const reference to the buffer depth texture.
const Texture &FBO::getDepthTexture() const {
	return m_depth;
}

// Returns the FBO init state.
bool FBO::getInitState() const {
	return m_initState;
}
