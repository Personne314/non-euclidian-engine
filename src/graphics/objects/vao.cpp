#include "vao.h"

#include <GL/glew.h>



// Returns the size in memory of types described by OpenGL constants.
int sizeFromGLType(int type) {
	switch (type) {
	case GL_FLOAT:	return sizeof(float);
	case GL_DOUBLE:	return sizeof(double);
	case GL_INT:	return sizeof(int);
	case GL_SHORT:	return sizeof(short);
	default:		return 1;
	}
}


// Constructor.
VAO::VAO() {
	glGenVertexArrays(1, &m_vao);
}

// Destructor.
VAO::~VAO() {
	if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);
}


// Clean the VAO and create an empty one.
void VAO::clean() {
	if(glIsVertexArray(m_vao) == GL_TRUE) glDeleteVertexArrays(1, &m_vao);
	glGenVertexArrays(1, &m_vao);
}


// Sends data to the VAO.
// data: list of arrays containing data vectors.
// sizes: dimension of the data vectors.
// array_ids: IDs of the arrays to link with the data in data.
// gl_types: data types of the lists in data.
// buffer_len: number of vectors in the lists in data.
// n: number of lists in data, and elements in sizes, array_ids, and gl_types.
// ----------------------------------------------------------------------------
// Provides n lists of buffer_len vectors with dimensions sizes.
// The type of a component is gl_types, contained in data, and a VBO is created.
// Generates a VAO and links it to the VBO.
void VAO::pushData(void** data, int* sizes, int* array_ids, 
int* gl_types, int buffer_len, int n) {
	clean();

	// Create the VBO.
	int type_sizes[n];
	for (int i = 0; i < n; i++) type_sizes[i] = sizeFromGLType(gl_types[i]);
	m_vbo.pushData(data, sizes, type_sizes, buffer_len, n);

	// Links the VBO to the VAO.
	glBind();
		m_vbo.glBind();

			// Links arrays and update offset.
			long long int offset = 0;
			for (int i = 0; i < n; i++) {
				glVertexAttribPointer(array_ids[i], sizes[i], gl_types[i], GL_FALSE, 0, (void*)(offset));
				glEnableVertexAttribArray(array_ids[i]);
				offset += sizes[i] * type_sizes[i] * buffer_len;
			}

		m_vbo.glUnbind();
	glUnbind();

}


// Returns the number of vertices.
int VAO::getSize() const {
	return m_vbo.getSize();
}

// Binds the VAO.
void VAO::glBind() const {
	glBindVertexArray(m_vao);
}

// Unbinds the VAO.
void VAO::glUnbind() const {
	glBindVertexArray(0);
}
