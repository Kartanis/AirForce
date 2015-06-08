#pragma once
#include "Dependencies/glew/glew.h"
class Model
{
private: 
	
	
public:
	static const int POINTS_PER_VERTEX = 3;

	Model();
	~Model();

	float* Model::calculateNormal(float* coord1, float* coord2, float* coord3);
	int Model::Load(char *filename);	// Loads the model
	virtual void Model::Draw();					// Draws the model on the screen
	void Model::Release();				// Release the model
	void init();
	

protected:
	float* normals;							// Stores the normals
	float* Faces_Triangles;					// Stores the triangles
	float* vertexBuffer;					// Stores the points which make the object
	long TotalConnectedPoints;				// Stores the total number of connected verteces
	long TotalConnectedTriangles;			// Stores the total number of connected triangles
	float *data;
	int verticesNumber = 0;
	unsigned int *indices;
	int indicesNumber = 0;

	unsigned int triangleVBO=0;
	unsigned int indexVBO=0;

	char* filetobuf(char *file);

	/* Это имя программы шейдера */
	GLuint shaderProgram;

	/* Эти указатели будут получать адреса в памяти исходных кодов шейдера */
	GLchar *vertexSource, *fragmentSource;
	/* Эти переменные используются для шейдеров */
	GLuint vertexShader, fragmentShader;
	const unsigned int shaderAttribute = 0;

	const float NUM_OF_VERTICES_IN_DATA = 3;

	/* Вершины треугольника (направление обхода: против часовой стрелки) */
	bool isWireFrame = false;
};

