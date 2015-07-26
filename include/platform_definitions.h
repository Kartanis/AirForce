//
// Created by kartanis on 26.07.15.
//
#pragma once

#define LINUX_NATIVE

#ifdef WINDOWS_LOCAL
	#include <glew/include/glew.h>
	#include <freeglut/include/freeglut.h>
#elif defined(LINUX_NATIVE)
	#include <GL/glew.h>
	#include <GL/freeglut.h>
#endif

