#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"

using std::string;

struct Material {
	float specularExp;
	vec3 specular;
	vec3 diffuse;
	vec3 ambient;
};

class Model
{
public:
	Model(string objFile, const ShaderProgram &sp);
	~Model();
	void draw();
	void processKeyboard(int key);
private:
	mat4 modelMatrix;
	Material material;

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
	void setMaterial();
	void loadModel(string objFile);
	void loadMaterial(string mtlFile);
};

