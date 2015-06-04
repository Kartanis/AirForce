#pragma once

#include <vector>
#include "../../Dependencies/glew/glew.h"
#include "../../Dependencies/freeglut/freeglut.h"
#include "../../MouseEvent.h"
#include "../../View.h"
#include "../../Camera.h"

namespace gui{

	class Screen
	{
	public:
		friend class Scene;
		friend void renderer(void);
		friend void reshape(int width, int height);
		friend void idleFunc(void);
		friend void mouseClick(int button, int state, int x, int y);
		friend void keyboard(unsigned char key, int x, int y);
		Screen(int argc, char **argv);
		~Screen();
		virtual void init(void);
		virtual void renderScene(void);
		static bool mouseAction(MouseEvent*, MouseEvent::Type, MouseEvent::Input);
	private:
		
		static int width;
		static int height;
		static Scene scene;
		static std::vector<View*> views;
		static void addView(View *view);
		static Camera camera;
	};

}