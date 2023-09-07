#pragma once
#include "Node.h"
#include "Vertex.h"
#include <glm/gtc/type_ptr.hpp>

class Shadow : public Node
{
public:	
	Shadow(string name, glm::mat4 matrix);
	~Shadow();

	void update(vector<Vertex*> vertices, glm::mat4 matrix);
	vector<Vertex*> getVertices();
	void render(glm::mat4 camera, glm::mat4 finalMatrix);

private:
	glm::mat4 scaling = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.002f, 1.0f));
	glm::mat4 translate;
	vector<Vertex*> vertices;
};

