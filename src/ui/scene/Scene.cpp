#include "Scene.h"
#include "../screens/Screen.h"

#define PI 3.14159265358979323846

using namespace gui;

Scene::Scene(int x, int y, int w, int h) : View(x, y, w, h)
{
	this->frame = new Frame(w-x, h-y);
}


Scene::~Scene()
{
	delete this->frame;
}

void Scene::draw() {

	View::draw();
	frame->draw();


	glRasterPos2i(120, 100);

	char* text = "Some internal test text!";
	// for (int i = 0; i < strlen(text); i++)
		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	/*
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	// glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);*/
	
}

void Scene::reshape(int w, int h) {
	throw;
}
	
void Scene::point(int x, int y){
}

void Scene::onScreenSizeChanged(int w, int h) {
	frame->reshape(w - x, h - y);
	this->w = w;
	this->h = h;
}
