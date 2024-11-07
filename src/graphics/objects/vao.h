#pragma once

#include <GL/glew.h>
#include "vbo.h"



// Class VAO : Use to create and use a Vertex Array Object.
class VAO {
public :

	// Constructor, destructor.
	VAO();
	~VAO();

	// Cleans VAO.
	void clean();

	// Function to push data to the VAO.
	void pushData(void** data, int* sizes, int* array_ids,
		int* gl_types, int buffer_len, int n);

	// Returns the number of vertices.
	int getSize() const;

	// Bind and unbind functions.
	void glBind() const;
	void glUnbind() const;

private :

	// VAO and associed VBO ids.
	GLuint m_vao;
	VBO m_vbo;

};
