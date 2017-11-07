#include "VertexArray.h"
#include <GL/glew.h>
#include "OpenGL.h"

VertexArray::VertexArray(vector<GLfloat> data, GLuint dim)
{
	this->dim = dim;

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

	// Tell OpenGL how it is formatted
	glVertexAttribPointer(0, this->dim, GL_FLOAT, GL_FALSE, 0, 0);
	if (OpenGL::error("glVertexAttribPointer"))
		return;

	glEnableVertexAttribArray(0);
	if (OpenGL::error("glEnableVertexAttribArray"))
		return;

	// Unbind ourselves
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	verts = data.size() / dim;
}

bool VertexArray::draw()
{
	// Bind
	glBindVertexArray(id);
	if (OpenGL::error("glBindVertexArray"))
		return false;

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
