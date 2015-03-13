#pragma once
#include "../Frame.h"
#include "features\BlinkedMark.h"

namespace gui{

	class Scene
	{
	public:
		Scene(int, int);
		~Scene();
		void draw();
		void reshape(int, int);
		void point(int, int);
	private:
		Frame* frame;
		BlinkedMark mark;
	};

}