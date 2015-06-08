#pragma once
#include "src\GUI\Screen.h"
#include "Model.h"
#include "Terrain.h"

class CVector3
{
public:
	float x, y, z;
};

class ModelViewScene :
	public gui::Screen
{
private:
	Model* model;
	Terrain* terrain; 

	CVector3 unprojectedVectorFar, unprojectedVectorNear;
public:
	ModelViewScene(int argc, char **argv);
	virtual ~ModelViewScene();
	virtual void init(void);
	virtual void renderScene(void);
	virtual void reshapeScene(int width, int height);
	virtual void keyboardAction(unsigned char key, int x, int y);
	virtual void mouseClick(int button, int state, int x, int y);
	virtual void unProjectMouse(int, int);

};

