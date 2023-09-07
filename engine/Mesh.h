#pragma once
#include "Node.h"
#include "Vertex.h"
#include "Material.h"
#include "Shadow.h"
#include <glm/gtc/type_ptr.hpp>

class Mesh : public Node
{
public:
	Mesh(string name, glm::mat4 matrix, Material* material);
	~Mesh() override;

	Material* getMaterial() const;
	void addVertex(Vertex* vertex);
	void render(glm::mat4 camera, glm::mat4 finalMatrix) override;
	void setHasShadow(bool hasShadow);
	bool getHasShadow();
	
private:
	vector<Vertex*> vertices;
	Material* material;
	Shadow* shadow;
	bool m_hasShadow;

	void loadTriangles();
};

