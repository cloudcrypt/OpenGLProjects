// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
// Program.cpp
//
// Author: Daniel Dastoor
// Date:   November 2017
// ==========================================================================

#include "Program.h"
#include "OpenGL.h"
#include <iostream>
#include <GL/glew.h>

#include "Camera.h"

#include <cmath>
#include "VertexArray.h"

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

using glm::mat4;
using glm::vec3;
using glm::scale;
using glm::translate;

using std::pow;
using std::sqrt;

using std::cerr;
using std::endl;

GLuint texture;
int picWidth, picHeight, channels;

int Program::run(int argc, const char ** argv)
{
	if (!initGLFW() || !initGLEW() || !initShaders())
		return -1;
	
	setReverseScaling();

	objModel = new Model(argv[1], shaderProgram, argv[2]);
	simpleModel = objModel;
	shaderProgram.bind();

	camera = new Camera(shaderProgram, objModel->getBoundingBox());

	shaderProgram.setVec3("lightPos", lightPos);

	projection = mat4();
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	shaderProgram.setMat4("projection", projection);

	glEnable(GL_DEPTH_TEST);

	while (live) {
		render();
		glfwPollEvents();
		if (glfwWindowShouldClose(window))
			live = false;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void Program::setReverseScaling()
{
	reverseScalingMatrix = mat4(1.0f);
	reverseScalingMatrix = scale(reverseScalingMatrix, reverseScaling);
	shaderProgram.bind();
	shaderProgram.setMat4("reverseScaling", reverseScalingMatrix);
}

void Program::render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram.bind();

	objModel->draw();

	glfwSwapBuffers(window);
}

bool Program::initGLFW()
{
	// Initialize the GLFW windowing system
	if (!glfwInit()) {
		cerr << "ERROR: GLFW did not initialize!" << endl;
		return false;
	}

	// Use OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, windowName, 0, 0);

	// Verify if context was created
	if (!window)
		return terminate("Could not create a render context!");

	glfwMakeContextCurrent(window);

	// Set up an error callback
	glfwSetErrorCallback([](int error, const char* description) {
		cerr << "ERROR: GLFW threw error " << error << ":" << endl;
		cerr << description << endl;
	});

	glfwSetWindowUserPointer(window, this);
	// Set up all callbacks
	glfwSetKeyCallback(window, keyCallback);
	glfwSetWindowSizeCallback(window, sizeCallback);

	return !OpenGL::error("Program::initGLFW() assert");
}

bool Program::initGLEW()
{
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "GLEW failed to initialize with error: " << glewGetErrorString(err) << endl;
		return false;
	}
	return !OpenGL::error("Program::initGLEW() assert");
}

bool Program::initShaders()
{
	if (!shaderProgram.attachShader("data/vertex.glsl", GL_VERTEX_SHADER))
		return terminate("Error attaching vertex shader");

	if (!shaderProgram.attachShader("data/fragment.glsl", GL_FRAGMENT_SHADER))
		return terminate("Error attaching fragment shader");

	if (!shaderProgram.link())
		return terminate("Error linking shader program");

	return !OpenGL::error("Program::initShaders() assert");
}


void Program::setAoMode()
{
	shaderProgram.bind();
	shaderProgram.setInt("aoMode", aoMode);
}

void Program::setTextureMode()
{
	shaderProgram.bind();
	shaderProgram.setInt("textureMode", textureMode);
}

void Program::sizeCallback(GLFWwindow * window, int width, int height)
{
	static_cast<Program*>(glfwGetWindowUserPointer(window))->sizeChange(width, height);
}

void Program::sizeChange(int width, int height)
{
	reverseScaling = vec3((double)1 / ((double)width / (double)(this->originalWidth)), (double)1 / ((double)height / (double)(this->originalHeight)), 1.0f);

	setReverseScaling();

	glViewport(0, 0, width, height);
	render();
	
	this->width = width;
	this->height = height;
}

void Program::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Program*>(glfwGetWindowUserPointer(window))->keyInput(key, scancode, action, mods);
}

void Program::keyInput(int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
		return;
	objModel->processKeyboard(key);
	camera->processKeyboard(key);
	switch (key) {
		case GLFW_KEY_O:
			aoMode = !aoMode;
			setAoMode();
			break;
		case GLFW_KEY_T:
			textureMode = !textureMode;
			setTextureMode();
			break;
		case GLFW_KEY_C:
			chessMode = !chessMode;
			if (chessMode) {
				if (chessModel == nullptr) {
					chessModel = new ChessBoard(shaderProgram);
				}
				objModel = chessModel;
				camera = new Camera(shaderProgram, chessModel->getBoundingBox());
			} else {
				objModel = simpleModel;
				objModel->translate(0, 0, 0);
				camera = new Camera(shaderProgram, simpleModel->getBoundingBox());
			}
	}
}

bool Program::terminate(string message)
{
	cerr << "ERROR: " << message << endl;
	glfwTerminate();
	return false;
}

int main(int argc, const char** argv) {
	if (argc != 2) {
		cerr << "Usage: rayTracer <modelName> <diffuseTextureFile>" << endl;
		return 0;
	}
	Program p;
	return p.run(argc, argv);
}
