#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"

using std::string;

class Model
{
public:
	Model(string objFile, const ShaderProgram &sp);
	~Model();
	void draw();
	void processKeyboard(int key);
private:
	mat4 modelMatrix;

	float scaleFactor = 1.0f;
	int pitch = 0;								// rotation about x-axis
	int yaw = 0;								// rotation about y-axis
	int roll = 0;								// rotation about z-axis

	const ShaderProgram &shaderProgram;
	vector<Mesh> meshes;
	void setScaling();
	void setPitch();
	void setYaw();
	void setRoll();
	void setModelMatrix();
	void loadModel(string objFile);
};

