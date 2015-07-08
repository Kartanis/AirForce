#pragma once
#include "Model.h"
#include <math/CVector3.h>
class Terrain :
	public Model
{
public:
	Terrain();
	~Terrain();
	void intersect(CVector3, CVector3, CVector3*);
	void Draw();
	void loadTexture();
};

