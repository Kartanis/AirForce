//
// Created by kartanis on 26.07.15.
//
#pragma once

#define WINDOWS_LOCAL

#ifdef WINDOWS_LOCAL
	#include <glew/include/glew.h>
	#include <freeglut/include/freeglut.h>
#endif

#ifdef LINUX_NATIVE
	#include <GL/glew.h>
	#include <GL/freeglut.h>
#endif

