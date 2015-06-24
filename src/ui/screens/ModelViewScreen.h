#pragma once

#include "Screen.h"
#include "../../model/Model.h"
#include "../../model/Terrain.h"
#include "../../Core/CVector3.h"

class ModelViewScreen :
	public gui::Screen
{
private:
	Model* model;
	Terrain* terrain; 

	CVector3 unprojectedVectorFar, unprojectedVectorNear;
public:
	ModelViewScreen(int argc, char **argv);
	virtual ~ModelViewScreen();
	virtual void init(void);
	virtual void renderScene(void);
	virtual void reshapeScene(int width, int height);
	virtual void keyboardAction(unsigned char key, int x, int y);
	virtual void mouseClick(int button, int state, int x, int y);
	virtual void unProjectMouse(int, int);
};

