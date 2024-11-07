#pragma once

#include <GL/glew.h>



// Class VBO : Use to create and use a Vertex Buffer Object.
class VBO {
public :

	// Constructor, destructor.
	VBO();
	~VBO();

	// Cleans VBO.
	void clean();

	// Function to push data to the VBO.
	void pushData(void** data, int* sizes, int* type_sizes, 
		int buffer_len, int n);

	// Returns the number of vertices.
	int getSize() const;

	// Bind and unbind functions.
	void glBind() const;
	void glUnbind() const;

private :

	// VBO id.
	GLuint m_vbo;
	int m_size;

};
