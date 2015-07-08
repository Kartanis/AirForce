#include "Camera.h"
#include "../../../Dependencies\freeglut\glut.h"

double Camera::matrix[9] = { 0.0, 105.0, -15, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
const double Camera::zoomStep = 1.0;
Camera::Camera()
{
	// this->matrix = new double[]{ 0.0, 45.0, -25, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	zoom = 0;
}


Camera::~Camera()
{
	//delete this->matrix;
}


void Camera::applyView() {
	gluLookAt(matrix[0], matrix[1] + zoom, matrix[2],
		matrix[3], matrix[4], matrix[5], 
		matrix[6], matrix[7], matrix[8]);
}

void Camera::init(int ex, int ey, int ez,
	int cx, int cy, int cz,
	int x, int y, int z) {
	this->matrix[0] = ex;
	this->matrix[1] = ey;
	this->matrix[2] = ez;

	this->matrix[3] = cx;
	this->matrix[4] = cy;
	this->matrix[5] = cz;

	this->matrix[6] = x;
	this->matrix[7] = y;
	this->matrix[8] = z;
}