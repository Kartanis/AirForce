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


using namespace Core;

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
