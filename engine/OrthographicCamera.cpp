#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(string name, float left, float right, float bottom, float top, float nearPlane, float farPlane) : Camera(name, nearPlane, farPlane)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
}

OrthographicCamera::~OrthographicCamera()
{
	cout << "[Destroyed ORTHOGRAPHIC CAMERA: " << OrthographicCamera::getName() << "(" << OrthographicCamera::getId() << ")" << "]" << endl;
}

void OrthographicCamera::setProjection(float right, float top)
{
	projection = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}
