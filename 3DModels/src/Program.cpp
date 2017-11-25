// ==========================================================================
// CPSC 453 Assignment #2: Image Manipulation
// Daniel Dastoor
// Program.cpp
// Class to display and manipulate images and catmull-rom splines.
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
	
	/*vector<float> vertices = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};*/
		/*1.000000, 0.003296, -1.000000, 0.0f, 0.0f,
		1.000000, 0.003296, 1.000000, 0.0f, 0.0f,
		-1.000000, 0.003296, 1.000000, 0.0f, 0.0f,
		-1.000000, 0.003296, -1.000000, 0.0f, 0.0f,
		-0.000000, 1.000000, 0.000000, 0.0f, 0.0f*/
	/*vector<float> vertices = {
		 1.000000f,  0.003296f,  1.000000f, 0.0f, 0.0f,
		-1.000000f,  0.003296f, -1.000000f, 0.0f, 0.0f,
		 1.000000f,  0.003296f, -1.000000f, 0.0f, 0.0f,

		 1.000000f,  0.003296f, -1.000000f, 0.0f, 0.0f,
		-0.000000f,  1.000000f,  0.000000f, 0.0f, 0.0f,
		 1.000000f,  0.003296f,  1.000000f, 0.0f, 0.0f,

		 1.000000f,  0.003296f,  1.000000f, 0.0f, 0.0f,
		-0.000000f,  1.000000f,  0.000000f, 0.0f, 0.0f,
		-1.000000f,  0.003296f,  1.000000f, 0.0f, 0.0f,

		-1.000000f,  0.003296f,  1.000000f, 0.0f, 0.0f,
		-0.000000f,  1.000000f,  0.000000f, 0.0f, 0.0f,
		-1.000000f,  0.003296f, -1.000000f, 0.0f, 0.0f,

		-0.000000f,  1.000000f,  0.000000f, 0.0f, 0.0f,
		 1.000000f,  0.003296f, -1.000000f, 0.0f, 0.0f,
		-1.000000f,  0.003296f, -1.000000f, 0.0f, 0.0f,

		 1.000000f,  0.003296f,  1.000000f, 0.0f, 0.0f,
		-1.000000f,  0.003296f,  1.000000f, 0.0f, 0.0f,
		-1.000000f,  0.003296f, -1.000000f, 0.0f, 0.0f,
	};*/
	//va = new VertexArray(vertices, 3, 36, true);
	//va->setType(GL_TRIANGLES);

	//setCurrentControlPoints();
	//glEnable(GL_PROGRAM_POINT_SIZE);

	/*string fileName = "objs/coffee_cup.colour.png";
	float* pixels = stbi_loadf(fileName.c_str(), &picWidth, &picHeight, &channels, 0);
	if (pixels == nullptr) {
		cerr << "Error loading image " << fileName << ": " << stbi_failure_reason() << endl;
		return -1;
	}*/

	/*glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, picWidth, picHeight, 0, GL_RGB, GL_FLOAT, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pixels);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	// Create aspect ratio scaling
	//float larger = (picWidth >= picHeight) ? picWidth : picHeight;
	//float scaleX = picWidth / larger;
	//float scaleY = picHeight / larger;

	//aspectRatioScaling = vec3(scaleX, scaleY, 1.0f);

	//setModel();
	//setTransform();

	objModel = new Model("timmy_cup", shaderProgram, "timmy_cup.colour.png");

	shaderProgram.bind();

	//view = mat4();
	//view = translate(view, vec3(0.0f, 0.0f, -4.0f));
	//shaderProgram.setMat4("view", view);

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

void Program::render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//setModel();
	shaderProgram.bind();
	//shaderProgram.setInt("curve", false);
	//va->draw();

	objModel->draw();

	//shaderProgram.setInt("curve", true);
	//currentControlPoints->draw();
	//for (VertexArray *controlPointSet : controlPointSets) {
	//	controlPointSet->draw();
	//}
	//tessellationProgram.bind();
	//for (VertexArray *curve : curves) {
	//	curve->draw();
	//}

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
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);

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

	/*if (!tessellationProgram.attachShader("data/tessellationVertex.glsl", GL_VERTEX_SHADER))
		return terminate("Error attaching tessellation vertex shader");

	if (!tessellationProgram.attachShader("data/tessellationFragment.glsl", GL_FRAGMENT_SHADER))
		return terminate("Error attaching tessellation fragment shader");

	if (!tessellationProgram.attachShader("data/tessellationControl.glsl", GL_TESS_CONTROL_SHADER))
		return terminate("Error attaching tessellation control shader");

	if (!tessellationProgram.attachShader("data/tessellationEvaluation.glsl", GL_TESS_EVALUATION_SHADER))
		return terminate("Error attaching tessellation evaluation shader");

	if (!tessellationProgram.link())
		return terminate("Error linking tessellation shader program");*/

	return !OpenGL::error("Program::initShaders() assert");
}

