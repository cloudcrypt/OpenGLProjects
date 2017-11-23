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

VertexArray::VertexArray(vector<GLfloat> data, GLuint dim, GLuint verts, bool enableTextureCoords)
{
	this->dim = dim;
	this->verts = verts;
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
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
	if (OpenGL::error("glBufferData"))
		return;

	GLsizei stride = enableTextureCoords ? ((this->dim + 2) * sizeof(GLfloat)) : 0;
	// Tell OpenGL how it is formatted
	glVertexAttribPointer(0, this->dim, GL_FLOAT, GL_FALSE, stride, 0);
	if (OpenGL::error("glVertexAttribPointer 0"))
		return;

	glEnableVertexAttribArray(0);
	if (OpenGL::error("glEnableVertexAttribArray 0"))
		return;

	if (enableTextureCoords) {
		// Tell OpenGL how it is formatted
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (this->dim + 2) * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		if (OpenGL::error("glVertexAttribPointer 1"))
			return;

		glEnableVertexAttribArray(1);
		if (OpenGL::error("glEnableVertexAttribArray 1"))
			return;
	}

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
