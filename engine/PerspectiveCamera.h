#pragma once
#include "Camera.h"
#include "CameraType.h"

class ENGINE_API PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(string name, CameraType type, glm::vec3 eye, glm::vec3 center, float fov, float aspect, float nearPlane, float farPlane);
	~PerspectiveCamera();

	CameraType getType();
	bool getIsAvailable();
	glm::vec3 getEye() const;
	void setEye(glm::vec3 eye);
	glm::vec3 getCenter() const;
	void setCenter(glm::vec3 center);
	float getAspect() const;

	void updateMatrix();
	void setProjection(float aspect);

private:
	CameraType type;
	bool isAvailable;
	glm::vec3 eye; // position of camera
	glm::vec3 center; // position point camera is looking at
	glm::vec3 up; // orientation of the world (default)
	float fov;
	float aspect;
	static int cntCabin;
};

