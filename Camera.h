#pragma once
class Camera
{
private:
	// gluLookAt(0.0, 45.0, -25, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// static float;
	static double matrix[9]; 
	double zoom;
	static const double zoomStep;
public:
	Camera();
	~Camera();
	void applyView();
	void zoomIn() { zoom -= zoomStep; };
	void zoomOut() { zoom -= zoomStep; };
	
};

