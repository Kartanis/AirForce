#pragma once
class MouseEvent
{
public:
	enum Type {
		MOVE, MOUSE_DOWN, MOUSE_UP, MOUSE_HOLD, MOUSE_CLICK
	};
	enum Input {
		BUTTON_LEFT, BUTTON_RIGHT, BUTTON_MIDDLE, BUTTON_SPECIAL
	};
	MouseEvent(int x, int y);
	~MouseEvent();

	inline int getX() { return x; };
	inline int getY() { return y; };
private:
	int x, y;
};


