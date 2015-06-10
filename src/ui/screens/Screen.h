#pragma once

#include <vector>
#include "../../../Dependencies/glew/glew.h"
#include "../../../Dependencies/freeglut/freeglut.h"
#include "../events/MouseEvent.h"

#include "../camera/Camera.h"

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
		virtual void reshapeScene(int width, int height);

		virtual bool mouseAction(MouseEvent*, MouseEvent::Type, MouseEvent::Input);
		virtual void mouseClick(int button, int state, int x, int y);
		virtual void keyboardAction(unsigned char key, int x, int y);
		// static bool mouseAction(MouseEvent*, MouseEvent::Type, MouseEvent::Input);
	private:
		
		static Scene scene;

	protected:
		float fieldOfViewAngle = 45;
		float zNear = 1.0f;
		float zFar = 500.0f;
		int width = 800;
		int height = 600;
		static Camera camera;

	};

}
