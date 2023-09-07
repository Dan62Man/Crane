#include "PerspectiveCamera.h"

int PerspectiveCamera::cntCabin = 0;
ENGINE_API PerspectiveCamera::PerspectiveCamera(string name, CameraType type, glm::vec3 eye, glm::vec3 center, float fov, float aspect, float nearPlane, float farPlane) : Camera(name, nearPlane, farPlane)
{
	if (type == CameraType::CABIN)
	{
		cntCabin++;
		if (cntCabin <= 1)
			isAvailable = true;
		else
		{
			isAvailable = false;
			cout << "Unble to create " << cntCabin << " cabin cameras (max 1)" << endl;
			return;
		}
	}
	else
		isAvailable = true;

	this->type = type;
	this->eye = eye;
	this->center = center;
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->fov = fov;

	updateMatrix();
	setProjection(aspect);
}

ENGINE_API PerspectiveCamera::~PerspectiveCamera()
{
	cout << "[Destroyed PERSPECTIVE_CAMERA: " << PerspectiveCamera::getName() << "(" << PerspectiveCamera::getId() << ")" << "]" << endl;
}

CameraType PerspectiveCamera::getType()
{
	return type;
}

bool PerspectiveCamera::getIsAvailable()
{
	return isAvailable;
}

glm::vec3 PerspectiveCamera::getEye() const
{
	return eye;
}

void PerspectiveCamera::setEye(glm::vec3 eye)
{
	this->eye = eye;
}

glm::vec3 PerspectiveCamera::getCenter() const
{
	return center;
}

void PerspectiveCamera::setCenter(glm::vec3 center)
{
	this->center = center;
}

float PerspectiveCamera::getAspect() const
{
	return aspect;
}

void PerspectiveCamera::updateMatrix()
{
	setMatrix(glm::lookAt(eye, center, up));
}

void PerspectiveCamera::setProjection(float aspect)
{
	this->aspect = aspect;
	projection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}
