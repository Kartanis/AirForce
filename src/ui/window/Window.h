#pragma once
#include "../screens/Screen.h"

using namespace gui;

class Window
{
public:

	static  Window& Window::getInstance();
	Screen* getScreen(void); 
	void setScreen(Screen*);
	bool isScreenAppended();
private:
	~Window();
	Window();
	Window(const Window& root);
	Window& operator=(const Window&);
	
	Screen* screen;
	bool screenAppended;
};