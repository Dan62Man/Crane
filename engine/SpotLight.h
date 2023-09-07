#pragma once
#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight(string name, glm::mat4 matrix, glm::vec3 color, float cutOff, glm::vec3 direction);
	~SpotLight() override;

	void render(glm::mat4 camera, glm::mat4 finalMatrix) override;

private:
	float cutoff;
	glm::vec3 direction;
	glm::vec4 position;
};