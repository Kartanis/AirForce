#include <models/Model.h>

#include <definitions.h>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include <sstream>
#include <cmath>
#include <tga/tga.h>

#define KEY_ESCAPE 27

#define TOTAL_FLOATS_IN_TRIANGLE 9

using namespace std;


GLuint LoadGLTexture(void)
{
	TGA *tga;
	TGAData *data;

	data = (TGAData*)malloc(sizeof(TGAData));
	if (!data) {
		TGA_ERROR((TGA*)NULL, TGA_OOM);
		return 0;
	}

	printf("[open] name=%s, mode=%s\n", "resources/textures/background.tga", "r");
	tga = TGAOpen("resources/textures/background.tga", "r");
	if (!tga || tga->last != TGA_OK) {
		TGA_ERROR(tga, TGA_OPEN_FAIL);
		return 0;
	}

	printf("[read] image\n");
	data->flags = TGA_IMAGE_INFO | TGA_IMAGE_DATA;;
	if (TGAReadImage(tga, data) != TGA_OK) {
		TGA_ERROR(tga, TGA_READ_FAIL);
		return 0;
	}

	if (data->flags & TGA_IMAGE_INFO) {
		printf("[info] width=%i\n", tga->hdr.width);
		printf("[info] height=%i\n", tga->hdr.height);

		printf("[info] color map type=%i\n", tga->hdr.map_t);

		printf("[info] image type=%i\n", tga->hdr.img_t);

		printf("[info] depth=%i\n", tga->hdr.depth);
		printf("[info] x=%i\n", tga->hdr.x);
		printf("[info] y=%i\n", tga->hdr.y);
		printf("[info] orientation=%s-%s\n",
			(tga->hdr.vert == TGA_BOTTOM) ?
			"bottom" : "top",
			(tga->hdr.horz == TGA_LEFT) ?
			"left" : "right");
	}

	std::cout << "------------------------------------Loading texture 0 -------------------------------------\n";
	GLuint textureID;
	glGenTextures(1, &textureID);

	// ������� ��������� �������� �������, ����� ������� ��� ��������� ������� ����� �������� ������ � ���� ���������
	glBindTexture(GL_TEXTURE_2D, textureID);

	// ��������� ����������� OpenGL
	std::cout << "------------------------------------Loading texture 1 -------------------------------------\n";
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tga->hdr.width, tga->hdr.height, 0, GL_BGR, GL_UNSIGNED_BYTE, data->img_data);
	std::cout << "------------------------------------Loading texture 2 -------------------------------------\n";

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	std::cout << "------------------------------------Loading texture 3 -------------------------------------\n";

	printf("[close]\n");
	TGAClose(tga);
	printf("[exit] main\n");

	return textureID;
}

Model::~Model()
{ 
	glDeleteBuffers(1, &this->indexVBO);
	glDeleteBuffers(1, &this->triangleVBO);
	delete data;
	delete indices;
}

Model::Model(ObjModelReader reader) {
	//Model::Model();
	cout << "Model from reader called.." << "\n";

	this->TotalConnectedTriangles = 0;
	this->TotalConnectedPoints = 0;

	this->rotDegree = 0;
	this->pos.x = 0.0f;
	this->pos.y = 0.0f;
	this->pos.z = 0.0f;

	this->rot.x = 0.0f;
	this->rot.y = 0.0f;
	this->rot.z = 0.0f;
	
	this->verticesNumber = reader.getVertices().size();
	this->indicesNumber = reader.getFaces().size();
	cout << "Model from reader called..2.1" << "\n";
	cout << "vertNum: " << reader.getVertices().size() << "\n";
	cout << "faceNum:" << reader.getFaces().size() << "\n";
	cout << "verticesNumber:" << verticesNumber << "\n";
	cout << "indicesNumber:" << indicesNumber << "\n";

	this->data = new float[verticesNumber * Model::POINTS_PER_VERTEX];
	this->indices = new unsigned int[indicesNumber];
	cout << "Model from reader called..2" << "\n";

	for (int i = 0; i < verticesNumber; i++) {
		cout << i << ". " << reader.getVertices()[i]; 
		if((i+1)%3 == 0)
			cout<< "\n";
		data[i * Model::POINTS_PER_VERTEX] = reader.getVertices()[i].x;
		data[i * Model::POINTS_PER_VERTEX + 1] = reader.getVertices()[i].y;
		data[i * Model::POINTS_PER_VERTEX + 2] = reader.getVertices()[i].z;
	}

	cout << "Model from reader called..3" << "\n";
	for (int i = 0; i < indicesNumber; i++) {
		indices[i] = (unsigned int)reader.getFaces()[i].x - 1;

		cout << " " << indices[i];
		if ((i + 1) % 3 == 0)
			cout << "\n";
	}

	cout << "Model from reader called..4" << "\n";
	// this->textureId = LoadGLTexture();
	
}

