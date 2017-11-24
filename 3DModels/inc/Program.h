// ==========================================================================
// CPSC 453 Assignment #2: Image Manipulation
// Daniel Dastoor
// Program.h
// Class to display and manipulate images and catmull-rom splines.
//
// Author: Daniel Dastoor
// Date:   November 2017
// ==========================================================================

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "Camera.h"
#include "Model.h"
#include "glm/glm.hpp"

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
	ShaderProgram tessellationProgram;

	VertexArray* va;
	VertexArray* currentControlPoints;

	vector<float> controlPoints;
	vector<float> readyPoints;

	vector<VertexArray*> curves;
	vector<VertexArray*> controlPointSets;

	Model *objModel;
	Camera *camera;

	mat4 model;
	mat4 view;
	mat4 projection;
	//mat4 transform;

	char *windowName = "3DModels";
	int width = 1024;
	int originalWidth = width;
	int height = 1024;
	int originalHeight = height;
	float scaleFactor = 1.0f;

	bool buttonPressed = false;
	bool grayscale = false;
	bool closedMode = false;

	vec3 reverseTranslation = vec3(0.0, 0.0, 0.0);
	vec3 reverseScaling = vec3(1.0, 1.0, 1.0);
	vec3 aspectRatioScaling = vec3(1.0, 1.0, 1.0);
	vec2 pressOrigin;
	vec2 releaseLocation;
	vec2 previousTranslation = vec2(0.0, 0.0);
	vec2 translation = vec2(0.0, 0.0);

	void render();
	bool initGLFW();
	bool initGLEW();
	bool initShaders();

	void setModel();
	void setTransform();
	void setQuantizationLevel(int level);
	void setGrayscale();
	void renderCurve();
	void setCurrentControlPoints();

	static void sizeCallback(GLFWwindow* window, int width, int height);
	void sizeChange(int width, int height);

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void keyInput(int key, int scancode, int action, int mods);

	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void scrollChange(double xoffset, double yoffset);

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void mouseButtonInput(int button, int action, int mods);

	static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
	void cursorPositionChange(double xPos, double yPos);

	bool terminate(string message);

public:
	Program() { }
	int run(int argc, const char** argv);
};

