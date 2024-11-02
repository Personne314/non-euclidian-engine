#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>



// Class Shader : Charge et compile un Shader GLSL.
class Shader {

public:

	// Constructeurs, destructeur.
	Shader(const std::string& vertexSource, const std::string& fragmentSource, 
		const std::vector<std::pair<int, std::string> >& attribLocation);
	~Shader();

	// Fonctions de bind et d'unbind.
	void glUse() const;
	void glUnuse() const;

	// glUniformLocation.
	int getUniformLocation(std::string name) const;

	// Etat d'initialisation.
	bool getInitState() const;

private:

	// Etat d'initialisation.
	bool m_initState;

	// Fonctions de chargement.
	bool compileShader(GLuint& shader, GLenum type, const std::string& source);

	// IDs des shaders.
	GLuint m_vertID;
	GLuint m_fragID;
	GLuint m_progID;

};



// Fonctions de bind du shader.
inline void Shader::glUse() const {
	glUseProgram(m_progID);
}

// Fonctions d'unbind du shader.
inline void Shader::glUnuse() const {
	glUseProgram(0);
}

// Implémentation de glUniformLocation.
inline int Shader::getUniformLocation(std::string name) const {
	return glGetUniformLocation(m_progID, name.c_str());
}

// Renvoie l'état d'utilisation.
inline bool Shader::getInitState() const {
	return m_initState;
}
