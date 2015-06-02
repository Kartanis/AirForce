#include "Mark.h"

#include "../../../Dependencies/glew/glew.h"
#include "../../../Dependencies/freeglut/freeglut.h"

#include <cmath>


#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

Mark::Mark()
{
	this->x = 0;
	this->y = 0;
}

void Mark::setPositionDirection(int x, int y, int angle)
{
    this->x = x;
    this->y = y;
    this->angle = angle;

}

void Mark::display()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    float xCenter = this->x;
    float yCenter = this->y;
    glBegin(GL_LINE_LOOP);
    for(int i =0; i <= 300; i++)
    {
		double angle = 2 * PI * i / 300;
        double x = cos(angle);
        double y = sin(angle);
        glVertex2d(xCenter + x, yCenter + y);
    }
    glEnd();

}
