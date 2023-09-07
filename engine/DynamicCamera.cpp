#include "DynamicCamera.h"

DynamicCamera::DynamicCamera(string name, glm::vec3 eye, glm::vec3 center, float fov, float aspect, float nearPlane, float farPlane)
	: PerspectiveCamera(name, CameraType::DYNAMIC, eye, center, fov, aspect, nearPlane, farPlane) 
{ 
	isAvailable = true;
}

DynamicCamera::~DynamicCamera()
{
	cout << "[Destroyed DYNAMIC_CAMERA: " << DynamicCamera::getName() << "(" << DynamicCamera::getId() << ")" << "]" << endl;
}