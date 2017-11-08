#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

using std::string;

class ShaderProgram
{
public:
//private:
	GLint id = -1;
//public:
	ShaderProgram();
	~ShaderProgram();
	bool attachShader(string fileName, GLenum type);
	bool link();
	bool setInt(string variable, GLint value);
	bool setFloat(string variable, GLfloat value);
	bool setVec2(string variable, GLfloat value1, GLfloat value2);
	bool bind();
	static void unbind();
};

