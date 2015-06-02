#pragma once
#include <vector>
#include "Drawable.h"
#include "OnMouseActionListener.h"

class View: public OnMouseActionListener, public Drawable
{
public:
	View(int x, int y, int w, int h);
	~View();
	virtual bool onMouseAction(MouseEvent*, MouseEvent::Type, MouseEvent::Input);
	virtual void draw();

protected:
	int x;
	int y;
	int w;
	int h;
	int blinkedTimes;
	bool colorChanged;
	int times;

	std::vector<Drawable> drawables();
};

