#include "Frame.h"
#include <iostream>

Frame::Frame(int width, int height)
{
	this->width = width;
	this->height = height;
}


Frame::~Frame()
{
}

void Frame::draw() {
	glLineWidth(2.5);
	glColor3f(1.0, 1.0, 1.0);

	const float start = -1.0;

	int steps = height / mult;

	// std::cout << steps << ":steps" << "\n";
	for (int i = 0; i < steps; i++) {
		glBegin(GL_LINES);
		int lstart = 0;
		int rend = 0;
		int ustart = 0;
		int bend = 0;


// 		600 / 5 = 120
		// 0 = -1.0
		// 120 = 2 / 5 = 0.4
		// 600 = +1.0

		glVertex3f(0.0f, start + (height / steps) * i, 0.0);
		glVertex3f(width, start + (height / steps) * i, 0.0);
		glEnd();
	}
	

	steps = width / mult;
	for (int i = 0; i < steps; i++) {
		glBegin(GL_LINES);
		int lstart = 0;
		int rend = 0;
		int ustart = 0;
		int bend = 0;


		// 		600 / 5 = 120
		// 0 = -1.0
		// 120 = 2 / 5 = 0.4
		// 600 = +1.0

		glVertex3f(start + (width / steps) * i, 0.0f, 0.0);
		glVertex3f(start + (width / steps) * i, height, 0.0);
		glEnd();
	}
	
}

void Frame::reshape(int w, int h) {
	this->width = width;
	this->height = height;
}
