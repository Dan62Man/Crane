#include "Material.h"
#include <GL/freeglut.h>

Material::Material(string name, glm::vec3 emission, glm::vec3 albedo, float roughness, Texture* texture) : Object(name)
{
	this->emission = glm::vec4(emission, 1.0f);
	this->ambient = glm::vec4(albedo * 0.2f, 1.0f);
	this->diffuse = glm::vec4(albedo * 0.6f, 1.0f);
	this->specular = glm::vec4(albedo * 0.4f, 1.0f);
	this->shininess = (1 - sqrt(roughness)) * 128;
	this->texture = texture;
}

Material::~Material()
{
	cout << "[Destroyed MATERIAL: " << Material::getName() << "(" << Material::getId() << ")" << "]" << endl;
}

Texture* Material::getTexture() const
{
	return texture;
}

void Material::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
	if (texture != nullptr)
	{
		glEnable(GL_TEXTURE_2D);
		texture->render(camera, finalMatrix);
	}
	else
		glDisable(GL_TEXTURE_2D);

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
