// ==========================================================================
// CPSC 453 Assignment #2: Image Manipulation
// Daniel Dastoor
// VertexArray.h
// Class to create and draw vertex array objects.
//
// Author: Daniel Dastoor, based on code by Haysn Hornbeck.
// Date:   November 2017
// ==========================================================================

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

using std::vector;

class VertexArray
{
private:
	GLuint id = 0;
	GLuint bufID = 0;
	GLuint dim;
	GLuint verts;
	GLenum prim = GL_TRIANGLES;
public:
	VertexArray(vector<GLfloat> data, GLuint dim, GLuint verts, bool enableTextureCoords);
	bool draw();
	bool setType(GLenum type);
};

