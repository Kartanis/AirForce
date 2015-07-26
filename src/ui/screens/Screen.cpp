#include "Screen.h"
#include <iostream>
#include "../scene/Scene.h"
#include "../events/MouseEvent.h"
#include "../window/Window.h"

#include "platform_definitions.h"

using namespace gui;

// int Screen::width = 800;
// int Screen::height = 600;

// Scene Screen::scene(Screen::width, Screen::height);
// std::vector <View*> Screen::views;
Camera Screen::camera;


void drawGround() {
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

Screen::Screen(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(this->width, this->height);

	// Screen::addView(new View(0, 0, this->width, 70));
	// Screen::addView(new View(0, 71, 120, this->height));
	// Screen::addView(new Scene(0, 0, this->width, this->height));

	glutCreateWindow("Drawing my first triangle");
	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) {
		std::cout << "Glew init status..." << glewInitStatus << "\n";
		exit(glewInitStatus);
	}

	// register callbacks
	glutDisplayFunc(gui::renderer);
	glutReshapeFunc(gui::reshape);
	glutMouseFunc(gui::mouseClick);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboard);

	// glutMainLoop();
	// glDeleteProgram(program);

}


Screen::~Screen()
{
}

void Screen::renderScene() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float fMoonRot = 0.0f;
	static float fEarthRot = 0.0f;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glTranslatef(0.0f, 0.0f, -0.0f);


	glColor3ub(255, 255, 0);
	// glDisable(GL_LIGHTING);

	glutSolidSphere(15.0f, 15, 15);

	// glEnable(GL_LIGHTING);
	// glLightfv(GL_LIGHT0, GL_POSITION, new float[]{ 105.0f, 0.0f, 0.0f });
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
	glColor3ub(0, 0, 255);
	glTranslatef(15.0f, 0.0f, 0.0f);
	glutSolidSphere(15.0f, 15, 15);

	glColor3ub(200, 200, 200);
	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);

	fMoonRot += 15.0f;
	if (fMoonRot > 360) fMoonRot = 0.0f;

	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();
	fEarthRot += 5.0f;
	if (fEarthRot > 360) fEarthRot = 0.0f;

	drawGround();


	glutSwapBuffers();
	// glutPostRedisplay();
		
}



void Screen::init(void){
	

	/*
	glEnable(GL_DEPTH_TEST);

	//load and compile shaders
	Core::Shader_Loader shaderLoader;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	*/
	 glEnable(GL_DEPTH_TEST);
	 // glOrtho(0.0, this->width, this->height, 0.0, -1, 1);
	
	 std::cout << "inited in base";
}




void  gui::renderer(void) {
	Window &window = Window::getInstance();
	if (window.isScreenAppended()) {
		window.getScreen()->renderScene();
	}
	else {
	}
	
	
}

void gui::reshape(int width, int height)
{
	Window &window = Window::getInstance();
	if (window.isScreenAppended()) {
		window.getScreen()->reshapeScene(width, height);
	}
	else {
	}
}

void gui::mouseClick(int button, int state, int x, int y)
{
	Window &window = Window::getInstance();
	if (window.isScreenAppended()) {
		window.getScreen()->mouseClick(button, state, x, y);
	}
	else {
		return;
	}
	
}

void gui::idleFunc()
{
	glutPostRedisplay();
}

void gui::keyboard(unsigned char key, int x, int y) {
	Window &window = Window::getInstance();
	if (window.isScreenAppended()) {
		window.getScreen()->keyboardAction(key, x, y);
	}
	else {
		return;
	}
}


bool Screen::mouseAction(MouseEvent *event, MouseEvent::Type type, MouseEvent::Input input) {
	/*for (std::vector<View*>::iterator v = Screen::views.begin(); v != Screen::views.end(); ++v) {
		if ((*v)->onMouseAction(event, type, input))
			return true;
	}*/
	return false;
}

void Screen::reshapeScene(int width, int height) {
	std::cout << "reshape in base...";
	
	if (height == 0)
		height = 1;
	float aspectRatio = (float)width / height;

	this->width = width;
	this->height = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	std::cout << aspectRatio;
	gluPerspective(60.0, aspectRatio, 1.0, 425.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Screen::camera.applyView();

	/*std::cout << "x:" << width << "h:" << height << "\n";
	float aspectRatio;
	if (height == 0)
	height == 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = width / height;
	if (width < height) {
	glOrtho(0.0, width, height / aspectRatio, 0.0, -1, 1);
	} else {
	glOrtho(0.0, width * aspectRatio, height, 0.0, -1, 1);
	}

	if (width <= height) {
	glOrtho(-100.0, 100.0f, -height / aspectRatio, height / aspectRatio, -1, 1);
	}
	else {
	glOrtho(-width * aspectRatio, width * aspectRatio, -100.0, 100.0, -1, 1);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	// glOrtho(0.0, width, height, 0.0, -1, 1);


	Screen::width = width;
	Screen::height = height;

	// for (std::vector<View*>::iterator v = Screen::views.begin(); v != Screen::views.end(); ++v) {
		// (*v)->onScreenSizeChanged(width, height);
	//}

}

void Screen::mouseClick(int button, int state, int x, int y) {

	std::cout << "[" << button << ":" << state << "]\n";
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		int xx = (this->width / (float)this->width) * x;
		int yy = (this->height / (float)this->height) * y;
		std::cout << xx << ":::" << yy << "\n";
		// glEnableClientState
		// Screen::scene.point(xx, yy);
		MouseEvent *event = new MouseEvent(xx, yy);
		this->mouseAction(event, MouseEvent::Type::MOUSE_CLICK, MouseEvent::Input::BUTTON_LEFT);
	}
	if (button == 3 && state == GLUT_DOWN) {
		this->camera.zoomIn();

		this->camera.applyView();
	}
	if (button == 4 && state == GLUT_DOWN) {
		this->camera.zoomOut();

		this->camera.applyView();
	}
}

void Screen::keyboardAction(unsigned char key, int x, int y) {
	static bool fullscreen = false;
	std::cout << "Pressed:" << key << "[" << x << "," << y << "]\n";
	switch (key) {
	case 'f': case 'F': //toggle screenmode
		if (!fullscreen){
			glutFullScreen();
			fullscreen = true;
		}
		else if (fullscreen){
			glutReshapeWindow(1366, 768);
			glutPositionWindow(0, 0);
			fullscreen = false;
		}
		break;

	case 'x': case 'X': //toggle screenmode
		exit(0);
	}
}
