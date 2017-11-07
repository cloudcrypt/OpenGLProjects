#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Hilbert.h"

using std::string;

class Program
{
private:

	int n = 1;
	Hilbert::Mode mode = Hilbert::Mode::Rectangles;
	Hilbert h;

	bool live = true;
	GLFWwindow* window = nullptr;
	char *windowName = "ImageManipulation";
	int width = 1024;
	int height = 768;
	void render();
	bool initGLFW();
	bool initGLEW();
	static void sizeCallback(GLFWwindow* window, int width, int height);
	void sizeChange(int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void keyInput(int key, int scancode, int action, int mods);
	bool terminate(string message);
public:
	Program() { }
	int run(int argc, const char** argv);
};