void Program::setModel()
{
	model = mat4(1.0f);
	//model = translate(model, reverseTranslation);
	//model = scale(model, reverseScaling);
	//model = scale(model, aspectRatioScaling);
	//model = glm::rotate(model, glm::radians(50.0f), vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, glm::radians((float)((int)glfwGetTime() % 360)), vec3(0.0f, 1.0f, 0.0f));
	shaderProgram.bind();
	shaderProgram.setMat4("model", model);
	//tessellationProgram.bind();
	//tessellationProgram.setMat4("model", model);
}

void Program::setTransform()
{
	/*transform = mat4();
	transform = translate(transform, vec3(translation, 0.0));
	transform = scale(transform, vec3(scaleFactor, scaleFactor, 1.0f));
	shaderProgram.bind();
	shaderProgram.setMat4("transform", transform);
	tessellationProgram.bind();
	tessellationProgram.setMat4("transform", transform);*/
}

void Program::setQuantizationLevel(int level)
{
	shaderProgram.bind();
	shaderProgram.setInt("quantizationLevel", level);
}

void Program::setGrayscale()
{
	//shaderProgram.bind();
	//shaderProgram.setInt("grayscale", grayscale);
}

void Program::setAoMode()
{
	shaderProgram.bind();
	shaderProgram.setInt("aoMode", aoMode);
}

void Program::renderCurve()
{
	//VertexArray *controlPointSet = new VertexArray(controlPoints, 2, controlPoints.size() / 2, false);
	//controlPointSet->setType(GL_POINTS);
	//controlPointSets.push_back(controlPointSet);
	vec2 first = vec2(controlPoints.at(0), controlPoints.at(1));
	controlPoints.insert(controlPoints.begin(), first.y);
	controlPoints.insert(controlPoints.begin(), first.x);
	vec2 last = vec2(controlPoints.at(controlPoints.size() - 2), controlPoints.at(controlPoints.size() - 1));
	controlPoints.push_back(last.x);
	controlPoints.push_back(last.y);
	vector<float> expandedPoints;
	for (int i = 0; ((i / 2) + 3) < (controlPoints.size() / 2); i+=2) {
		for (int n = 0; n < 8; n++) {
			expandedPoints.push_back(controlPoints.at(i + n));
		}
	}
	if (closedMode && ((controlPoints.size() / 2) > 4)) {
		vector<float> closingSegment;
		closingSegment.push_back(expandedPoints.at(expandedPoints.size() - 6));
		closingSegment.push_back(expandedPoints.at(expandedPoints.size() - 5));
		closingSegment.push_back(expandedPoints.at(expandedPoints.size() - 4));
		closingSegment.push_back(expandedPoints.at(expandedPoints.size() - 3));
		closingSegment.push_back(expandedPoints.at(2));
		closingSegment.push_back(expandedPoints.at(3));
		closingSegment.push_back(expandedPoints.at(4));
		closingSegment.push_back(expandedPoints.at(5));
		for (float point : closingSegment) {
			expandedPoints.push_back(point);
		}
	}
	//VertexArray *curve = new VertexArray(expandedPoints, 2, expandedPoints.size() / 2, false);
	//curve->setType(GL_PATCHES);
	//curves.push_back(curve);
	controlPoints.clear();
	setCurrentControlPoints();
}

