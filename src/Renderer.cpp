#include <renderers/Renderer.h>
#include <platform_definitions.h>
#include <iostream>


Renderer::Renderer()
{
	selectedCamera.init(
		5, 15, 10,
		0, 0, 0,
		0, 1, 0);

}


Renderer::~Renderer()
{
}


void Renderer::init() {
	std::cout << "Renderer initialization started...";
	
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION);
	GLfloat aspect = (GLfloat)width / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fieldOfViewAngle, aspect, zNear, zFar);
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

void Renderer::draw() {
	if (!needToReDraw) {
		return;
	}

	clearBuffer(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// init 2D Overlay
	this->draw2DOverlay();

	// init 3D

	this->draw3DScene();
	

	// Change buffers
	glutSwapBuffers();

	// POST display calculation

	needToReDraw = false;
}

void Renderer::invalidate() {
	needToReDraw = true;
}

void Renderer::draw2DOverlay() {
	// save initial state before edit
	saveAndClearMatrix(GL_PROJECTION);
	saveAndClearMatrix(GL_MODELVIEW);
	
	//Disable some 3D states and enable 2D
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	gluOrtho2D(0, width, height, 0);
	glRasterPos2i(0, 0); // center of screen. (-1,0) is center left.

	glColor3f(0.0f, 0.0f, 1.0f);
	// Draw here

	//test triangle
	glBegin(GL_TRIANGLES);
	glVertex2i(0, 0);
	glVertex2i(50, 200);
	glVertex2i(0, 400);
	glEnd();

	// revert to initial state
	revertMatrix(GL_MODELVIEW); 
	revertMatrix(GL_PROJECTION);
}

void Renderer::draw3DScene() {

	// save initial state before edit
	saveAndClearMatrix(GL_PROJECTION);
	GLfloat aspect = (GLfloat)width / height;
	gluPerspective(fieldOfViewAngle, aspect, zNear, zFar);
	saveAndClearMatrix(GL_MODELVIEW);
	selectedCamera.applyView();

	glEnable(GL_DEPTH_TEST); // Turn depth testing back on

	// Draw here

	//test cube
	glColor3f(1.0f, 0.0f, 0.0f);
	// Multi-colored side - FRONT
	glBegin(GL_QUADS);

	glVertex3f(-0.5, -0.5, -1.5);       // P1
	glVertex3f(-0.5, 0.5, -1.5);       // P2
	glVertex3f(0.5, 0.5, -1.5);       // P3
	glVertex3f(0.5, -0.5, -1.5);       // P4

	glEnd();

	// revert to initial state
	revertMatrix(GL_MODELVIEW);
	revertMatrix(GL_PROJECTION);
}

void Renderer::saveAndClearMatrix(int matrix) {
	glMatrixMode(matrix);
	glPushMatrix(); // save 
	glLoadIdentity(); // and clear
}

void Renderer::revertMatrix(int matrix) {
	glMatrixMode(matrix);
	glPopMatrix(); // revert back to the matrix I had before.
}

void Renderer::clearBuffer(int clearFlags) {
	glClear(clearFlags);
}