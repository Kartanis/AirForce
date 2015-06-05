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
	void moveLeft() { matrix[0] -= 1; };
	void moveRight() { matrix[0] += 1; };

	void moveLeftSide() { 
		matrix[0] -= 1; 
		if(matrix[2] > 0 && matrix[2] <= 10)
			matrix[2] += 1; 
		else
			matrix[2] -= 1;
	};
	void moveRightSide() { 
		matrix[0] += 1; 
		if (matrix[2] > 0 && matrix[2] <= 10)
			matrix[2] += 1;
		else
			matrix[2] -= 1;
	};

	void moveUp() { matrix[1] += 1; };
	void moveDown() { matrix[1] -= 1; };
	void init(int, int, int,
		int, int, int,
		int, int, int);
};

