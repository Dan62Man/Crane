#pragma once
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

class Vertex
{
public:
    Vertex(const glm::vec3 positionCoordinates, const glm::vec3 normalVectorCoordinates, const glm::vec2 textureCoordinates);

    ~Vertex();

    const glm::vec3 getPositionCoordinates() const;
    const glm::vec3 getNormalVectorCoordinates() const;
    const glm::vec2 getTextureCoordinates() const;

private:
    glm::vec3 positionCoordinates;
    glm::vec3 normalVectorCoordinates;
    glm::vec2 textureCoordinates;
};

