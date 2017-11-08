#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
//#include "Hilbert.h"
#include "ShaderProgram.h"
#include "VertexArray.h"

using std::endl;

using std::string;

class Program
{
private:

	/*int n = 1;
	Hilbert::Mode mode = Hilbert::Mode::Rectangles;
	Hilbert h;*/

	bool live = true;
	GLFWwindow* window = nullptr;
	ShaderProgram shaderProgram;
	VertexArray* va;
	char *windowName = "ImageManipulation";
	int width = 1024;
	int height = 768;
	void render(GLuint texture, int w, int h);
	bool initGLFW();
	bool initGLEW();
	bool initShaders();
	static void sizeCallback(GLFWwindow* window, int width, int height);
	void sizeChange(int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void keyInput(int key, int scancode, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void scrollChange(double xoffset, double yoffset);
	bool terminate(string message);
public:
	Program() { }
	int run(int argc, const char** argv);
};

