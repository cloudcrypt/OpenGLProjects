#include "ShaderProgram.h"
#include "OpenGL.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/gtc/type_ptr.hpp"

using std::cerr;
using std::endl;


ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

bool ShaderProgram::attachShader(string path, GLenum type)
{
	if (id <= 0) {
		id = glCreateProgram();
		if (OpenGL::error("glCreateProgram"))
			return false;
	}

	std::ifstream in(path);
	string buffer = [&in] {
		std::ostringstream ss{};
		ss << in.rdbuf();
		return ss.str();
	}();
	const char *buffer_array[] = { buffer.c_str() };

	GLuint shader = glCreateShader(type);
	if (OpenGL::error("glCreateShader"))
		return false;

	glShaderSource(shader, 1, buffer_array, 0);
	if (OpenGL::error("glShaderSource"))
		return false;

	glCompileShader(shader);
	if (OpenGL::error("glCompileShader"))
		return false;

	// Compile results
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		string info(length, ' ');
		glGetShaderInfoLog(shader, info.length(), &length, &info[0]);
		cerr << "ERROR compiling shader " << shader << " :" << endl;
		cerr << info << endl;
	}

	// Attach shader
	glAttachShader(id, shader);
	if (OpenGL::error("glAttachShader"))
		return false;
}

bool ShaderProgram::link()
{
	if (id <= 0) {
		return false;
	}

	glLinkProgram(id);
	if (OpenGL::error("glLinkProgram"))
		return false;

	GLint state = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &state);
	if (state == GL_FALSE) {
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &state);

		char* buffer = new char[state];
		glGetProgramInfoLog(id, state, &state, buffer);
		buffer[state - 1] = '\0';         // ensure we're null-terminated

		cerr << "ERROR: Program " << id << " did not link. The program log:" << endl;
		cerr << buffer << endl;

		return false;
	}

	return true;
}

bool ShaderProgram::setInt(string variable, GLint value)
{
	// Get the uniform's location, if possible
	GLint location = glGetUniformLocation(id, variable.c_str());
	if (location < 0)
		return false;

	glUniform1i(location, value);
	return true;
}

bool ShaderProgram::setFloat(string variable, GLfloat value)
{
	// Get the uniform's location, if possible
	GLint location = glGetUniformLocation(id, variable.c_str());
	if (location < 0)
		return false;

	glUniform1f(location, value);
	return true;
}

bool ShaderProgram::setVec2(string variable, GLfloat value1, GLfloat value2)
{
	// Get the uniform's location, if possible
	GLint location = glGetUniformLocation(id, variable.c_str());
	if (location < 0)
		return false;

	glUniform2f(location, value1, value2);
	return true;
}

bool ShaderProgram::setMat4(string variable, mat4 mat)
{
	// Get the uniform's location if possible
	GLint location = glGetUniformLocation(id, variable.c_str());
	if (location < 0)
		return false;

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	return true;
}

bool ShaderProgram::bind()
{
	glUseProgram(id);
	if (OpenGL::error("glUseProgram"))
		return false;
	return true;
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}
