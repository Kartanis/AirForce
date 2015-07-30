#pragma once
#include <vector>
#include <camera\Camera.h>

class Renderer
{

public:
	Renderer();
	~Renderer();
	void init();
	void draw();
	void invalidate();

	void draw2DOverlay();
	void draw3DScene();
	void clearBuffer(int );

	void saveAndClearMatrix(int );
	void revertMatrix(int);

protected:
	std::vector<Camera> cams;
	Camera selectedCamera;

	// the block below of initials should be encapsulated in future
	int width = 800;
	int height = 600;
	float fieldOfViewAngle = 45;
	float zNear = 1.0f;
	float zFar = 500.0f;
	// the block above of initials should be encapsulated in future

	bool needToReDraw = false;
};

