#include "Cube.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "../../Dependencies/glew/glew.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define TOTAL_FLOATS_IN_TRIANGLE 9
using namespace std;


Cube::~Cube()
{
	delete this->data;
	delete this->indices;
}


Cube::Cube()
{
	cout << "Cube called..";
	this->TotalConnectedTriangles = 0;
	this->TotalConnectedPoints = 0;
	this->verticesNumber = 8;
	this->indicesNumber = 36;

	data = new float[verticesNumber * Model::POINTS_PER_VERTEX]();

	data[0] = 1.0f;
	data[1] = -1.0f;
	data[2] = -1.0f;

	data[3] = 1.0f;
	data[4] = -1.0f;
	data[5] = 1.0f;
	//([\d\.-]+) 
	data[6] = -1.0f;
	data[7] = -1.0f;
	data[8] = 1.0f;


	data[9] = -1.0f;
	data[10] = -1.0f;
	data[11] = -1.0f;

	data[12] = 1.0f;
	data[13] = 1.0f;
	data[14] = -1.0f;

	data[15] = 1.0f;
	data[16] = 1.0f;
	data[17] = 1.0f;

	data[18] = -1.0f;
	data[19] = 1.0f;
	data[20] = 1.0f;

	data[21] = -1.0f;
	data[22] = 1.0f;
	data[23] = -1.0f;

	indices = new unsigned int[36]
	{
		2, 3, 4,
			8, 7, 6,
			5, 6, 2,
			6, 7, 3,
			3, 7, 8,
			1, 4, 8,
			1, 2, 4,
			5, 8, 6,
			1, 5, 2,
			2, 6, 3,
			4, 3, 8,
			5, 1, 8
	};

	for (int i = 0; i < this->indicesNumber; i++) {
		this->indices[i]--;
	}

}
