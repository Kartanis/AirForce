#include "Terrain.h"
#include <iostream>

Terrain::Terrain()
{
	std::cout << "Terrain called.." << "\n";

	GLfloat fExtent = 50.f;
	GLfloat fStep = 1.0f;
	GLfloat y = -0.4f;
	GLfloat iLine;

	isWireFrame = true;
	this->verticesNumber = ((fExtent * 2 / fStep) + 1) * 4 * Model::POINTS_PER_VERTEX;
	this->indicesNumber = ((fExtent * 2 / fStep) + 1) * 4 * Model::POINTS_PER_VERTEX;

	this->data = new float[(int)((fExtent * 2 / fStep )+ 1) * 4 * Model::POINTS_PER_VERTEX - 1];
	this->indices = new unsigned int[(int)((fExtent * 2 / fStep) + 1) * 4 * Model::POINTS_PER_VERTEX - 1];

	int i = 0;
	int j = 0;
	for (iLine = -fExtent; iLine <= fExtent; iLine += fStep) {
		int startIndex = i;

		data[i++] = iLine;
		data[i++] = y; 
		data[i++] = fExtent;

		data[i++] = iLine;
		data[i++] = y;
		data[i++] = -fExtent;

		data[i++] = fExtent;
		data[i++] = y;
		data[i++] = iLine;

		data[i++] = -fExtent;
		data[i++] = y;
		data[i++] = iLine;
		
		for (int k = 0; k < i - startIndex; k++) {
			this->indices[j++] = startIndex + k;
		}
	}

	std::cout << "data size " << i <<"\n";
	std::cout << "indicies size " << j << "\n";
	std::cout << "expected size " << (int)((fExtent * 2 / fStep) + 1) * 4 * Model::POINTS_PER_VERTEX << "\n";
	

}

Terrain::~Terrain()
{
}

void simpleterrain() {

}

