#include "ModelViewScreen.h"
#include <models\Cube.h>
#include <models\House.h>
#include <iostream>
#include <math.h>
#include <tga\tga.h>

/*
float PlaneDistance(CVector3 a, CVector3 b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z)); 
}

float Normal(CVector3 vPolygon[])
{
	CVector3 vVector1 = vPolygon[2] - vPolygon[0];
	CVector3 vVector2 = vPolygon[1] - vPolygon[0];
	CVector3 vNormal = Cross(vVector1, vVector2);
	vNormal = Normalize(vNormal);
	return vNormal;
}

bool IntersectedPlane(CVector3 vPoly[], CVector3 vLine[],
	CVector3 &vNormal, float &originDistance)
{
	float distance1 = 0, distance2 = 0;                  vNormal = Normal(vPoly);
	originDistance = PlaneDistance(vNormal, vPoly[0]);

	distance1 = ((vNormal.x * vLine[0].x) + (vNormal.y * vLine[0].y) +
		(vNormal.z * vLine[0].z)) + originDistance;
	distance2 = ((vNormal.x * vLine[1].x) + (vNormal.y * vLine[1].y) +
		(vNormal.z * vLine[1].z)) + originDistance;

	if (distance1 * distance2 >= 0) return false;
	return true;
}

*/

void drawSelected(CVector3 intersection) {

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	int x = (int)(intersection.x);
	int z = (int)(intersection.z);
	float y = -0.4f;

	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 1.0f);
	glVertex3f(x + 1.0f, y, z + 1.0f);
	glVertex3f(x + 1.0f, y, z);
	glEnd();
}

void checkSelected() {

}


ModelViewScreen::ModelViewScreen(int argc, char **argv) : gui::Screen(argc, argv)
{

	ObjModelReader modelReader;
	modelReader.load("resources/models/cube.obj");

	this->cube = new Model(modelReader);
	this->cube->init();

	this->model = new House();
	this->model->init();


// 	this->terrain = new Terrain();
// 	this->terrain->init();
	
	this->camera.init(
		0, 5, 10, 
		0, 0, 0, 
		0, 1, 0);
}

ModelViewScreen::~ModelViewScreen()
{
}



void ModelViewScreen::init(void){

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

void drawGround2() {
	

	GLfloat fExtent = 50.f;
	GLfloat fStep = 1.0f;
	GLfloat y = -0.4f;
	GLfloat iLine;

	glBegin(GL_LINES);
	for (iLine = -fExtent; iLine <= fExtent; iLine += fStep) {
		if (iLine < 0)
			glColor3f(1.0f, 0.0f, 0.0f);
		else
			glColor3f(0.0f, 1.0f, 0.0f);

		glVertex3f(iLine, y, fExtent);
		glVertex3f(iLine, y, -fExtent);
		glVertex3f(fExtent, y, iLine);
		glVertex3f(-fExtent, y, iLine);
	}
	glEnd();
}
void ModelViewScreen::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera.applyView();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	
	this->model->Draw();
		
	glPopMatrix();
	this->cube->Draw();
	 drawGround2();
	glBegin(GL_LINE_STRIP);
	glVertex3f(unprojectedVectorFar.x, unprojectedVectorFar.y, unprojectedVectorFar.z);
	glVertex3f(unprojectedVectorNear.x, unprojectedVectorNear.y, unprojectedVectorNear.z);
	glEnd();
	drawSelected(this->lastIntersect);
	glutSwapBuffers();

}

void ModelViewScreen::reshapeScene(int width, int height) {
	std::cout << "reshapeScene...";
	
	Screen::reshapeScene(width, height);
}

void ModelViewScreen::keyboardAction(unsigned char key, int x, int y) {
	
	std::cout << "Pressed:" << key << "[" << x << "," << y << "]\n";
	switch (key) {
	case 'a': case 'A': //toggle screenmode
		camera.moveLeft();
		break;
	case 's': case 'S': camera.moveBack(); break;
	case 'w': case 'W': camera.moveForward(); break;
	case 'd': case 'D': camera.moveRight(); break;
	case 'q': case 'Q': 
		this->model->rotate(-90);
		break;
	case 'e': case 'E': 
		
		this->model->rotate(+90);
		break;
	default:
		Screen::keyboardAction(key, x, y);
	}
}

void ModelViewScreen::mouseClick(int button, int state, int x, int y) {

	std::cout << "[" << button << ":" << state << "]\n";
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		unProjectMouse(x, y);
	} else if (button == 3 && state == GLUT_DOWN) {
		this->camera.moveUp();
	} else if (button == 4 && state == GLUT_DOWN) {
		this->camera.moveDown();
	} else {
		Screen::mouseClick(button, state, x, y);
	}
}

void ModelViewScreen::unProjectMouse(int x, int y) {
	// mouse_x, mouse_y  - оконные координаты курсора мыши.
	// p1, p2            - возвращаемые параметры - концы селектирующего отрезка,
	//                     лежащие соответственно на ближней и дальней плоскостях
	//                     отсечения.
	GLint    viewport[4];    // параметры viewport-a.
	GLdouble projection[16]; // матрица проекции.
	GLdouble modelview[16];  // видовая матрица.
	GLdouble vx, vy, vz;       // координаты курсора мыши в системе координат viewport-a.
	GLdouble wx, wy, wz;       // возвращаемые мировые координаты.

	glGetIntegerv(GL_VIEWPORT, viewport);           // узнаём параметры viewport-a.
	glGetDoublev(GL_PROJECTION_MATRIX, projection); // узнаём матрицу проекции.
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);   // узнаём видовую матрицу.
	// переводим оконные координаты курсора в систему координат viewport-a.
	vx = x;
	vy = this->height - y - 1; // где height - текущая высота окна.

	// вычисляем ближний конец селектирующего отрезка.
	vz = -1;
	gluUnProject(vx, vy, vz, modelview, projection, viewport, &wx, &wy, &wz);

	//p1 = CVector3(wx,wy,wz);
	unprojectedVectorNear.x = wx;
	unprojectedVectorNear.y = wy;
	unprojectedVectorNear.z = wz;
	// вычисляем дальний конец селектирующего отрезка.
	vz = 1;
	gluUnProject(vx, vy, vz, modelview, projection, viewport, &wx, &wy, &wz);

	//p2 = CVector3(wx,wy,wz);
	unprojectedVectorFar.x = wx;
	unprojectedVectorFar.y = wy;
	unprojectedVectorFar.z = wz;
	
	terrain->intersect(unprojectedVectorNear, unprojectedVectorFar, &lastIntersect);

	this->model->translate(lastIntersect);
	checkSelected();
}
