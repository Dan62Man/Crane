#include "CabinCamera.h"

int CabinCamera::cnt = 0;
CabinCamera::CabinCamera(string name, glm::vec3 eye, glm::vec3 center, float fov, float aspect, float nearPlane, float farPlane)
	: PerspectiveCamera(name, CameraType::CABIN, eye, center, fov, aspect, nearPlane, farPlane) 
{
	if (cnt > 0)
	{
		cout << "Unable to create more than 1 cabin camera" << endl;
		isAvailable = false;
		return;
	}

	cnt++;
	isAvailable = true;
}

CabinCamera::~CabinCamera()
{
	cout << "[Destroyed CABIN_CAMERA: " << CabinCamera::getName() << "(" << CabinCamera::getId() << ")" << "]" << endl;
}

