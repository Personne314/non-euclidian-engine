#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>



// Class Shader : Loads and compiles a GLSL shader.
class Shader {

public:

	// Constructors, destructor.
	Shader(const std::string& vertexSource, const std::string& fragmentSource, 
		const std::vector<std::pair<int, std::string> >& attribLocation);
	~Shader();

	// Bind and unbind functions.
	void glUse() const;
	void glUnuse() const;

	// Call to glUniformLocation.
	int getUniformLocation(std::string name) const;

	// Returns the Shader init state.
	bool getInitState() const;

private:

	// Init state.
	bool m_initState;

	// Compilation function.
	bool compileShader(GLuint& shader, GLenum type, const std::string& source);

	// Shader id.
	GLuint m_progID;

};
