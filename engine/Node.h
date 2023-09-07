#pragma once
#include "Object.h"
#include <vector>

class ENGINE_API Node : public Object
{
public:
	Node(string name, glm::mat4 matrix = glm::mat4(1.0f), Node* parent = nullptr);
	~Node() override;

	int getId() const;
	string getName() const;
	vector<Node*> getChildren() const;
	int getNumberOfChildren() const;
	glm::mat4 getMatrix();
	void setMatrix(glm::mat4 matrix);
	glm::mat4 getWorldMatrix() const;
	Node* getParent();

	void attachChild(Node* child);
	void detachChild(Node* child);
	void render(glm::mat4 camera, glm::mat4 finalMatrix) override;

private:
	Node* parent;
	vector<Node*> children;
	glm::mat4 matrix;
	int numberOfChildren;

	void setParent(Node* parent);
};


