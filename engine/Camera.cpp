#include "Camera.h"
#include "GL/freeglut.h"

Camera::Camera(string name, float nearPlane, float farPlane) : Node(name)
{
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
}

Camera::~Camera() {}

glm::mat4 Camera::getProjection()
{
	return projection;
}