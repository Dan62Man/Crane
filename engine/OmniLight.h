#pragma once
#include "Light.h"

class OmniLight : public Light
{
public:
	OmniLight(string name, glm::mat4 matrix, glm::vec3 color, float cutOff);
	~OmniLight() override;

	void render(glm::mat4 camera, glm::mat4 finalMatrix) override;

private:
	float cutOff;
};
