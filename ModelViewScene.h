#pragma once
#include "src\GUI\Screen.h"
class ModelViewScene :
	public gui::Screen
{
public:
	ModelViewScene(int argc, char **argv);
	virtual ~ModelViewScene();
	virtual void init(void);
	virtual void renderScene(void);
	static bool mouseAction(MouseEvent*, MouseEvent::Type, MouseEvent::Input);
};

