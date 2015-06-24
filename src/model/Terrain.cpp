#include "Terrain.h"
#include <iostream>
#include <math/Math.h>


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


void Terrain::intersect(CVector3 near, CVector3 far, CVector3 *res) {
	float t, u, v;
	float orig[3] = { near.x, near.y, near.z };
	float dir[3] = { far.x, far.y, far.z };
	
	float rv1[3] = { -50.0, 0, -50.0 };
	float rv2[3] = { 50.0, 0, -50.0 };
	float rv3[3] = { 50.0, 0, 50.0 };

	float lv1[3] = { -50.0, 0, -50.0 };
	float lv2[3] = { -50.0, 0, 50.0 };
	float lv3[3] = { 50.0, 0, 50.0 };

	int result = Math::intersect_triangle(orig, dir, rv1, rv2, rv3, &t, &u, &v);
	if (result == 0) {
		std::cout << "right not found" << "\n";
		result = Math::intersect_triangle3(orig, dir, lv1, lv2, lv3, &t, &u, &v);
	}
	if (result == 0) {
		return;
	}
	// if (!(Math::intersect_triangle(orig, dir, rv1, rv2, rv3, &t, &u, &v) == 0 || Math::intersect_triangle3(orig, dir, lv1, lv2, lv3, &t, &u, &v) == 0))  {
		// return;
	//} 
	
	std::cout << "Intersection......Start\n";
	std::cout << u << " " << v << " " << t << "\n";
	std::cout << orig[0] << " " << orig[1] << " " << orig[2] << "\n";
	std::cout << dir[0] << " " << dir[1] << " " << dir[2] << "\n";
	std::cout << orig[0] + dir[0] * t << " " << orig[1] + dir[1] * t << " " << orig[2] + dir[2] * t << "\n";
	std::cout << "Intersection......End\n";

	res->x = orig[0] + dir[0] * t;
	res->y = orig[1] + dir[1] * t;
	res->z = orig[2] + dir[2] * t;

};

void Terrain::Draw() {
	// glBegin();
	Model::Draw();

}