#include <models\Model.h>

#include "../../Dependencies/glew/glew.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define KEY_ESCAPE 27

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9

using namespace std;

Model::~Model()
{
	glDeleteBuffers(1, &triangleVBO);
	glDeleteBuffers(1, &indexVBO);
}

/*Model::Model(ObjModelReader reader) {

	this->data = new float[reader.getVerticesNumber()];
	this->indices = new unsigned int[reader.getFacesNumber()];
}*/

Model::Model()
{
	cout << "Model called.." << "\n";
	this->TotalConnectedTriangles = 0;
	this->TotalConnectedPoints = 0;

}

void Model::init() {
	cout << "Model init called..";
	/*---------------------- Инициализация VBO - (делается единожды, при запуске программы) ---------------------*/
	/* Создание новго VBO и использование переменной "triangleVBO" для сохранения VBO id */
	glGenBuffers(1, &this->triangleVBO);
	glGenBuffers(1, &this->indexVBO);
	
	//cout << "triangleVBO" << this->triangleVBO<<"\n";
	//exit(0);
	//cout << "indexVBO" << this->indexVBO << "\n";

	//cout << "VerticesNumber : " << this->verticesNumber << "\n";
	//cout << "POINTS_PER_VERTEX : " << POINTS_PER_VERTEX << "\n";
	
	cout << "indicesNumber : " << indicesNumber << "\n";

	cout << "triangleVBO" << triangleVBO << "\n";
	cout << "indexVBO" << indexVBO << "\n";
	
	/* Делаем новый VBO активным */
	glBindBuffer(GL_ARRAY_BUFFER, this->triangleVBO);
	/* Выгружаем данные в видеоустройство */
	glBufferData(GL_ARRAY_BUFFER, this->verticesNumber * POINTS_PER_VERTEX * sizeof(float), this->data, GL_STATIC_DRAW);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexVBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesNumber * sizeof(unsigned int), this->indices, GL_STATIC_DRAW);
	
	/* Указываем что наши данные координат в индексе атрибутов, равный 0 (shaderAttribute), и содержат POINTS_PER_VERTEX числа с плавающей точкой на вершину */
	glVertexAttribPointer(this->shaderAttribute, POINTS_PER_VERTEX, GL_FLOAT, GL_FALSE, 0, 0);

	/* Включаем индекс атрибутов, равный 0 (shaderAttribute), как используемый */
	glEnableVertexAttribArray(this->shaderAttribute);

	/* Делаем новый VBO активным */
	glBindBuffer(GL_ARRAY_BUFFER, this->triangleVBO);

	/*--------------------- Загрузка Vertex и Fragment из файлов и их компиляция --------------------*/
	/* Читаем код шейдеров в соответствующие выделенные динамически буферы */
	this->vertexSource = filetobuf("exampleVertexShader.vert");
	this->fragmentSource = filetobuf("exampleFragmentShader.frag");

	/* Назначаем нашим обработчикам "имена" для новых объектов шейдера */
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	/* Объединяем буферы исходных кодов шейдеров с соответствующими обработчиками */
	glShaderSource(this->vertexShader, 1, (const GLchar**)&this->vertexSource, 0);
	glShaderSource(this->fragmentShader, 1, (const GLchar**)&this->fragmentSource, 0);

	/* Освобождаем ранее выделенную память */
	free(this->vertexSource);
	free(this->fragmentSource);

	/* Компилируем наши коды шейдеров */
	glCompileShader(this->vertexShader);
	glCompileShader(this->fragmentShader);

	/*-------------------- Создание программы шейдера, присоединение шейдера к ней и линковка ---------------------*/
	/* Назначим нашей программе обработчику имя */
	this->shaderProgram = glCreateProgram();

	/* Присоединяем наши шейдеры к программе шейдера */
	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragmentShader);

	/* Связываем индекс атрибута, равный 0, (shaderAttribute) с in_Position*/
	/* "in_Position" будет представлять массив данных в вершинном шейдере*/
	glBindAttribLocation(this->shaderProgram, this->shaderAttribute, "in_Position");

	/* Линкуем программу шейдера */
	glLinkProgram(this->shaderProgram);

	/* Установка нашей программы шейдера активной */
	glUseProgram(shaderProgram);
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

void Model::Draw()
{
	// Enable to draw Wireframe 
	if (isWireFrame) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexVBO);
	glDrawElements(GL_TRIANGLES, this->indicesNumber, GL_UNSIGNED_INT, (void*)0);

	glPopMatrix();
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