void Program::setCurrentControlPoints()
{
	//currentControlPoints = new VertexArray(controlPoints, 2, controlPoints.size() / 2, false);
	//currentControlPoints->setType(GL_POINTS);
}

void Program::sizeCallback(GLFWwindow * window, int width, int height)
{
	static_cast<Program*>(glfwGetWindowUserPointer(window))->sizeChange(width, height);
}

void Program::sizeChange(int width, int height)
{
	//reverseTranslation = vec3(-(width - this->originalWidth), -(height - this->originalHeight), 0.0);
	//reverseTranslation.x *= (2 / (double)width);
	//reverseTranslation.y *= (2 / (double)height);

	//reverseScaling = vec3((double)1 / ((double)width / (double)(this->originalWidth)), (double)1 / ((double)height / (double)(this->originalHeight)), 1.0f);

	//setModel();

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
	if ((key >= 49) && (key <= 56)) {
		//setQuantizationLevel(key - 48);
		return;
	}
	switch (key) {
		case GLFW_KEY_Q:
			//live = false;
			break;
		case GLFW_KEY_O:
			aoMode = !aoMode;
			setAoMode();
			break;
		case GLFW_KEY_R:
			//renderCurve();
			break;
		case GLFW_KEY_C:
			//closedMode = !closedMode;
			break;
		case GLFW_KEY_DELETE:
		case GLFW_KEY_BACKSPACE:
			/*if (controlPoints.size() > 1) {
				controlPoints.pop_back();
				controlPoints.pop_back();
				setCurrentControlPoints();
			}
			else if (curves.size() > 0) {
				curves.pop_back();
				controlPointSets.pop_back();
			}*/
			break;
	}
}

void Program::scrollCallback(GLFWwindow * window, double xOffset, double yOffset)
{
	static_cast<Program*>(glfwGetWindowUserPointer(window))->scrollChange(xOffset, yOffset);
}

void Program::scrollChange(double xOffset, double yOffset)
{
	/*if (yOffset > 0) {
		scaleFactor *= 1.1;
		setTransform();
	}
	else if (yOffset < 0) {
		scaleFactor *= 0.9;
		setTransform();
	}*/
}

void Program::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	static_cast<Program*>(glfwGetWindowUserPointer(window))->mouseButtonInput(button, action, mods);
}

void Program::mouseButtonInput(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			/*buttonPressed = true;
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			pressOrigin = vec2(xPos, yPos);*/
		}
		else if (action == GLFW_RELEASE) {
			/*buttonPressed = false;
			previousTranslation = translation;
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			releaseLocation = vec2(xPos, yPos);
			if (releaseLocation == pressOrigin) {
				releaseLocation.x = (releaseLocation.x / (width / (float)2)) - 1.0;
				releaseLocation.y = ((height - releaseLocation.y) / (height / (float)2)) - 1.0;
				mat4 transformMatrix = transform * model;
				mat4 inverse = glm::inverse(transformMatrix);
				glm::vec4 vertice = glm::vec4(releaseLocation, 0.0, 1.0);
				releaseLocation = inverse * vertice;
				controlPoints.push_back(releaseLocation.x);
				controlPoints.push_back(releaseLocation.y);
				setCurrentControlPoints();
			}*/
		}
	}
}

void Program::cursorPositionCallback(GLFWwindow * window, double xPos, double yPos)
{
	static_cast<Program*>(glfwGetWindowUserPointer(window))->cursorPositionChange(xPos, yPos);
}

void Program::cursorPositionChange(double xPos, double yPos)
{
	/*if (buttonPressed) {
		translation = vec2(xPos, yPos) - pressOrigin;
		translation.y = -translation.y;
		translation.x *= (2 / (float)width);
		translation.y *= (2 / (float)height);
		translation = previousTranslation + translation;
		setTransform();
	}*/
}

bool Program::terminate(string message)
{
	cerr << "ERROR: " << message << endl;
	glfwTerminate();
	return false;
}

int main(int argc, const char** argv) {
	/*A a;
	a.testInt = 472;
	a.testStr = "Initial test string in A";
	B b(a);
	a.testInt = 35;
	a.testStr = "changed test string in A";
	return 0;*/
	Program p;
	return p.run(argc, argv);
}
