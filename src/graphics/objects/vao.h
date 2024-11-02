#pragma once

#include <GL/glew.h>
#include "vbo.h"



// Class VAO : Permet de gérer un Vertex Buffer Array.
class VAO {
public :

	// Constructeur, destructeur.
	VAO();
	~VAO();

	// Nettoie les données du VAO.
	void clean();

	// Envoie des données au VAO.
	void pushData(void** data, int* sizes, int* array_ids,
		int* gl_types, int buffer_len, int n);

	// Renvoie le nombre de vertices.
	int getSize() const;

	// Fonctions de bind.
	void glBind() const;
	void glUnbind() const;

private :

	// Ids du VAO et VBO associé.
	GLuint m_vao;
	VBO m_vbo;

};



// Renvoie le nombre de vertices.
inline int VAO::getSize() const {
	return m_vbo.getSize();
}

// Bind le VAO.
inline void VAO::glBind() const {
	glBindVertexArray(m_vao);
}

// Unbind le VAO.
inline void VAO::glUnbind() const {
	glBindVertexArray(0);
}
