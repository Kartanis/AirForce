#include <models/Terrain.h>
#include <iostream>
#include <math/Math.h>
#include <tga/tga.h>


Terrain::Terrain()
{
	std::cout << "Terrain called.." << "\n";
	TGA *tga;
	TGAData *data;

	data = (TGAData*)malloc(sizeof(TGAData));
	if (!data) {
		TGA_ERROR((TGA*)NULL, TGA_OOM);
		return;
	}

	printf("[open] name=%s, mode=%s\n", "resources/textures/ground_2.tga", "r");
	tga = TGAOpen("resources/maps/ground_2.tga", "r");
	if (!tga || tga->last != TGA_OK) {
		TGA_ERROR(tga, TGA_OPEN_FAIL);
		return;
	}

	printf("[read] image\n");
	data->flags = TGA_IMAGE_INFO | TGA_IMAGE_DATA;;
	if (TGAReadImage(tga, data) != TGA_OK) {
		TGA_ERROR(tga, TGA_READ_FAIL);
		return;
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

	

	int fWidth = tga->hdr.width;
	int fHeight = tga->hdr.height;
	GLfloat fStep = 1.0f;
	// GLfloat y = -0.4f;
	GLfloat iLine;


	fWidth = 8;
	fHeight = 8;

	const int indicesPerQuad = Model::INDICES_PER_TRIANGLE * Model::TRINAGLES_PER_QUAD;
	isWireFrame = true;
	this->verticesNumber = fWidth * fHeight;
	this->indicesNumber = (fWidth - 1) * (fHeight - 1) * indicesPerQuad;

	this->data = new float[verticesNumber * Model::POINTS_PER_VERTEX];
	this->indices = new unsigned int[indicesNumber];


	tbyte testData[64] = {
		0, 0, 1, 2,
		0, 1, 1, 2,
		1, 2, 2, 2,
		0, 1, 1, 2,
		0, 1, 1, 2,
		1, 2, 2, 2,
		0, 1, 1, 2,
		0, 0, 1, 2,
		0, 0, 1, 2,
		0, 1, 1, 2,
		1, 2, 2, 2,
		0, 1, 1, 2,
		0, 1, 1, 2,
		1, 2, 2, 2,
		0, 1, 1, 2,
		0, 0, 1, 2
	};

	tbyte testData2[4] = {
		0, 0, 
		0, 1
	};
	
	tbyte* map = testData;
	//tbyte* map = data->img_data;

	std::cout << "Terrain from reader called..2.1" << "\n";
	std::cout << "vertNum: " << verticesNumber << "\n";
	std::cout << "faceNum:" << indicesNumber / 6 << "\n";
	std::cout << "verticesNumber:" << verticesNumber << "\n";
	std::cout << "indicesNumber:" << indicesNumber << "\n";

	for (int i = 0; i <= fWidth - 1; i++) {
		for (int j = 0; j <= fHeight - 1; j++) {
			int pointer = (i * fWidth * Model::POINTS_PER_VERTEX) + j * Model::POINTS_PER_VERTEX;

			// CVector3 vertice = CVector3((float)i - fWidth / 2, map[i * fWidth + j], (float)j - fHeight / 2);
			// std::cout << "Current vertice is: " << vertice << "\n";
			//std::cout << "pointer : " << pointer << "\n";

			this->data[pointer] = ((float)i - fWidth / 2) * fStep; // x
			this->data[pointer + 1] = (map[i * fWidth + j])*fStep; // y
			this->data[pointer + 2] = ((float)j - fHeight / 2) * fStep; //z
		}

	}

	for (int i = 0; i <= fWidth - 2; i++) {
		for (int j = 0; j <= fHeight - 2; j++) {
			int lineLength = fWidth;
			int quadsPerLine = lineLength - 1;
			int base = i * lineLength + j;
			int pointer = (i * quadsPerLine * indicesPerQuad) + j * indicesPerQuad;

			// std::cout << "lineLength : " << lineLength << "\n";
			// std::cout << "quadsPerLine : " << quadsPerLine << "\n";
			// std::cout << "base : " << base << "\n";
			// std::cout << "pointer : " << pointer << "\n";
			
			this->indices[pointer] = base;
			this->indices[pointer + 1] = base + 1;
			this->indices[pointer + 2] = base + lineLength;

			this->indices[pointer + 3] = base + 1;
			this->indices[pointer + 4] = lineLength + base + 1;
			this->indices[pointer + 5] = lineLength + base;
		}
	}
	
	TGAClose(tga);

	loadTexture();
}

Terrain::~Terrain()
{
}

void Terrain::loadTexture() {
	TGA *tga;
	TGAData *data;

	data = (TGAData*)malloc(sizeof(TGAData));
	if (!data) {
		TGA_ERROR((TGA*)NULL, TGA_OOM);
		return;
	}

	printf("[open] name=%s, mode=%s\n", "resources/textures/ground_grass.tga", "r");
	tga = TGAOpen("resources/textures/ground_grass.tga", "r");
	if (!tga || tga->last != TGA_OK) {
		TGA_ERROR(tga, TGA_OPEN_FAIL);
		return;
	}

	printf("[read] image\n");
	data->flags = TGA_IMAGE_INFO | TGA_IMAGE_DATA;;
	if (TGAReadImage(tga, data) != TGA_OK) {
		TGA_ERROR(tga, TGA_READ_FAIL);
		return;
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

	glGenTextures(1, &this->backgroundTextureId); //���������� �������������. ������ ����� ������� ����� 1
	glBindTexture(GL_TEXTURE_2D, this->backgroundTextureId);
	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tga->hdr.width, tga->hdr.height,
		GL_RGB, GL_UNSIGNED_BYTE, data->img_data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

CVector3 Terrain::getIndexesByFirstIndex(int index) {
	CVector3 vec = CVector3((float)indices[index], (float)indices[index] + 1, (float)indices[index] + 2);
	return vec;
}

CVector3 Terrain::getVertexByIndex(int index) {
	CVector3 vec = CVector3((float)data[index], (float)data[index + 1], (float)data[index + 2]);
	return vec;
}

void Terrain::intersect(CVector3 near2, CVector3 far2, CVector3 *res) {
	float t, u, v;
	float orig[3] = { near2.x, near2.y, near2.z };
	float dir[3] = { far2.x, far2.y, far2.z };
	
	float rv1[3] = { -50.0, 0, -50.0 };
	float rv2[3] = { 50.0, 0, -50.0 };
	float rv3[3] = { 50.0, 0, 50.0 };

	float lv1[3] = { -50.0, 0, -50.0 };
	float lv2[3] = { -50.0, 0, 50.0 };
	float lv3[3] = { 50.0, 0, 50.0 };

	int result = Math::intersect_triangle(orig, dir, rv1, rv2, rv3, &t, &u, &v);
	if (result == 0) {
		std::cout << "right not found" << "\n";
		result = Math::intersect_triangle3(orig, dir, lv1, lv2, lv3, &t, &u, &v);
	}
	if (result == 0) {
		return;
	}

	res->x = orig[0] + dir[0] * t;
	res->y = orig[1] + dir[1] * t;
	res->z = orig[2] + dir[2] * t;

	std::cout << "Intersection......Start\n";
	std::cout << u << " " << v << " " << t << "\n";
	std::cout << orig[0] << " " << orig[1] << " " << orig[2] << "\n";
	std::cout << dir[0] << " " << dir[1] << " " << dir[2] << "\n";
	std::cout << *(res) << "\n";
	std::cout << "Intersection......End\n";

	for (int i = 0; i < indicesNumber; i+=3) {
		std::cout << "i:" << i << "\t" << indices[i] << "\t" << indices[i] + 1 << "\t" << indices[i] + 2 << "\n";
		std::cout << "i:" << i + 1 << "\t" << indices[i+1] << "\t" << indices[i+1] + 1 << "\t" << indices[i+1] + 2 << "\n";
		std::cout << "i:" << i + 2<< "\t" << indices[i+2] << "\t" << indices[i+2] + 1 << "\t" << indices[i+2] + 2 << "\n";
		std::cout << "Vec:" << getIndexesByFirstIndex(i) << "\n";
		std::cout << "Vec:" << getIndexesByFirstIndex(i + 1) << "\n";
		std::cout << "Vec:" << getIndexesByFirstIndex(i + 2) << "\n";

		std::cout << "VecA:" << getVertexByIndex(indices[i]) << "\n";
		std::cout << "VecB:" << getVertexByIndex(indices[i + 1]) << "\n";
		std::cout << "VecC:" << getVertexByIndex(indices[i + 2]) << "\n";

		float v1[3] = { data[indices[i]], data[indices[i] + 1], data[indices[i]+ 2] };
		float v2[3] = { data[indices[i + 1]], data[indices[i + 1] + 1], data[indices[i + 1] + 2] };
		float v3[3] = { data[indices[i + 2]], data[indices[i + 2] + 1], data[indices[i + 2] + 2] };
		int result = 0; Math::intersect_triangle3(orig, dir, v1, v2, v3, &t, &u, &v);
		
		if (result == 0) {
			intersection->x = indices[i];
			intersection->y = indices[i + 1];
			intersection->z = indices[i+ 2];
		}
	}

};



void Terrain::Draw() {
	// glBegin();
	Model::Draw();
	/*
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);

		glVertex3f(data[indices[(int)intersection->x]], data[indices[(int)intersection->x] + 1], data[(int)intersection->x] + 2);
		glVertex3f(data[indices[(int)intersection->y]], data[indices[(int)intersection->y] + 1], data[(int)intersection->y] + 2);
		glVertex3f(data[indices[(int)intersection->z]], data[indices[(int)intersection->z] + 1], data[(int)intersection->z] + 2);

	glEnd();
	*/
}