#pragma once

#include <GL/glew.h>



// Class VBO : Permet de gérer un Vertex Buffer Object.
class VBO {
public :

	// Constructeur, destructeur.
	VBO();
	~VBO();

	// Nettoie les données du VBO.
	void clean();

	// Envoie des données au VBO.
	void pushData(void** data, int* sizes, int* type_sizes, 
		int buffer_len, int n);

	// Renvoie le nombre de vertices.
	int getSize() const;

	// Fonctions de bind.
	void glBind() const;
	void glUnbind() const;

private :

	// ID du VBO et taille.
	GLuint m_vbo;
	int m_size;

};



// Renvoie le nombre de vertices.
inline int VBO::getSize() const {
	return m_size;
}

// Bind le VBO.
inline void VBO::glBind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

// Unbind le VBO.
inline void VBO::glUnbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
