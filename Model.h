#pragma once
class Model
{
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

