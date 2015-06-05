#pragma once
#include "Dependencies/glew/glew.h"
class Model
{
private: 
	char* filetobuf(char *file);

	unsigned int triangleVBO;
	unsigned int indexVBO;
	/* ��� ��� ��������� ������� */
	GLuint shaderProgram;

	/* ��� ��������� ����� �������� ������ � ������ �������� ����� ������� */
	GLchar *vertexSource, *fragmentSource;
	/* ��� ���������� ������������ ��� �������� */
	GLuint vertexShader, fragmentShader;
	const unsigned int shaderAttribute = 0;

	const float NUM_OF_VERTICES_IN_DATA = 3;

	/* ������� ������������ (����������� ������: ������ ������� �������) */
	float data[3][3];
public:
	Model();
	~Model();
	float* Model::calculateNormal(float* coord1, float* coord2, float* coord3);
	int Model::Load(char *filename);	// Loads the model
	void Model::Draw();					// Draws the model on the screen
	void Model::Release();				// Release the model

	float* normals;							// Stores the normals
	float* Faces_Triangles;					// Stores the triangles
	float* vertexBuffer;					// Stores the points which make the object
	long TotalConnectedPoints;				// Stores the total number of connected verteces
	long TotalConnectedTriangles;			// Stores the total number of connected triangles

};

