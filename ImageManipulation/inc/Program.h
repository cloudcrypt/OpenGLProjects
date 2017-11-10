#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
//#include "Hilbert.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "glm/glm.hpp"

using std::endl;
using std::string;
using glm::vec2;
using glm::vec3;

class Program
{
private:

	/*int n = 1;
	Hilbert::Mode mode = Hilbert::Mode::Rectangles;
	Hilbert h;*/

	bool live = true;
	GLFWwindow* window = nullptr;
	ShaderProgram shaderProgram;
	ShaderProgram tessellationProgram;
	VertexArray* va;
	VertexArray* va2;
	VertexArray* curve;
	vector<float> controlPoints;
	mat4 model;
	mat4 transform;
	char *windowName = "ImageManipulation";
	int width = 1024;
	int originalWidth = width;
	int height = 1024;
	int originalHeight = height;
	float scaleFactor = 1.0f;
	bool buttonPressed = false;
	bool grayscale = false;
	bool curveMode = false;
	vec3 reverseTranslation = vec3(0.0, 0.0, 0.0);
	vec3 reverseScaling = vec3(1.0, 1.0, 1.0);
	vec3 aspectRatioScaling = vec3(1.0, 1.0, 1.0);
	vec2 pressOrigin;
	vec2 releaseLocation;
	vec2 previousTranslation = vec2(0.0, 0.0);
	vec2 translation = vec2(0.0, 0.0);
	void render(GLuint texture, int w, int h);
	bool initGLFW();
	bool initGLEW();
	bool initShaders();
	void setModel();
	void setTransform();
	void setQuantizationLevel(int level);
	void setGrayscale();
	void prepareControlPoints();
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

