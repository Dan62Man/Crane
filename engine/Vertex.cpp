#include "Vertex.h"

Vertex::Vertex(const glm::vec3 positionCoordinates, const glm::vec3 normalVectorCoordinates, const glm::vec2 textureCoordinates)
{
	this->positionCoordinates = positionCoordinates;
	this->normalVectorCoordinates = normalVectorCoordinates;
	this->textureCoordinates = textureCoordinates;
}

Vertex::~Vertex()
{
	cout << "[Destroyed VERTEX]" << endl;
}

const glm::vec3 Vertex::getPositionCoordinates() const
{
	return positionCoordinates;
}

const glm::vec3 Vertex::getNormalVectorCoordinates() const
{
	return normalVectorCoordinates;
}

const glm::vec2 Vertex::getTextureCoordinates() const
{
	return textureCoordinates;
}
