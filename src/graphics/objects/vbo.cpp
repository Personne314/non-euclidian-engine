#include "vbo.h"



// Constructor.
VBO::VBO() : m_size(0) {
	glGenBuffers(1, &m_vbo);
}

// Destructor.
VBO::~VBO() {
	if(glIsBuffer(m_vbo) == GL_TRUE) glDeleteBuffers(1, &m_vbo);
}


// Cleans the VBO.
void VBO::clean() {
	if(glIsBuffer(m_vbo) == GL_TRUE) glDeleteBuffers(1, &m_vbo);
	glGenBuffers(1, &m_vbo);
	m_size = 0;
}


// Sends data to the VBO.
// data: list of arrays containing data vectors.
// sizes: dimension of the data vectors.
// type_sizes: size in memory of the data types in the lists in data.
// buffer_len: number of vectors in the lists in data.
// n: number of lists in data, and elements in sizes, array_ids, and gl_types.
// ----------------------------------------------------------------------------
// Provides n lists of buffer_len vectors with dimensions sizes, where
// the memory size of each component is type_sizes, contained in data.
void VBO::pushData(void** data, int* sizes, int* type_sizes, 
int buffer_len, int n) {
	clean();
	m_size = buffer_len;

	// Calculate the size used by each list and the total size.
	GLsizeiptr data_sizes[n+1];
	data_sizes[n] = 0;
	for (int i = 0; i < n; i++) {
		GLsizeiptr val = sizes[i] * type_sizes[i] * buffer_len;
		data_sizes[n] += val;
		data_sizes[i] = val;
	}

	// Gives the data to the VBO.
	glBind();
		GLsizeiptr offset = 0;
		glBufferData(GL_ARRAY_BUFFER, data_sizes[n], 0, GL_STATIC_DRAW);
		for(int i = 0; i < n; i++) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, data_sizes[i], data[i]);
			offset += data_sizes[i];
		}
	glUnbind();
}


// Returns the number of vertices.
int VBO::getSize() const {
	return m_size;
}

// Binds the VBO.
void VBO::glBind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

// Unbinds the VBO.
void VBO::glUnbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
