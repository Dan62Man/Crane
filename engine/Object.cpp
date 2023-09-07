#include "Object.h"

int Object::cntId = 0;

ENGINE_API Object::Object(string name)
{
	cntId++;
	this->id = cntId;
	this->name = name;
}

ENGINE_API Object::~Object() {
	cout << "[Destroyed OBJECT: " << name << "(" << id << ")" << "]" << endl;
}

int Object::getId() const
{
	return id;
}

string Object::getName() const
{
	return name;
}

void Object::setName(string name)
{
	this->name = name;
}

void Object::render(glm::mat4 camera, glm::mat4 finalMatrix) { }
