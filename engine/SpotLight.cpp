#include "SpotLight.h"
#include "GL/freeglut.h"

SpotLight::SpotLight(string name, glm::mat4 matrix, glm::vec3 color, float cutOff, glm::vec3 direction) : Light(name, matrix, color)
{
	this->cutoff = cutOff;
	this->direction = direction;
	this->position = matrix[3];
}

SpotLight::~SpotLight()
{
	cout << "[Destroyed SPOT_LIGHT: " << SpotLight::getName() << "(" << SpotLight::getId() << ")" << "]" << endl;
}

void SpotLight::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
	if (!isAvailable) return;
	Light::render(camera, finalMatrix);
	glLightfv(GL_LIGHT0 + idLight, GL_POSITION, glm::value_ptr(position));
	glLightfv(GL_LIGHT0 + idLight, GL_SPOT_CUTOFF, &cutoff);
	glLightfv(GL_LIGHT0 + idLight, GL_SPOT_DIRECTION, glm::value_ptr(direction));
}