#include "shader.h"

#include <iostream>
#include <fstream>



// Constructor.
Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, 
	const std::vector<std::pair<int, std::string> >& attribLocation) : m_initState(false), m_progID(0) {

	// Compiles shader source files.
	GLuint m_vertID, m_fragID;
	if (!compileShader(m_vertID, GL_VERTEX_SHADER, vertexSource) ||
		!compileShader(m_fragID, GL_FRAGMENT_SHADER, fragmentSource)) {
		return;
	} 

	// Creates the program and attach the shaders.
	m_progID = glCreateProgram();
	glAttachShader(m_progID, m_vertID);
	glAttachShader(m_progID, m_fragID);

	// Attributes the lists.
	for (std::pair<int, std::string> loc : attribLocation) {
		glBindAttribLocation(m_progID, loc.first, loc.second.c_str());
	}

	// Links the program.
	glLinkProgram(m_progID);
	if(glIsShader(m_vertID) == GL_TRUE) glDeleteShader(m_vertID);
	if(glIsShader(m_fragID) == GL_TRUE) glDeleteShader(m_fragID);

	// Catchs linking errors.
	GLint state = 0;
	glGetProgramiv(m_progID, GL_LINK_STATUS, &state);
	if(state != GL_TRUE) {

		// Get the error message.
		GLint errorSize = 0;
		glGetProgramiv(m_progID, GL_INFO_LOG_LENGTH, &errorSize);
		char *charError = new char[errorSize + 1];
		glGetShaderInfoLog(m_progID, errorSize, &errorSize, charError);
		charError[errorSize] = '\0';

		// Prints the error message.
		std::cerr << "Shader linking error for the souces files \"" << vertexSource
			<< "\", \"" << fragmentSource << "\" : " << charError << std::endl;

		// Frees memory.
		delete[] charError;
		return;

	}

	// Shader initilized.
	m_initState = true;

}

// Destructor.
Shader::~Shader() {
	if(glIsProgram(m_progID) == GL_TRUE) glDeleteProgram(m_progID);
}


// Binds the shader.
void Shader::glUse() const {
	glUseProgram(m_progID);
}

// Unbinds the shader.
void Shader::glUnuse() const {
	glUseProgram(0);
}

// Call to glUniformLocation.
int Shader::getUniformLocation(std::string name) const {
	return glGetUniformLocation(m_progID, name.c_str());
}

// Returns the Shader init state.
bool Shader::getInitState() const {
	return m_initState;
}


// Compiles a GLSL shader souce file.
bool Shader::compileShader(GLuint& shader, GLenum type, const std::string& source) {

	// Creates a new shader.
	shader = glCreateShader(type);
	if (shader == 0) {
		std::cerr << "Error during shader \"" << source
			<< "\" compilation : the type \"" << type << "\" doesn't exists" << std::endl;
		return false;
	} 

	// Opens the source file.    
	std::ifstream file(source.c_str());
	if (!file) {
		std::cerr << "Error during shader \"" << source
			<< "\" compilation : the source file doesn't exists" << std::endl;
		return false;

	} 

	// Reads the source file.
	std::string sourceCode, line;
	while (getline(file, line)) {
		sourceCode += line + "\n";
	}
	file.close();

	// Compiles the shader.
	const GLchar* charSourceCode = sourceCode.c_str();
	glShaderSource(shader, 1, &charSourceCode, 0);
	glCompileShader(shader);

	// Catchs compilation errors.
	GLint state = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &state);
	if (state != GL_TRUE) {

		// Get the error messages.
		GLint errorSize = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);
		char *charError = new char[errorSize + 1];
		glGetShaderInfoLog(shader, errorSize, &errorSize, charError);
		charError[errorSize] = '\0';

		// Prints the error message.
		std::cerr << "Error during shader \"" << source
			<< "\" compilation : " << charError << std::endl;

		// Frees memory.
		delete [] charError;
		glDeleteShader(shader);
		return false;

	}

	// Shader compiled.
	return true;

}
