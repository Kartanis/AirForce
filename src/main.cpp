#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <vector>

#include "Core/Shader_Loader.h"
#include "ui/screens/ModelViewScreen.h"
#include "ui/window/Window.h"
#include <FileSystem/ObjModelReader.h>
#include <FileSystem/FileReader.h>
#include <json/json.h>
#include <easylog/easylogging++.h>
#include <renderers/Renderer.h>


using namespace Core;

INITIALIZE_EASYLOGGINGPP
GLuint program;

/*
- Show backgound texture(Video playback)
x keyboard reader
- show text on page
- adjust screen to real pixels
x full screen(enable/disable by pressnging F button)
x draw blinker
x mouse handler
x refactoring
*/

int main(int argc, char **argv) {
	LOG(DEBUG) << "My first info log using default logger";


	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	FileReader fr("resources/maps/ancient_kiev.map");

	std::string line = fr.readLine();
	std::cout << line << "\n";

	bool parsingSuccessful = reader.parse(line, root);
	//bool parsingSuccessful = reader.parse(" {      \"encoding\" : \"UTF-8\",           \"plug-ins\" : [         \"python\",         \"c++\",         \"ruby\"         ],               \"indent\" : { \"length\" : 3, \"use_space\": true } }", root);
	if (!parsingSuccessful)
	{
		// report to the user the failure and their locations in the document.
		std::cout << "Failed to parse configuration\n"
			<< reader.getFormattedErrorMessages();
		 exit(1);
	}

	// Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
	// such member.
	std::string encoding = root.get("id", "None").asString();
	std::cout << encoding << "\n";
	// Get the value of the member of root named 'encoding', return a 'null' value if
	// there is no such member.


	// And you can write to a stream, using the StyledWriter automatically.
	//std::cout << root << "\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);

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
	
	glutReshapeFunc(gui::reshape);
	glutMouseFunc(gui::mouseClick);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboard);

	// glutMainLoop();
	// glDeleteProgram(program);

	Renderer r;
	r.init();
	

	int x = 1;
	do {
		r.invalidate();
		r.draw();
		
	} while(x != 0);
	// Window &window = Window::getInstance();
	// window.setScreen(new ModelViewScreen(argc, argv));
	// window.getScreen()->init();

	// glutMainLoop();
	
	return 0;

}

int getShaderLanguageVersion(void) {
	std::string version = std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
	int value = 0;
	int deg = 0;
	for (unsigned int i = 0; i <= version.length(); i++) {
		if (version[i] != ' ') {
			if (version[i] >= '0' && version[i] <= '9') {
				value = value * 10;
				value += version[i] - '0';
			}

		} else {
			break;
		}
	}

	return value;
}

int degree(int v, int d) {
	int res = v;
	if (d == 0) return 1;
	for (int i = 1; i < d; i++) {
		res *= v;
	}

	return res;
}
