#pragma once
#include "Camera.h"

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(string name, float left, float right, float bottom, float top, float nearPlane=-1.0f, float farPlane=1.0f);
	~OrthographicCamera();

	void setProjection(float right, float top);

private:
	float left;
	float right;
	float bottom;
	float top;
};

	