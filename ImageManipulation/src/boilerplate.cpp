//// ==========================================================================
//// CPSC 453 Assignment #1: Generating and Rendering a Hilbert Curve
//// Daniel Dastoor
////  
//// Based on an Object-Oriented Boilerplate Code for GLFW
////
//// Author: Daniel Dastoor, Kamyar Allahverdi, University of Calgary. Minor tweaks by Haysn Hornbeck.
//// Date:   October 2017
//// ==========================================================================
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <vector>
//#include <map>
//#include <cmath>
//
//#include <GL/glew.h>
//
////#define GLFW_INCLUDE_GLCOREARB
//#define GL_GLEXT_PROTOTYPES
//#include <GLFW/glfw3.h>
//
//#include "Hilbert.h"
//
//using std::string;
//using std::vector;
//using std::cout;
//using std::cerr;
//using std::endl;
//using std::pow;
//using std::sqrt;
//
//class Program1 {
//	GLuint vertex_shader;
//	GLuint fragment_shader;
//public:
//	GLuint id;
//	Program1() {
//		vertex_shader = 0;
//		fragment_shader = 0;
//		id = 0;
//	}
//	Program1(string vertex_path, string fragment_path) {
//		init(vertex_path, fragment_path);
//	}
//	void init(string vertex_path, string fragment_path) {
//		id = glCreateProgram();
//		vertex_shader = addShader(vertex_path, GL_VERTEX_SHADER);
//		fragment_shader = addShader(fragment_path, GL_FRAGMENT_SHADER);
//		if (vertex_shader)
//			glAttachShader(id, vertex_shader);
//		if (fragment_shader)
//			glAttachShader(id, fragment_shader);
//
//		glLinkProgram(id);
//	}
//	GLuint addShader(string path, GLuint type) {
//		std::ifstream in(path);
//		string buffer = [&in] {
//			std::ostringstream ss {};
//			ss << in.rdbuf();
//			return ss.str();
//		}();
//		const char *buffer_array[] = { buffer.c_str() };
//
//		GLuint shader = glCreateShader(type);
//
//		glShaderSource(shader, 1, buffer_array, 0);
//		glCompileShader(shader);
//
//		// Compile results
//		GLint status;
//		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
//		if (status == GL_FALSE) {
//			GLint length;
//			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
//			string info(length, ' ');
//			glGetShaderInfoLog(shader, info.length(), &length, &info[0]);
//			cerr << "ERROR compiling shader:" << endl << endl;
//			cerr << info << endl;
//		}
//		return shader;
//	}
//	~Program1() {
//		glUseProgram(0);
//		glDeleteProgram(id);
//		glDeleteShader(vertex_shader);
//		glDeleteShader(fragment_shader);
//	}
//};
//
//class VertexArray1 {
//	std::map<string, GLuint> buffers;
//	std::map<string, int> indices;
//public:
//	GLuint id;
//	unsigned int count;
//	VertexArray1(int c) {
//		glGenVertexArrays(1, &id);
//		count = c;
//	}
//
//	VertexArray1(const VertexArray1 &v) {
//		glGenVertexArrays(1, &id);
//
//		// Copy data from the old object
//		this->indices = std::map<string, int>(v.indices);
//		count = v.count;
//
//		vector<GLuint> temp_buffers(v.buffers.size());
//
//		// Allocate some temporary buffer object handles
//		glGenBuffers(v.buffers.size(), &temp_buffers[0]);
//
//		// Copy each old VBO into a new VBO
//		int i = 0;
//		for (auto &ent : v.buffers) {
//			int size = 0;
//			glBindBuffer(GL_ARRAY_BUFFER, ent.second);
//			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//
//			glBindBuffer(GL_COPY_READ_BUFFER, temp_buffers[i]);
//			glBufferData(GL_COPY_READ_BUFFER, size, NULL, GL_STATIC_COPY);
//
//			glCopyBufferSubData(GL_ARRAY_BUFFER, GL_COPY_READ_BUFFER, 0, 0,
//					size);
//			i++;
//		}
//
//		// Copy those temporary buffer objects into our VBOs
//
//		i = 0;
//		for (auto &ent : v.buffers) {
//			GLuint buffer_id;
//			int size = 0;
//			int index = indices[ent.first];
//
//			glGenBuffers(1, &buffer_id);
//
//			glBindVertexArray(this->id);
//			glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
//			glBindBuffer(GL_COPY_READ_BUFFER, temp_buffers[i]);
//			glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
//
//			// Allocate VBO memory and copy
//			glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
//			glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0,
//					size);
//			string indexs = ent.first;
//
//			buffers[ent.first] = buffer_id;
//			indices[ent.first] = index;
//
//			// Setup the attributes
//			size = size / (sizeof(float) * this->count);
//			glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, 0);
//			glEnableVertexAttribArray(index);
//			glBindBuffer(GL_ARRAY_BUFFER, 0);
//			glBindVertexArray(0);
//			i++;
//		}
//
//		// Delete temporary buffers
//		glDeleteBuffers(v.buffers.size(), &temp_buffers[0]);
//	}
//
//	void addBuffer(string name, int index, vector<float> buffer) {
//		GLuint buffer_id;
//		glBindVertexArray(id);
//
//		glGenBuffers(1, &buffer_id);
//		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
//		glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),
//				buffer.data(), GL_STATIC_DRAW);
//		buffers[name] = buffer_id;
//		indices[name] = index;
//
//		int components = buffer.size() / count;
//		glVertexAttribPointer(index, components, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(index);
//
//		// unset states
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//	}
//
//	void updateBuffer(string name, vector<float> buffer) {
//		glBindBuffer(GL_ARRAY_BUFFER, buffers[name]);
//		glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),
//				buffer.data(), GL_STATIC_DRAW);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	}
//	~VertexArray1() {
//		glBindVertexArray(0);
//		glDeleteVertexArrays(1, &id);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		for (auto &ent : buffers)
//			glDeleteBuffers(1, &ent.second);
//	}
//};
//
//// Initialize global values for recursion level, rendering representations,
//// and a Hilbert object.
//int n = 1;
//Hilbert::Mode mode = Hilbert::Mode::Lines;
//Hilbert h;
//// Global values for window width and height
//int width = 512;
//int height = 512;
//
//void render(Program1 &program, VertexArray1 &va) {
//	// clear screen to a dark grey colour
//	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glUseProgram(program.id);
//	glBindVertexArray(va.id);	
//	if (mode == Hilbert::Mode::Lines) {
//		glDrawArrays(GL_POINTS, 0, va.count);
//		glDrawArrays(GL_LINE_STRIP, 0, va.count);
//	} else if (mode == Hilbert::Mode::Rectangles) {
//		glDrawArrays(GL_TRIANGLES, 0, va.count);
//	}
//	glEnable(GL_PROGRAM_POINT_SIZE);
//
//	glBindVertexArray(0);
//	glUseProgram(0);
//
//}
//
//// Callback functions for key press events
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    if (key == GLFW_KEY_Q && action == GLFW_PRESS) { // Terminate program if 'q' is pressed
//		glfwTerminate();
//		exit(0);
//	} else if (key == GLFW_KEY_UP && action == GLFW_PRESS) { // Increment n if 'up arrow' is pressed and if n value is allowed for the given mode and window size
//		if (mode == Hilbert::Mode::Lines) {
//			float maxGridAmount = width / 16;
//			float maxNValue = sqrt(maxGridAmount);
//			if (n < maxNValue) {
//				n++;
//			}
//		} else {
//			float maxGridAmount = width / 8;
//			float maxNValue = sqrt(maxGridAmount);
//			if (n < maxNValue) {
//				n++;
//			}
//		}
//	} else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) { // Decrement n if 'down arrow' is pressed
//		if (n > 1) {
//			n--;
//		}
//	} else if (key == GLFW_KEY_M && action == GLFW_PRESS) { // Switch rendering representation mode if 'm' is pressed
//		if (mode == Hilbert::Mode::Lines) {
//			mode = Hilbert::Mode::Rectangles;
//		} else {
//			mode = Hilbert::Mode::Lines;
//		}
//	}
//}
//
//// Callback function to resize and redraw the curve and screen to cover
//// the entire viewport when the window size changes
//void window_size_callback(GLFWwindow* window, int w, int h)
//{
//	width = w;
//	height = h;
//	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//
//	glViewport(0, 0, w, h);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//	glfwSwapBuffers(window);
//}
//
//int main(int argc, char *argv[]) {
//	// initialize the GLFW windowing system
//	if (!glfwInit()) {
//		cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
//		return -1;
//	}
//	glfwSetErrorCallback([](int error, const char* description) {
//		cout << "GLFW ERROR " << error << ":" << endl;
//		cout << description << endl;
//	});
//	
//	// Use OpenGL 4.1
//	GLFWwindow *window = 0;
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	window = glfwCreateWindow(width, height, "CPSC 453 Assignment #1", 0, 0);
//	if (!window) {
//		cout << "Program failed to create GLFW window, TERMINATING" << endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//	
//	GLenum err = glewInit();
//	if(err != GLEW_OK) {
//		std::cerr << "GLEW failed to initialize with error: " << glewGetErrorString(err) <<  '\n';
//		glfwTerminate();
//		exit(-1);	
//	}
//
//	Program1 p("data/vertex.glsl", "data/fragment.glsl");
//
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetWindowSizeCallback(window, window_size_callback);
//
//	// run an event-triggered main loop
//	while (!glfwWindowShouldClose(window)) {
//		// generate Hilbert curve at recursion level: n and mode: mode
//		h.generate(n, mode);
//		VertexArray1 va(h.vertices.size() / 2);
//		va.addBuffer("v", 0, h.vertices);
//		// render
//		render(p, va);
//
//		glfwSwapBuffers(window);
//
//		glfwPollEvents();
//	}
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//
//	cout << "The End" << endl;
//	return 0;
//}
