#include "fbo.h"

#include <iostream>



// Constructeur.
FBO::FBO(int width, int height) : m_initState(false),
m_fbo(0), m_rbo(0), m_texture(), m_width(width), m_height(height) {

	// Crée le FBO et lui bind la texture pour stoquer les couleurs.
	glGenFramebuffers(1, &m_fbo);
	glBind();

		// Génère la texture du FBO et la bind a celui-ci.
		glGenTextures(1, &m_texture.m_id);
		m_texture.m_width = width;
		m_texture.m_height = height;
		m_texture.m_initState = true;
		glBindTexture(GL_TEXTURE_2D, m_texture.m_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.m_id, 0);

		// Crée le buffer pour la profondeur et le stencil et le bind au FBO.
		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo); 
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);  
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);	

		// Vérifie que le FBO est bien construit.
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cerr << "Framebuffer is not complete!" << std::endl;	
		} else m_initState = true;

	glUnbind();

}

// Destructeur.
FBO::~FBO() {
	glDeleteRenderbuffers(1, &m_rbo);
	glDeleteFramebuffers(1, &m_fbo);
}
