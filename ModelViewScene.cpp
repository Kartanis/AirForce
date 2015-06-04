#include "ModelViewScene.h"


ModelViewScene::ModelViewScene(int argc, char **argv) : gui::Screen(argc, argv)
{
}


ModelViewScene::~ModelViewScene()
{
}


void ModelViewScene::init(void){
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


}
