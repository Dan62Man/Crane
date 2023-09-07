#include "Shadow.h"
#include <GL/freeglut.h>

Shadow::Shadow(string name, glm::mat4 matrix) : Node(name, matrix) 
{
	scaling = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.2f, 0.01f));
}

Shadow::~Shadow()
{
	cout << "[Destroyed SHADOW: " << Shadow::getName() << "(" << Shadow::getId() << ")" << "]" << endl;
}

void Shadow::update(vector<Vertex*> vertices, glm::mat4 matrix)
{
	this->vertices = vertices;
	setMatrix(matrix);
}

vector<Vertex*> Shadow::getVertices()
{
	return vertices;
}

void Shadow::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
	glLoadMatrixf(glm::value_ptr(camera * translate * scaling * finalMatrix));
	
	glDisable(GL_LIGHTING);

	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	for (Vertex* vertex : vertices) {
		glm::vec3 cord = vertex->getPositionCoordinates();
		glVertex3f(cord.x, cord.y, cord.z);
	}
	glEnd();
	
	glEnable(GL_LIGHTING);
}
