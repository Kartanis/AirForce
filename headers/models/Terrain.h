#pragma once
#include "Model.h"
#include <math/CVector3.h>
class Terrain :
	public Model
{
private:
	CVector3 getVertexByIndex(int index);
	CVector3 getIndexesByFirstIndex(int index);
public:
	Terrain();
	~Terrain();
	void intersect(CVector3, CVector3, CVector3*);
	void Draw();
	void loadTexture();
	CVector3 *intersection;
};

