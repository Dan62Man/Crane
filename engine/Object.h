#pragma once
#include "LibraryInfo.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class ENGINE_API Object
{
public:
	Object(string name);
	virtual ~Object();

	int getId() const;
	string getName() const;
	void setName(string name);

	virtual void render(glm::mat4 camera, glm::mat4 finalMatrix);

private:
	static int cntId;
	int id;
	string name;
};

