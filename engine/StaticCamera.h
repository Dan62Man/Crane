#pragma once
#include "PerspectiveCamera.h"
class ENGINE_API StaticCamera : public PerspectiveCamera
{
public:
	StaticCamera(string name, glm::vec3 eye, glm::vec3 center, float fov, float aspect, float nearPlane, float farPlane);
	~StaticCamera();

private:

};

