#include "List.h"

ENGINE_API List::List(string name) : Object(name) { }

ENGINE_API List::~List()
{ 
	cout << "[Destroyed LIST: " << List::getName() << "(" << List::getId() << ")" << "]" << endl;
}

map<Node*, glm::mat4> List::getList()
{
	return list;
}

void List::add(Node* node, glm::mat4 finalMatrix)
{
	glm::mat4 newFinalMatrix = finalMatrix * node->getMatrix();
	list[node] = newFinalMatrix;

	vector<Node*> children = node->getChildren();
	if (children.size() != 0) {
		for (Node* child : children) {
			add(child, newFinalMatrix);
		}
	}
}

Node ENGINE_API* List::findByName(string name)
{
	for (auto it = list.begin(); it != list.end(); ++it) 
	{ 
		if (it->first->getName() == name) 
		{ 
			return it->first; 
		} 
	} 
	return nullptr;
}

void List::render(glm::mat4 camera, glm::mat4 finalMatrix)
{
	if (list.size() == 0) return;

	for (const auto &node : list) {
		node.first->render(camera, node.first->getWorldMatrix());
	}
}



