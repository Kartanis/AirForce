//
// Created by kartanis on 26.07.15.
//
#pragma once

#define MAC_OS_X

#ifdef WINDOWS_LOCAL
	#include <glew/include/glew.h>
	#include <freeglut/include/freeglut.h>
	#include <Windows.h>
#elif defined(LINUX_NATIVE)
	#include <GL/glew.h>
	#include <GL/freeglut.h>

	#include <unistd.h>
	#include <sys/time.h>	
#elif defined MAC_OS_X
	#include <glewMACOSX/include/glew.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif

namespace time_system {
	long currentTimeInMillis();
	int sleepInMillis(long milliseconds);
}