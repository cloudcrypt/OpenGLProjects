// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
//
// Author: Daniel Dastoor
// Date:   November 2017
// ==========================================================================

#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"

using std::string;

struct Material {
	float specularExp;
	vec3 specular;
	GLuint diffuse;
	GLuint ao;
	vec3 ambient;
};

class Model
{
public:

	float scaleFactor = 1.0f;
	int pitch = 0;								// rotation about x-axis
	int yaw = 0;								// rotation about y-axis
	int roll = 0;								// rotation about z-axis

	Model(string modelName, const ShaderProgram &sp, string textureFile);
	~Model();
	void draw();
	void translate(float x, float y, float z);
	BoundingBox getBoundingBox();
	void processKeyboard(int key);
private:
	mat4 modelMatrix;
	Material material;
	vec3 translation = vec3(0.0f, 0.0f, 0.0f);

	const ShaderProgram &shaderProgram;
	vector<Mesh> meshes;
	void setModelMatrix();
	void setMaterial();
	void setTextures();
	void loadModel(string objFile);
	void loadMaterial(string mtlFile, string modelName);
	void loadTextures(string modelName, string textureType);
};

