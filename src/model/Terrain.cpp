#include <models\Terrain.h>
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

	printf("[open] name=%s, mode=%s\n", "resources/textures/ground.tga", "r");
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


	// fWidth = 8;
	// fHeight = 8;

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
	
	tbyte* map = data->img_data;

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
			this->data[pointer + 1] = (map[i * fWidth + j] / 16)*fStep; // y
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
}

Terrain::~Terrain()
{
}

void simpleterrain() {

}


void Terrain::intersect(CVector3 near, CVector3 far, CVector3 *res) {
	float t, u, v;
	float orig[3] = { near.x, near.y, near.z };
	float dir[3] = { far.x, far.y, far.z };
	
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
	// if (!(Math::intersect_triangle(orig, dir, rv1, rv2, rv3, &t, &u, &v) == 0 || Math::intersect_triangle3(orig, dir, lv1, lv2, lv3, &t, &u, &v) == 0))  {
		// return;
	//} 

	res->x = orig[0] + dir[0] * t;
	res->y = orig[1] + dir[1] * t;
	res->z = orig[2] + dir[2] * t;

	std::cout << "Intersection......Start\n";
	std::cout << u << " " << v << " " << t << "\n";
	std::cout << orig[0] << " " << orig[1] << " " << orig[2] << "\n";
	std::cout << dir[0] << " " << dir[1] << " " << dir[2] << "\n";
	std::cout << *(res) << "\n";
	std::cout << "Intersection......End\n";


};

void Terrain::Draw() {
	// glBegin();
	Model::Draw();

}