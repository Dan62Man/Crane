#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(string name, glm::mat4 matrix, glm::vec3 color);
	~DirectionalLight() override;

	void render(glm::mat4 camera, glm::mat4 finalMatrix) override;

private:
	glm::vec4 position;
};