Model::Model()
{
	cout << "Model called.." << "\n";
	this->TotalConnectedTriangles = 0;
	this->TotalConnectedPoints = 0;

	this->rotDegree = 0;
	this->pos.x = 0.0f;
	this->pos.y = 0.0f;
	this->pos.z = 0.0f;

	this->rot.x = 0.0f;
	this->rot.y = 0.0f;
	this->rot.z = 0.0f;
}

void Model::init() {

	cout << "Model init called..";
	/*---------------------- ������������� VBO - (�������� ��������, ��� ������� ���������) ---------------------*/
	/* �������� ����� VBO � ������������� ���������� "triangleVBO" ��� ���������� VBO id */
	glGenBuffers(1, &this->triangleVBO);
	glGenBuffers(1, &this->indexVBO);

	cout << "triangleVBO::" + this->triangleVBO<<"\n";
	cout << "indexVBO::" + this->indexVBO << "\n";
	
	//cout << "triangleVBO" << this->triangleVBO<<"\n";
	//exit(0);
	//cout << "indexVBO" << this->indexVBO << "\n";

	//cout << "VerticesNumber : " << this->verticesNumber << "\n";
	//cout << "POINTS_PER_VERTEX : " << POINTS_PER_VERTEX << "\n";
	
	cout << "indicesNumber : " << indicesNumber << "\n";

	cout << "triangleVBO:" << triangleVBO << "\n";
	cout << "indexVBO:" << indexVBO << "\n";


	cout << "triangleVBO::" << this->triangleVBO << "\n";
	cout << "indexVBO::" << this->indexVBO << "\n";
	
	/* ������ ����� VBO �������� */
	glBindBuffer(GL_ARRAY_BUFFER, this->triangleVBO);
	/* ��������� ������ � ��������������� */
	cout << "glBindBuffer::" << "1\n";
	glBufferData(GL_ARRAY_BUFFER, this->verticesNumber * POINTS_PER_VERTEX * sizeof(float), this->data, GL_STATIC_DRAW);
	cout << "glBufferData::" << "\n";
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	cout << "glBindBuffer::" << "0\n";
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesNumber * sizeof(unsigned int), this->indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	/* ��������� ��� ���� ������ ��������� � ������� ���������, ������ 0 (shaderAttribute), � �������� POINTS_PER_VERTEX ����� � ��������� ������ �� ������� */
	glVertexAttribPointer(this->triangleVBO, POINTS_PER_VERTEX, GL_FLOAT, GL_FALSE, 0, 0);

	/* �������� ������ ���������, ������ 0 (shaderAttribute), ��� ������������ */
	glEnableVertexAttribArray(this->shaderAttribute);

	/* ������ ����� VBO �������� */
	//glBindBuffer(GL_ARRAY_BUFFER, this->triangleVBO);

	/*--------------------- �������� Vertex � Fragment �� ������ � �� ���������� --------------------*/
	/* ������ ��� �������� � ��������������� ���������� ����������� ������ */
	this->vertexSource = filetobuf("exampleVertexShader.vert");
	this->fragmentSource = filetobuf("exampleFragmentShader.frag");

	/* ��������� ����� ������������ "�����" ��� ����� �������� ������� */
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	/* ���������� ������ �������� ����� �������� � ���������������� ������������� */
	glShaderSource(this->vertexShader, 1, (const GLchar**)&this->vertexSource, 0);
	glShaderSource(this->fragmentShader, 1, (const GLchar**)&this->fragmentSource, 0);

	/* ����������� ����� ���������� ������ */
	free(this->vertexSource);
	free(this->fragmentSource);

	/* ����������� ���� ���� �������� */
	glCompileShader(this->vertexShader);
	glCompileShader(this->fragmentShader);

	/*-------------------- �������� ��������� �������, ������������� ������� � ��� � �������� ---------------------*/
	/* �������� ����� ��������� ����������� ��� */
	this->shaderProgram = glCreateProgram();

	/* ������������ ���� ������� � ��������� ������� */
	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragmentShader);

	/* ��������� ������ ��������, ������ 0, (shaderAttribute) � in_Position*/
	/* "in_Position" ����� ������������ ������ ������ � ��������� �������*/
	glBindAttribLocation(this->shaderProgram, this->shaderAttribute, "in_Position");

	/* ������� ��������� ������� */
	glLinkProgram(this->shaderProgram);

	/* ��������� ����� ��������� ������� �������� */
	glUseProgram(shaderProgram);


	this->inited = true;
}

