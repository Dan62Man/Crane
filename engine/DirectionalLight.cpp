#include "DirectionalLight.h"
#include "GL/freeglut.h"

DirectionalLight::DirectionalLight(string name, glm::mat4 matrix, glm::vec3 color) : Light(name, matrix, color)
{
	this->position = matrix[3];
}

DirectionalLight::~DirectionalLight()
{
	cout << "[Destroyed DIRECTIONAL_LIGHT: " << DirectionalLight::getName() << "(" << DirectionalLight::getId() << ")" << "]" << endl;
}

void DirectionalLight::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
	if (!isAvailable) return;
	Light::render(camera, finalMatrix);
	glLightfv(GL_LIGHT0 + idLight, GL_POSITION, glm::value_ptr(position));
}