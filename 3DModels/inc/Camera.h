#pragma once

#include "glm/glm.hpp"

#include "ShaderProgram.h"

#include "Mesh.h"

using glm::vec3;
using glm::mat4;

class Camera
{
private:

	float speed = 0.05f;

	mat4 view;
	vec3 pos;
	vec3 target;
	vec3 direction;
	vec3 up;

	const ShaderProgram &shaderProgram;

	void setView();

public:
	Camera(const ShaderProgram &sp, BoundingBox boundingBox, vec3 pos = vec3(0.0f, 0.0f, 3.0f));

	void processKeyboard(int key);

	~Camera();
};

//class A 
//{
//public:
//	int testInt;
//	string testStr;
//	A() { }
//};
//
//class B
//{
//public:
//	const A &testA;
//	B(const A &testA): testA(testA)
//	{
//		//testA.testStr = string("changeddd");
//		//this->testA = &testA;
//	}
//};
