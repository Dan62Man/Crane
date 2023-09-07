#include "StaticCamera.h"

StaticCamera::StaticCamera(string name, glm::vec3 eye, glm::vec3 center, float fov, float aspect, float nearPlane, float farPlane)
: PerspectiveCamera(name, CameraType::STATIC, eye, center, fov, aspect, nearPlane, farPlane) 
{ 
    isAvailable = true;
}

StaticCamera::~StaticCamera()
{
	cout << "[Destroyed STATIC_CAMERA: " << StaticCamera::getName() << "(" << StaticCamera::getId() << ")" << "]" << endl;
}

