#pragma once
#include "Node.h"

class ENGINE_API Camera : public Node
{
public:
	Camera(string name, float nearPlane, float farPlane);
	virtual ~Camera();

	glm::mat4 getProjection();

protected:
	glm::mat4 projection;
	float nearPlane;
	float farPlane;
};

