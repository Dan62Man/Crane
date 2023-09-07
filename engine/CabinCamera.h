#pragma once
#include "PerspectiveCamera.h"

class ENGINE_API CabinCamera : public PerspectiveCamera
{
public:
	CabinCamera(string name, glm::vec3 eye, glm::vec3 center, float fov, float aspect, float nearPlane, float farPlane);
	~CabinCamera();


private:
	static int cnt;
};

