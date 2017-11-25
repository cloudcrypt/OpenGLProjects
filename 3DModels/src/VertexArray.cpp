// ==========================================================================
// CPSC 453 Assignment #2: Image Manipulation
// Daniel Dastoor
// VertexArray.cpp
// Class to create and draw vertex array objects.
//
// Author: Daniel Dastoor, based on code by Haysn Hornbeck.
// Date:   November 2017
// ==========================================================================

#include "VertexArray.h"
#include <GL/glew.h>
#include "OpenGL.h"

VertexArray::VertexArray(vector<Vertex> vertices)
{
	//this->dim = dim;
	verts = vertices.size();
	// Generate a named vertex array and bind to it
	glGenVertexArrays(1, &id);
	if (OpenGL::error("glGenVertexArrays"))
		return;

	glBindVertexArray(id);
	if (OpenGL::error("glBindVertexArray"))
		return;

	// Generate some storage space
	glGenBuffers(1, &bufID);
	if (OpenGL::error("glGenBuffers"))
		return;

	glBindBuffer(GL_ARRAY_BUFFER, bufID);
	if (OpenGL::error("glBindBuffer"))
		return;

	// Transfer over the data
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	if (OpenGL::error("glBufferData"))
		return;

	//GLsizei stride = enableTextureCoords ? ((this->dim + 2) * sizeof(GLfloat)) : 0;
	// Tell OpenGL how it is formatted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	if (OpenGL::error("glVertexAttribPointer 0"))
		return;

	glEnableVertexAttribArray(0);
	if (OpenGL::error("glEnableVertexAttribArray 0"))
		return;
	
	//if (enableTextureCoords) {
	// Tell OpenGL how it is formatted
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	if (OpenGL::error("glVertexAttribPointer 1"))
		return;

	glEnableVertexAttribArray(1);
	if (OpenGL::error("glEnableVertexAttribArray 1"))
		return;
	//}

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	if (OpenGL::error("glVertexAttribPointer 2"))
		return;

	glEnableVertexAttribArray(2);
	if (OpenGL::error("glEnableVertexAttribArray 2"))
		return;

	// Unbind ourselves
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bool VertexArray::draw()
{
	// Bind
	glBindVertexArray(id);
	if (OpenGL::error("glBindVertexArray"))
		return false;

	if (prim == GL_PATCHES) {
		glPatchParameteri(GL_PATCH_VERTICES, 4);
	}

	// Draw
	glDrawArrays(prim, 0, verts);
	if (OpenGL::error("glDrawArrays"))
		return false;

	// Unbind
	glBindVertexArray(0);

	return !OpenGL::error("VertexArray::draw() assert");
}

bool VertexArray::setType(GLenum type)
{
	this->prim = type;
	return true;
}
