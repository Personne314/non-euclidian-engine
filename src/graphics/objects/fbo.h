#pragma once

#include <GL/glew.h>

#include "../textures/texture.h"



class FBO {
public:

	FBO(int width, int height);
	~FBO();

	void clear();

	void glBind() const;
	void glUnbind() const;

	int getWidth() const;
	int getHeight() const;
	const Texture& getTexture() const;
	bool getInitState() const;

private:

	bool m_initState;

	GLuint m_fbo;
	GLuint m_rbo;
	Texture m_texture;

	int m_width;
	int m_height;

};



inline void FBO::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void FBO::glBind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);  
}

inline void FBO::glUnbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	glDrawBuffer(GL_BACK); 
}

inline int FBO::getWidth() const {
	return m_width;
}

inline int FBO::getHeight() const {
	return m_height;
}

inline const Texture& FBO::getTexture() const {
	return m_texture;
}

inline bool FBO::getInitState() const {
	return m_initState;
}