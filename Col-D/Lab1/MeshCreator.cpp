#include "MeshCreator.h"
#include <vector>

void MeshCreator::initMesh(VertexMesh* vertices, unsigned int numberOfVertices, unsigned int* indices, unsigned int numberOfIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numberOfVertices; i++)//get the positions of the models
	{
		model.positions.push_back(*vertices[i].GetPosition());
		model.textureCoordinate.push_back(*vertices[i].GetTextureCoordinates());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numberOfIndices; i++)
		model.indices.push_back(indices[i]);

	initialiseModel(model); // initialise the current model
}

void MeshCreator::initialiseModel(const IndexedModel& model)
{

	drawNum = model.indices.size(); // draw the models to the screen

	glGenVertexArrays(1, &vertexArrayObject); //generate a vertex array and store it in the VAO
	glBindVertexArray(vertexArrayObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.textureCoordinate[0]), &model.textureCoordinate[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our VAO
}

MeshCreator::MeshCreator()
{
	drawNum = NULL;
}

void MeshCreator::load_Model(const std::string& filename) // loads the model that was initialised 
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initialiseModel(model);
	SphereMesh meshSphere();
}

MeshCreator::~MeshCreator()
{
	glDeleteVertexArrays(1, &vertexArrayObject); // delete arrays
}

void MeshCreator::drawMesh() // draws the elements of the mesh
{
	glBindVertexArray(vertexArrayObject);

	glDrawElements(GL_TRIANGLES, drawNum, GL_UNSIGNED_INT, 0);
	

	glBindVertexArray(0);
}

void MeshCreator::update_SData(glm::vec3 pos, float radius) // updates the mesh data 
{
	meshSphere.SetPosition(pos);
	meshSphere.SetSphereRadius(radius);
}

