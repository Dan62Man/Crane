#pragma once
#include "Object.h"
#include "Texture.h"

class Material : public Object
{
public:
	Material(string name, glm::vec3 emission, glm::vec3 albedo, float roughness, Texture* texture);
	~Material() override;

	Texture* getTexture() const;

	void render(glm::mat4 camera, glm::mat4 finalMatrix);

private:
	glm::vec4 emission;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;
	Texture* texture;
};

