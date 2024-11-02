#include "vbo.h"



// Constructeur.
VBO::VBO() : m_size(0) {
	glGenBuffers(1, &m_vbo);
}

// Destructeur.
VBO::~VBO() {
	if(glIsBuffer(m_vbo) == GL_TRUE) glDeleteBuffers(1, &m_vbo);
}


// Fonction de nettoyage du VBO.
void VBO::clean() {
	if(glIsBuffer(m_vbo) == GL_TRUE) glDeleteBuffers(1, &m_vbo);
	glGenBuffers(1, &m_vbo);
	m_size = 0;
}


// Envoie les données au VBO.
// data : liste de tableaux de vecteurs de données.
// sizes : dimension des vecteurs de data.
// type_sizes : taille des types des données des listes de data. 
// buffer_len : nombre de vecteur dans les listes de data.
// n : nombre de listes dans data, d'éléments dans sizes, array_ids
// et gl_types.
// ----------------------------------------------------------------------------
// On fournit n listes de buffer_len vecteurs de dimension sizes dont la 
// taille en mémoire d'une composante est type_sizes, contenues dans data.
void VBO::pushData(void** data, int* sizes, int* type_sizes, 
int buffer_len, int n) {
	clean();
	m_size = buffer_len;

	// Calcule la taille prise par chaque liste et la taille totale.
	GLsizeiptr data_sizes[n+1];
	data_sizes[n] = 0;
	for (int i = 0; i < n; i++) {
		GLsizeiptr val = sizes[i] * type_sizes[i] * buffer_len;
		data_sizes[n] += val;
		data_sizes[i] = val;
	}

	// Bind le VBO, lui envoie les données, puis l'unbind.
	glBind();
		GLsizeiptr offset = 0;
		glBufferData(GL_ARRAY_BUFFER, data_sizes[n], 0, GL_STATIC_DRAW);
		for(int i = 0; i < n; i++) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, data_sizes[i], data[i]);
			offset += data_sizes[i];
		}
	glUnbind();
}
