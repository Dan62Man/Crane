#include "Node.h"

ENGINE_API Node::Node(string name, glm::mat4 matrix, Node* parent) : Object(name)
{
	this->matrix = matrix;
	if (parent != nullptr)
		parent->attachChild(this);
}

ENGINE_API Node::~Node() {
	cout << "[Destroyed OBJECT: " << Node::getName() << "(" << Node::getId() << ")" << "]" << endl;
}

int Node::getId() const
{
	return Object::getId();
}

string Node::getName() const
{
	return Object::getName();
}

vector<Node*> Node::getChildren() const
{
	return children;
}

int Node::getNumberOfChildren() const
{
	return children.size();
}


glm::mat4 Node::getMatrix()
{
	return matrix;
}

void Node::setMatrix(glm::mat4 matrix)
{
	this->matrix = matrix;
}

void Node::attachChild(Node* child)
{
	if (child != nullptr)
	{
		for (auto it = children.begin(); it != children.end(); ++it) {
			if ((*it)->getId() == child->getId())
				return;
		}
		child->setParent(this);
		children.push_back(child);
	}
}

void Node::detachChild(Node* child)
{
	if (child != nullptr) 
	{
		for (auto it = children.begin(); it != children.end(); ++it) {
			if ((*it)->getId() == child->getId()) {
				(*it)->parent = nullptr;
				it = children.erase(it);
				break;
			}
		}
	}
}

glm::mat4 Node::getWorldMatrix() const
{
	if (parent == nullptr) {
		return this->matrix;
	}
	return parent->getWorldMatrix() * matrix;
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}

Node* Node::getParent()
{
	return parent;
}

void Node::render(glm::mat4 camera, glm::mat4 finalMatrix) { }
