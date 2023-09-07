#pragma once
#include "Node.h"

class Light : public Node
{
public:
	Light(string name, glm::mat4 matrix, glm::vec3 color);
	~Light() override;
	
	bool getIsAvailable();
	void render(glm::mat4 camera, glm::mat4 finalMatrix) override;

private:
	static int cntLight;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float intensity;

protected:
	int idLight;
	bool isAvailable;
	
};

