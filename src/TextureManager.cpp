#include <texturing/TextureManager.h>
#include <iostream>
#include <tga/tga.h>
#include <exceptions/IOException.h>
#include <exceptions/OutOfMemoryException.h>
#include <platform_definitions.h>

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

unsigned int TextureManager::loadFromTGA(char * filename) {
	TGA *tga;
	TGAData *data;

	data = (TGAData*)malloc(sizeof(TGAData));
	if (!data) {
		TGA_ERROR((TGA*)NULL, TGA_OOM);
		std::string message = "Couldn't allocate memory with for TGA file ";
		message += filename;
		throw OutOfMemoryException(message.c_str());
	}

	printf("[open] name=%s, mode=%s\n", filename, "r");
	tga = TGAOpen(filename, "r");
	if (!tga || tga->last != TGA_OK) {
		TGA_ERROR(tga, TGA_OPEN_FAIL);
		std::string message = "Filed to open TGA file";
		message += filename;
		throw IOException(message.c_str());
		
	}

	printf("[read] image\n");
	data->flags = TGA_IMAGE_INFO | TGA_IMAGE_DATA;;
	if (TGAReadImage(tga, data) != TGA_OK) {
		TGA_ERROR(tga, TGA_READ_FAIL);
		std::string message = "Failed to read TGA file ";
		message += filename;
		throw IOException(message.c_str());
	}
	if (data->flags & TGA_IMAGE_INFO) {
		printf("[info] width=%i\n", tga->hdr.width);
		printf("[info] height=%i\n", tga->hdr.height);

		printf("[info] color map type=%i\n", tga->hdr.map_t);

		printf("[info] image type=%i\n", tga->hdr.img_t);

		printf("[info] depth=%i\n", tga->hdr.depth);
		printf("[info] x=%i\n", tga->hdr.x);
		printf("[info] y=%i\n", tga->hdr.y);
		printf("[info] orientation=%s-%s\n",
			(tga->hdr.vert == TGA_BOTTOM) ?
			"bottom" : "top",
			(tga->hdr.horz == TGA_LEFT) ?
			"left" : "right");
	}

	TGAClose(tga);

	unsigned int textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tga->hdr.width, tga->hdr.height,
		GL_RGBA, GL_UNSIGNED_BYTE, data->img_data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;

}