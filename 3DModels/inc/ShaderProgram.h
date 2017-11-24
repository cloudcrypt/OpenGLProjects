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

	bool setInt(string variable, GLint value) const;
	bool setFloat(string variable, GLfloat value) const;
	bool setVec2(string variable, GLfloat value1, GLfloat value2) const;
	bool setVec3(string variable, glm::vec3 vector) const;
	bool setMat4(string variable, mat4 mat) const;

	bool bind() const;
	static void unbind();
};

