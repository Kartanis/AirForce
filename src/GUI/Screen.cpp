#include "Screen.h"
#include "Scene.h"
#include <iostream>
#include "../../Dependencies/glew/glew.h"


using namespace gui;

int Screen::width = 800;
int Screen::height = 600;

// Scene Screen::scene(Screen::width, Screen::height);
std::vector <View*> Screen::views;

Screen::Screen(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(this->width, this->height);
	
	Screen::addView(new View(0, 0, this->width, 70));
	Screen::addView(new View(0, 71, 120, this->height));
	Screen::addView(new View(121, 71, this->width, this->height));

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

void Screen::addView(View* view){
	Screen::views.push_back(view);
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
	glViewport(0, 0, Screen::width, Screen::height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	for (std::vector<View*>::iterator v = Screen::views.begin(); v != Screen::views.end(); ++v) {
		(*v)->draw();
	}
	
	glRectf(0.0f, 0.0f, 1.0f, 1.0f);
	//Screen::scene.draw();

	glutSwapBuffers();
	glutPostRedisplay();
}

void gui::reshape(int width, int height)
{
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
		int xx = (Screen::width / (float)Screen::width) * x;
		int yy = (Screen::height / (float)Screen::height) * y;
		std::cout << xx << ":::" << yy << "\n";
		
		// Screen::scene.point(xx, yy);
		MouseEvent *event = new MouseEvent(xx, yy);
		Screen::mouseAction(event, MouseEvent::Type::MOUSE_CLICK, MouseEvent::Input::BUTTON_LEFT);
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


bool Screen::mouseAction(MouseEvent *event, MouseEvent::Type type, MouseEvent::Input input) {
	for (std::vector<View*>::iterator v = Screen::views.begin(); v != Screen::views.end(); ++v) {
		if ((*v)->onMouseAction(event, type, input))
			return true;
	}
	return false;
}