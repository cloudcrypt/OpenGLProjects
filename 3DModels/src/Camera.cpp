// ==========================================================================
// CPSC 453 Assignment #3: 3D Models
// Daniel Dastoor
//
// Author: Daniel Dastoor
// Date:   November 2017
// ==========================================================================

#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

using glm::lookAt;
using glm::normalize;
using glm::cross;

void Camera::setView()
{
	view = lookAt(pos, pos + direction, up);
	shaderProgram.bind();
	shaderProgram.setMat4("view", view);
	shaderProgram.setVec3("cameraPos", pos);
}

Camera::Camera(const ShaderProgram &sp, BoundingBox boundingBox, vec3 pos): shaderProgram(sp)
{
	float neededHeight;
	float neededDistance;
	if (boundingBox.y >= boundingBox.x && boundingBox.y >= boundingBox.z) {
		neededHeight = (boundingBox.y / (float)2) * 1.5f;
		neededDistance = neededHeight / glm::tan(glm::radians((float)45 / (float)2));
	} else if (boundingBox.x >= boundingBox.y && boundingBox.x >= boundingBox.z) {
		neededHeight = (boundingBox.x / (float)2) * 1.5f;
		neededDistance = neededHeight / glm::tan(glm::radians((float)45 / (float)2));
	} else {
		neededDistance = boundingBox.z * 1.5f;
	}

	this->pos = vec3(0.0f, 0.0f, neededDistance);

	target = vec3(0.0f, 0.0f, 0.0f);
	direction = normalize(target - pos);
	up = vec3(0.0f, 1.0f, 0.0f);
	setView();
}

void Camera::processKeyboard(int key)
{
	switch (key) {
	case GLFW_KEY_LEFT:
		pos -= normalize(cross(direction, up)) * speed;
		setView();
		break;
	case GLFW_KEY_RIGHT:
		pos += normalize(cross(direction, up)) * speed;
		setView();
		break;
	}
}

Camera::~Camera()
{

}
