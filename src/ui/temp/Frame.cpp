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

	int steps = this->height / mult;

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

		glVertex3f(0.0f, 0.0f, start + (this->height / steps) * i);
		glVertex3f(this->width, 0.0f, start + (this->height / steps) * i);
		glEnd();
	}

	steps = this->width / mult;
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

		glVertex3f(start + (this->width / steps) * i, 0.0f, 0.0f);
		glVertex3f(start + (this->width / steps) * i, 0.0f, this->height);
		glEnd();
	}
	
}

void Frame::reshape(int w, int h) {
	this->width = w;
	this->height = h;
}
