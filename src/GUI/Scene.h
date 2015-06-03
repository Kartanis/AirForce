#pragma once
#include "../Frame.h"
#include "features\BlinkedMark.h"
#include <vector>
#include "../../View.h"
#include "../../Drawable.h"

namespace gui{

	class Scene : public View 
	{
	public:
		Scene(int x, int y, int w, int h);
		~Scene();
		void draw();
		void reshape(int, int);
		void point(int, int);

		void onScreenSizeChanged(int w, int h);
	private:
		Frame* frame;
		BlinkedMark mark;
		
	};

}