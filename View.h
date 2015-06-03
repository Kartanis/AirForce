#pragma once
#include <vector>
#include "Drawable.h"
#include "OnMouseActionListener.h"
#include "OnScreenSizeChangedListener.h"

class View : public OnMouseActionListener, public Drawable, public OnScreenSizeChangedListener
{
public:
	View(int x, int y, int w, int h);
	~View();
	virtual bool onMouseAction(MouseEvent*, MouseEvent::Type, MouseEvent::Input);
	virtual void draw();

	enum Listeners {OnScreenSizeChangedListener};

	void onScreenSizeChanged(int w, int h);
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


