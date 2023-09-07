#include "Mesh.h"
#include <GL/freeglut.h>

Mesh::Mesh(string name, glm::mat4 matrix, Material* material) : Node(name, matrix)
{
	this->material = material;
	this->shadow = new Shadow(name + "_shadow", matrix);
}

Mesh::~Mesh()
{
	cout << "[Destroyed MESH: " << Mesh::getName() << "(" << Mesh::getId() << ")" << "]" << endl;
}

Material* Mesh::getMaterial() const
{
	return material;
}

void Mesh::addVertex(Vertex* vertex)
{
	vertices.push_back(vertex);
}

void Mesh::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
	if (material != nullptr)
		material->render(camera, finalMatrix);
	else
		glDisable(GL_TEXTURE_2D);

	// object
	glLoadMatrixf(glm::value_ptr(camera * finalMatrix));
	loadTriangles();

	// shadow
	shadow->update(vertices, finalMatrix);
	if (m_hasShadow) {
		shadow->render(camera, finalMatrix);
	};
}

void Mesh::setHasShadow(bool hasShadow)
{
	if (m_hasShadow != hasShadow) {
		m_hasShadow = hasShadow;
		for (Node* child : getChildren()) {
			if (Mesh* meshChild = dynamic_cast<Mesh*>(child)) {
				meshChild->setHasShadow(hasShadow);
			}
		}
	}
}

bool Mesh::getHasShadow() {
	return m_hasShadow;
}

void Mesh::loadTriangles()
{
	glBegin(GL_TRIANGLES);
	for (Vertex* vertex : vertices) {
		glm::vec3 normal = vertex->getNormalVectorCoordinates();
		glNormal3f(normal.x, normal.y, normal.z);

		glm::vec2 texture = vertex->getTextureCoordinates();
		glTexCoord2f(texture.x, texture.y);

		glm::vec3 cord = vertex->getPositionCoordinates();
		glVertex3f(cord.x, cord.y, cord.z);
	}
	glEnd();
}
