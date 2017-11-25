// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
// OpenGL.h
// Class to query and display OpenGl error messages
//
// Author: Daniel Dastoor, based on code by Haysn Hornbeck
// Date:   November 2017
// ==========================================================================

#include <string>

using std::string;

class OpenGL
{
public:
	static bool error(string tag);
};

