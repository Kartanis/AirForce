#include "Screen.h"
#include "Scene.h"
#include <iostream>

using namespace gui;

int Screen::width = 800;
int Screen::height = 600;

Scene Screen::scene(Screen::width, Screen::height);

Screen::Screen(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(this->width, this->height);

	glutCreateWindow("Drawing my first triangle");
	glewInit();

	this->init();

	// register callbacks
	glutDisplayFunc(renderer);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	// glDeleteProgram(program);
}


Screen::~Screen()
{
}

void Screen::renderScene() {
	
		
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
	glOrtho(0.0, this->width, this->height, 0.0, -1, 1);

	
}


void  gui::renderer(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear black

	/*//use the created program
	glUseProgram(program);

	//draw 3 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	*/

	Screen::scene.draw();

	glutSwapBuffers();
	glutPostRedisplay();
}

void gui::reshape(int width, int height)
{
	Screen::scene.reshape(width, height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	Screen::width = width;
	Screen::height = height;

	
}

void gui::mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		int xx = (800 / (float)Screen::width) * x;
		int yy = (600 / (float)Screen::height) * y;
		std::cout << xx << ":::" << yy << "\n";
		
		Screen::scene.point(xx, yy);
	}
}

void gui::idleFunc()
{
	glutPostRedisplay();
}

void gui::keyboard(unsigned char key, int x, int y) {
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