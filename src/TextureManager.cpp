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
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tga->hdr.width, tga->hdr.height,
		GL_RGBA, GL_UNSIGNED_BYTE, data->img_data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering



	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;

}


unsigned int TextureManager::loadFromBMP(char * filename) {
	unsigned int textureId;

	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(filename, "rb");
	if (!file) {
		printf("Image could not be opened\n"); return 0; 
	}

	if (fread(header, 1, 54, file) != 54){ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M'){
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);
	

	// Create one OpenGL texture
	glGenTextures(1, &textureId);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureId);

	for (int i = 0; i < height * width * 4; i+= 4) {
		if (data[i] == data[i + 1] && data[i + 2] == data[i + 3] && data[i] == data[i + 3] && data[i] == 255) {
			data[i + 3] = 0;
			// std::cout << "\ni." << i;
		}
	}

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;

}