#include "View.h"
#include <iostream>

#include "platform_definitions.h"

View::View(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->blinkedTimes = 0;
	this->colorChanged = false;
	this->times = 0;
}


View::~View()
{
}

void View::draw() {
	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, 1.0f);*/
	if (blinkedTimes > 0 && colorChanged) {
		if (times > 0)
			times--;
		else {
			times = 50;
			colorChanged = false;
			glColor3f(0.0f, 1.0f, 0.0f);
		}
	}
	else if (blinkedTimes > 0) {
		if (times > 0)
			times--;
		else {
			times = 50;
			colorChanged = true;
			glColor3f(1.0f, 0.0f, 0.0f);
			blinkedTimes--;
		}
	} else
		glColor3f(0.0f, 1.0f, 0.0f);
	
	// glRectf(x, y, w, h);
	
}

bool View::onMouseAction(MouseEvent* event, MouseEvent::Type type, MouseEvent::Input input){
	/*Checking whether event is for this view*/
	if (x <= event->getX() && event->getX() <= w
		&& y <= event->getY() && event->getY() <= h) {
		//TODO. if yes pass event deeper
		blinkedTimes = 5;
		times = 50;
	}
	std::cout << "Event passed" << event->getX() << ":" << event->getY();

	return false;
}


void View::onScreenSizeChanged(int w, int h) {
	return;
}
