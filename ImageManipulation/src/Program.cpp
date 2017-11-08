#include "Program.h"
#include "OpenGL.h"
#include <iostream>
#include <GL/glew.h>

#include <cmath>
#include "Hilbert.h"
#include "VertexArray.h"

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::pow;
using std::sqrt;

using std::cerr;
using std::endl;

GLuint texture;

int Program::run(int argc, const char ** argv)
{
	if (!initGLFW() || !initGLEW() || !initShaders())
		return -1;
	
	va = new VertexArray(vector<float> { 
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	}, 2);
	va->setType(GL_TRIANGLES);

	int picWidth, picHeight, channels;
	string fileName = "sign.jpg";
	float* pixels = stbi_loadf(fileName.c_str(), &picWidth, &picHeight, &channels, 0);
	if (pixels == nullptr) {
		cerr << "Error loading image " << fileName << ": " << stbi_failure_reason() << endl;
		return -1;
	}

	//GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, picWidth, picHeight, 0, GL_RGB, GL_FLOAT, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	while (live) {
		render(texture);
		glfwPollEvents();
		if (glfwWindowShouldClose(window))
			live = false;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void Program::render(GLuint texture)
{
	//h.generate(n, mode);
	////VertexArray va(vector<float> { -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 1.0f }, 2);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture);
	shaderProgram.bind();
	va->draw();

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
	// Set up a callbacks
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

void Program::sizeCallback(GLFWwindow * window, int width, int height)
{
	static_cast<Program*>(glfwGetWindowUserPointer(window))->sizeChange(width, height);
}

void Program::sizeChange(int width, int height)
{
	this->width = width;
	this->height = height;
	//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	glViewport(0, 0, width, height);
	
	//glClear(GL_COLOR_BUFFER_BIT);
	render(texture);
	//glfwSwapBuffers(window);
}

void Program::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Program*>(glfwGetWindowUserPointer(window))->keyInput(key, scancode, action, mods);
}

void Program::keyInput(int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
		return;
	switch (key) {
		case GLFW_KEY_Q:
			live = false;
			break;
		case GLFW_KEY_UP:
			if (mode == Hilbert::Mode::Lines) {
				float maxGridAmount = width / 16;
				float maxNValue = sqrt(maxGridAmount);
				if (n < maxNValue) {
					n++;
				}
			} else {
				float maxGridAmount = width / 8;
				float maxNValue = sqrt(maxGridAmount);
				if (n < (int)maxNValue) {
					n++;
				}
			}
			break;
		case GLFW_KEY_DOWN:
			if (n > 1)
				n--;
			break;
		case GLFW_KEY_M:
			break;
	}
}

bool Program::terminate(string message)
{
	cerr << "ERROR: " << message << endl;
	glfwTerminate();
	return false;
}

int main(int argc, const char** argv) {
	Program p;
	return p.run(argc, argv);
}
