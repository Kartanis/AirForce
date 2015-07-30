#pragma once
#include <string>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	static unsigned int loadFromTGA(char *);
	static unsigned int loadFromBMP(char *);
};

