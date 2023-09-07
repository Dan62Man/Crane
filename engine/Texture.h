#pragma once
#include "Object.h"

using namespace std;

class Texture : public Object
{
public:
	Texture(string name);
	~Texture() override;

	void LoadBitmapFromFile();
	void render(glm::mat4 camera, glm::mat4 finalMatrix);

private:
	bool initialized;
	unsigned int texId;
	string path;

	bool ifFileExist(const char* path);
};

