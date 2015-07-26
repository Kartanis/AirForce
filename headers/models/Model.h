#pragma once

#include <definitions.h>
#include <FileSystem/ObjModelReader.h>

class Model
{
private: 
	CVector3 pos;
	CVector3 rot;
	unsigned short rotDegree;

	void drawVertex(unsigned int ind);
	unsigned int textureId = 0;
public:
	static const int POINTS_PER_VERTEX = 3;
	static const int INDICES_PER_TRIANGLE = 3;
	static const int TRINAGLES_PER_QUAD = 2;

	Model();

	Model(ObjModelReader reader);
	~Model();

	float* calculateNormal(float* coord1, float* coord2, float* coord3);
	int Load(char *filename);		// Loads the model
	virtual void Draw();				// Draws the model on the screen
	void Release();					// Release the model
	void init();
	void translate(CVector3);
	void rotate(unsigned short, CVector3);
	void rotate(unsigned short);

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

	unsigned int triangleVBO = 0;
	unsigned int indexVBO = 0;

	char* filetobuf(char *file);
	bool inited = false;

	/* ��� ��� ��������� ������� */
	GLuint shaderProgram;
	/* ��� ��������� ����� �������� ������ � ������ �������� ����� ������� */
	GLchar *vertexSource, *fragmentSource;
	/* ��� ���������� ������������ ��� �������� */
	GLuint vertexShader, fragmentShader;
	const unsigned int shaderAttribute = 0;

	const float NUM_OF_VERTICES_IN_DATA = 3;

	/* ������� ������������ (����������� ������: ������ ������� �������) */
	bool isWireFrame = false;

	unsigned int backgroundTextureId = 0;
	virtual void loadTexture();
};

