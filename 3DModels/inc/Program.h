// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
// Program.h
//
// Author: Daniel Dastoor
// Date:   November 2017
// ==========================================================================

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "Camera.h"
#include "ObjectBase.h"
#include "Model.h"
#include "glm/glm.hpp"
#include "ChessBoard.h"

using std::endl;
using std::string;
using glm::vec2;
using glm::vec3;

class Program
{
private:
	bool live = true;
	GLFWwindow* window = nullptr;

	ShaderProgram shaderProgram;

	ObjectBase *objModel;
	ObjectBase *simpleModel;
	ObjectBase *chessModel;
	Camera *camera;

	mat4 model;
	mat4 view;
	mat4 projection;

	vec3 lightPos = vec3(3.0f, 3.0f, 3.0f);

	bool aoMode = true;
	bool chessMode = false;

	char *windowName = "3DModels";
	int width = 1024;
	int originalWidth = width;
	int height = 1024;
	int originalHeight = height;

	void setReverseScaling();

	vec3 reverseScaling = vec3(1.0, 1.0, 1.0);

	mat4 reverseScalingMatrix;

	void render();
	bool initGLFW();
	bool initGLEW();
	bool initShaders();

	void setAoMode();

	static void sizeCallback(GLFWwindow* window, int width, int height);
	void sizeChange(int width, int height);

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void keyInput(int key, int scancode, int action, int mods);

	bool terminate(string message);

public:
	Program() { }
	int run(int argc, const char** argv);
};

