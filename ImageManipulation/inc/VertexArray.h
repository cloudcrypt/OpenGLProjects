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

