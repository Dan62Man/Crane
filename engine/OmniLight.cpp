#include "OmniLight.h"
#include "GL/freeglut.h"

OmniLight::OmniLight(string name, glm::mat4 matrix, glm::vec3 color, float cutOff) : Light(name, matrix, color)
{
	this->cutOff = cutOff;
}

OmniLight::~OmniLight()
{
	cout << "[Destroyed OMNI_LIGHT: " << OmniLight::getName() << "(" << OmniLight::getId() << ")" << "]" << endl;
}

void OmniLight::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
	if (!isAvailable) return;
	Light::render(camera, finalMatrix);
	glLightfv(GL_LIGHT0 + idLight, GL_SPOT_CUTOFF, &cutOff);
}