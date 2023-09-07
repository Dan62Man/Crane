#include "Light.h"
#include "GL/freeglut.h"


int Light::cntLight = 0;
Light::Light(string name, glm::mat4 matrix, glm::vec3 color) : Node(name, matrix)
{
	this->idLight = Light::cntLight;
	Light::cntLight++;

	if (Light::cntLight < 9)
	{
		this->intensity = 0.7f;
		this->ambient = glm::vec4(color[0], color[1], color[2], 1.0f);
		this->diffuse = glm::vec4(color[0], color[1], color[2], 1.0f);
		this->specular = glm::vec4(color[0], color[1], color[2], 1.0f);
		isAvailable = true;

		//Enable this light
		glEnable(GL_LIGHT0 + idLight);

		//Allows for the lighting calculation to consider the position of the camera
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
	} 
	else 
	{
		isAvailable = false;
		cout << "Unble to create light number " << cntLight << " (max 8)" << endl;
	}
}

Light::~Light()
{
	cout << "[Destroyed LIGHT: " << Light::getName() << "(" << Light::getId() << ")" << "]" << endl;
}

bool Light::getIsAvailable()
{
	return isAvailable;
}

void Light::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
	glLoadMatrixf(glm::value_ptr(camera * finalMatrix));
	glLightfv(GL_LIGHT0 + idLight, GL_AMBIENT, glm::value_ptr(ambient * intensity));
	glLightfv(GL_LIGHT0 + idLight, GL_DIFFUSE, glm::value_ptr(diffuse * intensity));
	glLightfv(GL_LIGHT0 + idLight, GL_SPECULAR, glm::value_ptr(specular));
}



