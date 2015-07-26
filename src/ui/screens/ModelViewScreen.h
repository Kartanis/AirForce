#pragma once

#include "Screen.h"
#include <models/Model.h>
#include <models/Terrain.h>
#include <math/CVector3.h>

class ModelViewScreen :
	public gui::Screen
{
private:
	Model* model;
	Terrain* terrain; 
	Model* cube;

	CVector3 unprojectedVectorFar, unprojectedVectorNear;
	CVector3 lastIntersect;
	unsigned int previousFrames = 0;
	unsigned int frames = 0;
	long millisPassed = 0;
	float previousRenderTime = 0.0f;
	float timeDelta = 0.0f;
public:
	ModelViewScreen(int argc, char **argv);
	virtual ~ModelViewScreen();
	virtual void init(void);
	virtual void renderScene(void);
	virtual void reshapeScene(int width, int height);
	virtual void keyboardAction(unsigned char key, int x, int y);
	virtual void mouseClick(int button, int state, int x, int y);
	virtual void unProjectMouse(int, int);

	void DrawText(std::string ) const;

	long getSystemTimeInMillis() const;

	void calcFrames(long beginTime, long finishTime);
};

