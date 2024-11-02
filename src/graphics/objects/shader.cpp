#include "shader.h"

#include <iostream>
#include <fstream>



// Constructeur.
Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, 
	const std::vector<std::pair<int, std::string> >& attribLocation) :
m_initState(false), m_vertID(0), m_fragID(0), m_progID(0) {

	// Compile les fichiers source.
	if(!compileShader(m_vertID, GL_VERTEX_SHADER, vertexSource) ||
		!compileShader(m_fragID, GL_FRAGMENT_SHADER, fragmentSource)) {
		return;
	} 

	// Crée le programme et attache les fichiers.
	m_progID = glCreateProgram();
	glAttachShader(m_progID, m_vertID);
	glAttachShader(m_progID, m_fragID);

	// Attribu les listes.
	for (std::pair<int, std::string> loc : attribLocation) {
		glBindAttribLocation(m_progID, loc.first, loc.second.c_str());
	}

	// Link le programme.
	glLinkProgram(m_progID);

	// Récupère les erreurs de linkage.
	GLint state = 0;
	glGetProgramiv(m_progID, GL_LINK_STATUS, &state);
	if(state != GL_TRUE) {

		// Récupère le message d'erreur.
		GLint errorSize = 0;
		glGetProgramiv(m_progID, GL_INFO_LOG_LENGTH, &errorSize);
		char *charError = new char[errorSize + 1];
		glGetShaderInfoLog(m_progID, errorSize, &errorSize, charError);
		charError[errorSize] = '\0';

		// Log le message d'erreur.
		std::cerr << "Erreur lors du linkage du shader \"" << vertexSource << "\", \"" 
			<< fragmentSource << "\" : " << charError << std::endl;

		// Vide la mémoire.
		delete[] charError;
		return;

	}

	// Shader initialisé.
	m_initState = true;

}

// Destructeur.
Shader::~Shader() {
	if(glIsShader(m_vertID) == GL_TRUE) glDeleteShader(m_vertID);
	if(glIsShader(m_fragID) == GL_TRUE) glDeleteShader(m_fragID);
	if(glIsProgram(m_progID) == GL_TRUE) glDeleteProgram(m_progID);
}


// Compile un fichier GLSL.
bool Shader::compileShader(GLuint& shader, GLenum type, const std::string& source) {

	// Crée un nouveau shader en mémoire.
	shader = glCreateShader(type);
	if (shader == 0) {
		std::cerr << "Erreur lors de la compilation du shader \"" << source
			<< "\" : le type \"" << type << "\" n'existe pas !" << std::endl;
		return false;
	} 

	// Ouvre le fichier.    
	std::ifstream file(source.c_str());
	if (!file) {
		std::cerr << "Erreur lors de la compilation du shader \"" << source 
			<< "\" : le fichier source n'existe pas !" << std::endl;
		return false;

	} 

	// Lit le code source.
	std::string sourceCode, line;
	while (getline(file, line)) {
		sourceCode += line + "\n";
	}
	file.close();

	// Compile le programme.
	const GLchar* charSourceCode = sourceCode.c_str();
	glShaderSource(shader, 1, &charSourceCode, 0);
	glCompileShader(shader);

	// Récupère les erreurs de compilation.
	GLint state = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &state);
	if (state != GL_TRUE) {

		// Récupère le message d'erreur.
		GLint errorSize = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);
		char *charError = new char[errorSize + 1];
		glGetShaderInfoLog(shader, errorSize, &errorSize, charError);
		charError[errorSize] = '\0';

		// Affiche le message d'erreur.
		std::cerr << "Erreur lors de la compilation du shader \"" << source 
			<< "\" : " << charError << std::endl;

		// Vide la mémoire.
		delete [] charError;
		glDeleteShader(shader);
		return false;

	}

	// Le programme est bien compilé.
	return true;

}
