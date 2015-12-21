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

	 Window &window = Window::getInstance();
	 window.setScreen(new ModelViewScreen(argc, argv));
	 window.getScreen()->init();

	glutMainLoop();

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
