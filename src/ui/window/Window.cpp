#include "Window.h"

Window& Window::getInstance()
{
	static Window theSingleInstance;
	return theSingleInstance;
}

Screen* Window::getScreen(void) {
	return screen;
}

void Window::setScreen(Screen* screen) {
	screenAppended = true;
	this->screen = screen;
}

bool Window::isScreenAppended() {
	return screenAppended;
}


Window::~Window()
{
}

Window::Window() {
	screenAppended = false;
	//screen = ;
}
