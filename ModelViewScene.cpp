#include "ModelViewScene.h"
#include <iostream>

ModelViewScene::ModelViewScene(int argc, char **argv) : gui::Screen(argc, argv)
{
	this->model = model;
	model.Load("cube.obj");
}


ModelViewScene::~ModelViewScene()
{
}


void ModelViewScene::init(void){

	std::cout << "init...";
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, this->width, this->height);
	GLfloat aspect = (GLfloat)this->width / this->height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->fieldOfViewAngle, aspect, this->zNear, this->zFar);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void ModelViewScene::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 1, 20, 0, 0, 0, 0, 1, 0);
	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	//	g_rotation++;
	glutSolidSphere(5, 15, 15);
	glColor3f(1.0f, 1.0f, 0.0f);
	model.Draw();
	glPopMatrix();
	glutSwapBuffers();
}

void ModelViewScene::reshapeScene(int width, int height) {
	std::cout << "reshapeScene...";
}