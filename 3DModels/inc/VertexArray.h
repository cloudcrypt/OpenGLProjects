// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
//
// Author: Daniel Dastoor
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