float* Model::calculateNormal(float *coord1, float *coord2, float *coord3)
{
	/* calculate Vector1 and Vector2 */
	float va[3], vb[3], vr[3], val;
	va[0] = coord1[0] - coord2[0];
	va[1] = coord1[1] - coord2[1];
	va[2] = coord1[2] - coord2[2];

	vb[0] = coord1[0] - coord3[0];
	vb[1] = coord1[1] - coord3[1];
	vb[2] = coord1[2] - coord3[2];

	/* cross product */
	vr[0] = va[1] * vb[2] - vb[1] * va[2];
	vr[1] = vb[0] * va[2] - va[0] * vb[2];
	vr[2] = va[0] * vb[1] - vb[0] * va[1];

	/* normalization factor */
	val = sqrt(vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);

	float norm[3];
	norm[0] = vr[0] / val;
	norm[1] = vr[1] / val;
	norm[2] = vr[2] / val;


	return norm;
}


int Model::Load(char* filename)
{
	string line;
	ifstream objFile(filename);
	if (objFile.is_open())													// If obj file is open, continue
	{
		objFile.seekg(0, ios::end);										// Go to end of the file, 
		long fileSize = objFile.tellg();									// get file size
		objFile.seekg(0, ios::beg);										// we'll use this to register memory for our 3d model

		vertexBuffer = (float*)malloc(fileSize);							// Allocate memory for the verteces
		Faces_Triangles = (float*)malloc(fileSize*sizeof(float));			// Allocate memory for the triangles
		normals = (float*)malloc(fileSize*sizeof(float));					// Allocate memory for the normals

		int triangle_index = 0;												// Set triangle index to zero
		int normal_index = 0;												// Set normal index to zero

		while (!objFile.eof())											// Start reading file data
		{
			getline(objFile, line);											// Get line from file

			if (line.c_str()[0] == 'v' && line.c_str()[1] != 'n')										// The first character is a v: on this line is a vertex stored.
			{
				line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf

				sscanf(line.c_str(), "%f %f %f ",							// Read floats from the line: v X Y Z
					&vertexBuffer[TotalConnectedPoints],
					&vertexBuffer[TotalConnectedPoints + 1],
					&vertexBuffer[TotalConnectedPoints + 2]);
				//cout << "v " << vertexBuffer[TotalConnectedPoints] << " " << vertexBuffer[TotalConnectedPoints + 1] << " " << vertexBuffer[TotalConnectedPoints + 2] << "\n";

				TotalConnectedPoints += POINTS_PER_VERTEX;					// Add 3 to the total connected points
			}
			if (line.c_str()[0] == 'f')										// The first character is an 'f': on this line is a point stored
			{
				line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf

				int vertexNumber[4] = { 0, 0, 0 };
				sscanf(line.c_str(), "%i%i%i",								// Read integers from the line:  f 1 2 3
					&vertexNumber[0],										// First point of our triangle. This is an 
					&vertexNumber[1],										// pointer to our vertexBuffer list
					&vertexNumber[2]);										// each point represents an X,Y,Z.

				vertexNumber[0] -= 1;										// OBJ file starts counting from 1
				vertexNumber[1] -= 1;										// OBJ file starts counting from 1
				vertexNumber[2] -= 1;										// OBJ file starts counting from 1


				/********************************************************************
				* Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z).
				* The vertexBuffer contains all verteces
				* The triangles will be created using the verteces we read previously
				*/

				int tCounter = 0;
				for (int i = 0; i < POINTS_PER_VERTEX; i++)
				{
					Faces_Triangles[triangle_index + tCounter] = vertexBuffer[3 * vertexNumber[i]];
					Faces_Triangles[triangle_index + tCounter + 1] = vertexBuffer[3 * vertexNumber[i] + 1];
					Faces_Triangles[triangle_index + tCounter + 2] = vertexBuffer[3 * vertexNumber[i] + 2];
					tCounter += POINTS_PER_VERTEX;
				}

				/*********************************************************************
				* Calculate all normals, used for lighting
				*/
				float coord1[3] = { Faces_Triangles[triangle_index], Faces_Triangles[triangle_index + 1], Faces_Triangles[triangle_index + 2] };
				float coord2[3] = { Faces_Triangles[triangle_index + 3], Faces_Triangles[triangle_index + 4], Faces_Triangles[triangle_index + 5] };
				float coord3[3] = { Faces_Triangles[triangle_index + 6], Faces_Triangles[triangle_index + 7], Faces_Triangles[triangle_index + 8] };
				float *norm = this->calculateNormal(coord1, coord2, coord3);

				tCounter = 0;
				for (int i = 0; i < POINTS_PER_VERTEX; i++)
				{
					normals[normal_index + tCounter] = norm[0];
					normals[normal_index + tCounter + 1] = norm[1];
					normals[normal_index + tCounter + 2] = norm[2];
					tCounter += POINTS_PER_VERTEX;
				}

				triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
				normal_index += TOTAL_FLOATS_IN_TRIANGLE;
				TotalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;
			}
		}
		objFile.close();														// Close OBJ file
	}
	else
	{
		cout << "Unable to open file\n";
		cout << strerror(errno)<<"\n";
	}
	cout << "Total points " << TotalConnectedPoints<<"\n";
	cout << "Total triangles " << TotalConnectedTriangles << "\n";
	/*
	for (int i = 0; i < TotalConnectedPoints - 3; i += 3) {
		cout << "v2 " << vertexBuffer[i] << " " << vertexBuffer[i + 1] << " " << vertexBuffer[i + 2] << "\n";
	}*/
	for (int i = 0; i < TotalConnectedPoints - 3; i += 3) {
		cout << "v2 " << Faces_Triangles[i] << " " << Faces_Triangles[i + 1] << " " << Faces_Triangles[i + 2] << "\n";
	}
	return 0;
}

