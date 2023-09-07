#pragma once
#include "LibraryInfo.h"
#include "Object.h"
#include "Node.h"
#include "Light.h"
#include "Mesh.h"
#include <map>


class ENGINE_API List : public Object
{
public:
	List(string name);
	~List();

	map<Node*, glm::mat4> getList();

	void add(Node* node, glm::mat4 finalMatrix);
	Node* findByName(string name);
	void render(glm::mat4 camera, glm::mat4 finalMatrix) override;

private:
	map<Node*, glm::mat4> list;

};

