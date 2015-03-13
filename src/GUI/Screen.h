#pragma once

#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"

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
		void init(void);
		void renderScene(void);
	private:
		static int width;
		static int height;
		static Scene scene;
	};

}