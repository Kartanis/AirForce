#pragma once
#include "../temp/Frame.h"
#include "../../GUI/features/BlinkedMark.h"
#include <vector>
#include "../temp/View.h"
#include "../temp/Drawable.h"

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