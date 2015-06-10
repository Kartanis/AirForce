#include "ModelViewScreen.h"
#include "../../model/Cube.h"
#include "../../model/House.h"
#include <iostream>

int rot = 0;

ModelViewScreen::ModelViewScreen(int argc, char **argv) : gui::Screen(argc, argv)
{
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
	//gluLookAt(0, 5, 10, 0, 0, 0, 0, 1, 0);
	camera.applyView();
	glPushMatrix();
	glRotatef(rot % 360, 0, 1, 0);
	// glRotatef(90, 0, 1, 0);
	//	g_rotation++;
	//glutSolidSphere(5, 15, 15);
	glColor3f(1.0f, 0.0f, 1.0f);
	//glutSolidSphere(1, 15, 15);
	glColor3f(1.0f, 1.0f, 1.0f);
	this->model->Draw();
	//this->terrain->Draw();
	glPopMatrix();
	 drawGround2();
	glBegin(GL_LINE_STRIP);
	glVertex3f(unprojectedVectorFar.x, unprojectedVectorFar.y, unprojectedVectorFar.z);
	glVertex3f(unprojectedVectorNear.x, unprojectedVectorNear.y, unprojectedVectorNear.z);
	glEnd();
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
	case 's': case 'S': camera.moveDown(); break;
	case 'w': case 'W': camera.moveUp(); break;
	case 'd': case 'D': camera.moveRight(); break;
	case 'q': case 'Q': rot -= 15; // camera.moveLeftSide(); 
		break;
	case 'e': case 'E': rot += 15;
		// camera.moveRightSide(); 
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
	}
	else {
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
}

