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

Camera::Camera(const ShaderProgram &sp, vec3 pos): shaderProgram(sp)
{
	this->pos = pos;
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