void Model::Release()
{
	free(this->Faces_Triangles);
	free(this->normals);
	free(this->vertexBuffer);
}

void Model::drawVertex(unsigned int ind) {
	int pos = ind * Model::POINTS_PER_VERTEX;
	glVertex3f(data[pos], data[pos + 1], data[pos + 2]);
}

void Model::Draw()
{
	glEnable(GL_TEXTURE_2D);
//	You can load different textures and select one at a time just using the glBindTexture function just like in LoadTextureRAW above.


	glBindTexture(GL_TEXTURE_2D, this->backgroundTextureId);

	// cout << "-------------------------------------Start to Draw() ------------------------------------------------\n";
	// Enable to draw Wireframe 
	if (isWireFrame) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(this->pos.x, this->pos.y, this->pos.z);
	//glRotatef(this->rotDegree % 360, 1, 0, 0);
	glRotatef(this->rotDegree % 360, 0, 1, 0);
	//glRotatef(this->rotDegree % 360, 0, 0, 1);

	// glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	int x = (int)(pos.x);
	int z = (int)(pos.z);
	float y = -0.4f;

	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 1.0f);
	glVertex3f(x + 1.0f, y, z + 1.0f);
	glVertex3f(x + 1.0f, y, z);
	glEnd();


	for (int i = 0; i < indicesNumber; i += 3) {
		if (indicesNumber < 1000) {
			cout << "i:" << i << "\t" << "pos:" << indices[i] << "\tx:" << data[indices[i] * 3] << "\ty:" << data[indices[i] * 3 + 1] << "\tz:" << data[indices[i] * 3 + 2] << "\n";
			cout << "i:" << i << "\t" << "pos:" << indices[i+1] << "\tx:" << data[indices[i+1] * 3] << "\ty:" << data[indices[i+1] * 3 + 1] << "\tz:" << data[indices[i+1] * 3 + 2] << "\n";
			cout << "i:" << i << "\t" << "pos:" << indices[i+2] << "\tx:" << data[indices[i+2] * 3] << "\ty:" << data[indices[i+2] * 3 + 1] << "\tz:" << data[indices[i+2] * 3 + 2] << "\n";
		}
		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0f, 0.0f); drawVertex(indices[i]);
		glTexCoord2f(1.0f, 0.0f); drawVertex(indices[i + 1]);
		glTexCoord2f(0.0f, 1.0f); drawVertex(indices[i + 2]);
		
		glEnd();
	}


	glPopMatrix();
	//cout << "-------------------------------------End to Draw() ------------------------------------------------\n";
	
	return;
	if (!inited) {
		cout << "not inited\n";
	}

	cout << "triangleVBO::" << triangleVBO << "\n";
	cout << "indexVBO::" << indexVBO << "\n";

	

	cout << "--------------------------------1-------------------------\n";
	glEnableClientState(GL_VERTEX_ARRAY);
	cout << "--------------------------------2-------------------------\n";
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	// glVertexPointer(3, GL_FLOAT, 30, this->data);
	cout << "--------------------------------3-------------------------\n";
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	cout << "--------------------------------4-------------------------\n";
	glDrawElements(GL_TRIANGLES, indicesNumber, GL_UNSIGNED_INT, (void*)0);
	cout << "--------------------------------5-------------------------\n";
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	cout << "--------------------------------6-------------------------\n";
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	cout << "--------------------------------7-------------------------\n";

}

/*       Function will read a text file into allocated char buffer       */
char* Model::filetobuf(char *file)
{
	FILE *fptr;
	long length;
	char *buf;

	fptr = fopen(file, "rb"); /* Open file for reading */
	if (!fptr) /* Return NULL on failure */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
	length = ftell(fptr); /* Find out how many bytes into the file we are */
	buf = (char*)malloc(length + 1); /* Allocate a buffer for the entire length of the file and a null terminator */
	fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
	fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
	fclose(fptr); /* Close the file */
	buf[length] = 0; /* Null terminator */

	return buf; /* Return the buffer */
}

void Model::translate(CVector3 pos) {
	this->pos = pos;
}

void Model::rotate(unsigned short rotDegree, CVector3 rot) {
	this->rotDegree = rotDegree;
	this->rot = rot;

	if (this->rotDegree > 360)
		this->rotDegree %= 360;
}


void Model::rotate(unsigned short rotDegree) {
	this->rotDegree += rotDegree;
	if (this->rotDegree < 0 || 360 < this->rotDegree)
		this->rotDegree %= 360;
}


void Model::loadTexture() {
	this->backgroundTextureId = 0;
}