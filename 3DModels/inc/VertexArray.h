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
#include "Mesh.h"

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
	VertexArray(vector<Vertex> data);
	bool draw();
	bool setType(GLenum type);
};

