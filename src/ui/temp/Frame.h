#pragma once


#include <definitions.h>

class Frame
{
public:
	Frame(int, int);
	void draw(void);
	void reshape(int, int);
	~Frame();
private:
	int height;
	int width;
	int mult = 120;

};

