#pragma once
#include "src\GUI\Screen.h"
#include "Model.h"
class ModelViewScene :
	public gui::Screen
{
private:
	Model model;
public:
	ModelViewScene(int argc, char **argv);
	virtual ~ModelViewScene();
	virtual void init(void);
	virtual void renderScene(void);
	virtual void reshapeScene(int width, int height);
	static bool mouseAction(MouseEvent*, MouseEvent::Type, MouseEvent::Input);
	virtual void keyboardAction(unsigned char key, int x, int y);
};

