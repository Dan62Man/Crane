#pragma once
#include "PerspectiveCamera.h"

class ENGINE_API DynamicCamera : public PerspectiveCamera
{
public:
	DynamicCamera(string name, glm::vec3 eye, glm::vec3 center, float fov, float aspect, float nearPlane, float farPlane);
	~DynamicCamera();

private:

};

