#include "BlinkedMark.h"
#include "platform_definitions.h"
#include <math.h>
#include <iostream>


#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

BlinkedMark::BlinkedMark()
{
	this->state = MAX_STATE;
	this->regression = true;
}

void BlinkedMark::display()
{
	// Mark::display();
	drawState();
}

void BlinkedMark::drawState()
{
	if (this->state <= 0) {
		regression = false;
	}
	if (this->state >= MAX_STATE) {
		regression = true;
	}

	glColor3f(1.0f, 0.0f, 0.0f);
	float xCenter = this->x;
	float yCenter = this->y;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 300; i++)
	{
		double angle = 2 * PI * i / 300;
		double x = cos(angle) * state;
		double y = sin(angle) * state;

		glVertex2d(xCenter + x, yCenter + y);
	}
	glEnd();

	changeState();

}

void BlinkedMark::changeState()
{
	if (regression)
		this->state--;
	else
		this->state++;
}