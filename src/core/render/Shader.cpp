#include "../Libs.h"
#include "Shader.h"
#include <fstream>
#include <iostream>
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& rawText, GLenum shaderType);

Shader::Shader(const std::string& fileName) {
	m_program = glCreateProgram();
	
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (GLuint sh : m_shaders) {
		glAttachShader(m_program, sh);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Program linking failed");
	
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Program is invalid");

	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "viewMatrix");
	m_uniforms[PROJ_U] = glGetUniformLocation(m_program, "projectionMatrix");
	m_uniforms[COORD_X] = glGetUniformLocation(m_program, "coordX");
	m_uniforms[COORD_Z] = glGetUniformLocation(m_program, "coordZ");
}

Shader::~Shader() {
	for (size_t i = 0; i<NUM_SHADERS; i++) {
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void Shader::Bind() {
	glUseProgram(m_program);
}

void Shader::Update(const ChunkCoord& coord, const Camera& camera) {
	glm::mat4 projMat = camera.GetProjectionMatrix();
	glm::mat4 viewMat = camera.GetViewMatrix();
	glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(m_uniforms[PROJ_U], 1, GL_FALSE, glm::value_ptr(projMat));
	glUniform1i(m_uniforms[COORD_X], coord.x);
	glUniform1i(m_uniforms[COORD_Z], coord.y);
}

static GLuint CreateShader(const std::string& rawText, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Shader creation failed." << std::endl;
		                           
	const GLchar* src[1];
	GLint lengths[1];

	src[0] = rawText.c_str();
	lengths[0] = rawText.length();
	glShaderSource(shader, 1, src, lengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader");

	return shader;
}

static std::string LoadShader(const std::string& fileName) {
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			std::getline(file, line);
			output.append(line + "\n");
		}
	} else {
		std::cerr << "Unable to load the shader: " << fileName << std::endl;
	}

	file.close();
	
	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint result = 0;
	GLchar error[1024] = {0};
	
	if (isProgram)
		glGetProgramiv(shader, flag, &result);
	else
		glGetShaderiv(shader, flag, &result);
	
	if(result == GL_FALSE){
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}