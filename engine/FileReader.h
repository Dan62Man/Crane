#pragma once
#include "Node.h"
#include "OvType.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "OmniLight.h"
#include "Mesh.h"
#include <iostream>
#include <vector>
#include <map>
#include <glm/gtc/packing.hpp>
#include <cstring>

using namespace std;

class FileReader
{
public:
	FileReader(const char* fileName);
	~FileReader();

	Node* read();

private:
	FILE* file;
	Node* recursiveLoading();
	void recursiveLoadingChildren(Node* parent, int nrOfChildren);
};

