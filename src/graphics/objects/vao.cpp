#include "vao.h"

#include <GL/glew.h>



// Renvoie la taille d'un type correspondant à une constante d'OpenGL.
int sizeFromGLType(int type) {
	switch (type) {
	case GL_FLOAT:	return sizeof(float);
	case GL_DOUBLE:	return sizeof(double);
	case GL_INT:	return sizeof(int);
	case GL_SHORT:	return sizeof(short);
	default:		return 1;
	}
}



// Constructeur.
VAO::VAO() {
	glGenVertexArrays(1, &m_vao);
}

// Destructeur.
VAO::~VAO() {
	if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);
}


// Fonction de nettoyage du VBO.
void VAO::clean() {
	if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);
	glGenVertexArrays(1, &m_vao);
}


// Envoie les données au VAO.
// data : liste de tableaux de vecteurs de données.
// sizes : dimension des vecteurs de data.
// array_ids : ids des arrays avec lesquelles lier les données de data.
// gl_types : types des données des listes de data. 
// buffer_len : nombre de vecteur dans les listes de data.
// n : nombre de listes dans data, d'éléments dans sizes, array_ids
// et gl_types.
// ----------------------------------------------------------------------------
// On fournit n listes de buffer_len vecteurs de dimension sizes
// le type d'une composante est gl_types, contenues dans datas, et on crée
// un VBO. Génère un VAO et le lie au VBO.
void VAO::pushData(void** data, int* sizes, int* array_ids, 
int* gl_types, int buffer_len, int n) {
	clean();

	// Génère le VBO.
	int type_sizes[n];
	for (int i = 0; i < n; i++) type_sizes[i] = sizeFromGLType(gl_types[i]);
	m_vbo.pushData(data, sizes, type_sizes, buffer_len, n);

	// Lie le VBO au VAO.
	glBind();
		m_vbo.glBind();

			// Lie les arrays et met à jour l'offset.
			long long int offset = 0;
			for (int i = 0; i < n; i++) {
				glVertexAttribPointer(array_ids[i], sizes[i], gl_types[i], GL_FALSE, 0, (void*)(offset));
				glEnableVertexAttribArray(array_ids[i]);
				offset += sizes[i] * type_sizes[i] * buffer_len;
			}

		m_vbo.glUnbind();
	glUnbind();

}
