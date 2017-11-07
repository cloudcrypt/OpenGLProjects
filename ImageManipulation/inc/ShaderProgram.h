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
	bool bind();
	static void unbind();
};

