// ==========================================================================
// CPSC 453 Assignment #2: Image Manipulation
// Daniel Dastoor
// ShaderProgram.h
// Class to load and compile GLSL shaders
//
// Author: Daniel Dastoor, based on code by Haysn Hornbeck
// Date:   November 2017
// ==========================================================================

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "glm/mat4x4.hpp"

using std::string;
using glm::mat4;

class ShaderProgram
{
private:
	GLint id = -1;
public:
	ShaderProgram() { }
	bool attachShader(string fileName, GLenum type);
	bool link();

	bool setInt(string variable, GLint value);
	bool setFloat(string variable, GLfloat value);
	bool setVec2(string variable, GLfloat value1, GLfloat value2);
	bool setMat4(string variable, mat4 mat);

	bool bind();
	static void unbind();
};

