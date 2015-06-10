#pragma once

class OnScreenSizeChangedListener {
public:
	// OnScreenSizeChangedListener(int ow, int oh, int w, int h);
	virtual void onScreenSizeChanged(int w, int h) = 0;
};
