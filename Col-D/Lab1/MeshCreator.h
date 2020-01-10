#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct VertexMesh
{
public:
	VertexMesh(const glm::vec3& position, const glm::vec2& textureCoordinates) // used to store the position of the texture
	{
		this->position = position;
		this->textureCoordinates = textureCoordinates;
		this->normal = normal;
	}

	glm::vec3* GetPosition() { return &position; } //Getters
	glm::vec2* GetTextureCoordinates() { return &textureCoordinates; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 position;
	glm::vec2 textureCoordinates;
	glm::vec3 normal;
};

struct SphereMesh
{
public:

	SphereMesh() {}

	SphereMesh(glm::vec3& position, float sphereRadius)
	{
		this->position = position;
	}

	glm::vec3 GetPosition() { return position; }
	float GetSphereRadius() { return sphereRadius; }

	void SetPosition(glm::vec3 position)
	{
		this->position = position;
	}

	void SetSphereRadius(float radius)
	{
		this->sphereRadius = sphereRadius;
	}

private:
	glm::vec3 position;
	float sphereRadius;
};

class MeshCreator
{
public:
	MeshCreator();
	~MeshCreator();


	void drawMesh();
	void initMesh(VertexMesh* vertices, unsigned int numberOfVertices, unsigned int* indices, unsigned int numberOfIndices);
	void load_Model(const std::string& filename);
	void initialiseModel(const IndexedModel& model);
	void update_SData(glm::vec3 position, float sphereRadius);
	glm::vec3 get_SPosition() { return meshSphere.GetPosition(); }
	float get_SRadius() { return meshSphere.GetSphereRadius(); }

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	SphereMesh meshSphere;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawNum; //how much of the vertexArrayObject do we want to draw
};