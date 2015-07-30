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
	void moveLeft() {
		matrix[3] -= 1; matrix[0] -= 1;
	};
	void moveRight() { matrix[3] += 1; 
	matrix[0] += 1;
	};

	void moveBack() {
		matrix[2] += 1;
		matrix[5] += 1;
	}

	void moveForward() {
		matrix[2] -= 1;
		matrix[5] -= 1;
	}

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

	void moveUp() { 
		// if (matrix[1] < 5 )
			//return;

		matrix[1] -= 1; 
		matrix[4] += 1;
	};
	void moveDown() { 
		// if (matrix[1] > 10)
			// return;

		matrix[1] += 1; 
		matrix[4] -= 1;
	};
	void init(int, int, int,
		int, int, int,
		int, int, int);
};

