#pragma once

#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2]; 

class Math
{
public:
	Math();
	~Math();
	static int intersect_triangle(float orig[3], float dir[3],
		float vert0[3], float vert1[3], float vert2[3],
		float *t, float *u, float *v);
	static int intersect_triangle1(float orig[3], float dir[3],
		float vert0[3], float vert1[3], float vert2[3],
		float *t, float *u, float *v);

	static int intersect_triangle2(float orig[3], float dir[3],
		float vert0[3], float vert1[3], float vert2[3],
		float *t, float *u, float *v);

	static int intersect_triangle3(float orig[3], float dir[3],
		float vert0[3], float vert1[3], float vert2[3],
		float *t, float *u, float *v);
};



