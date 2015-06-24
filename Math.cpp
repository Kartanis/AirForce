#include "Math.h"


/* Ray-Triangle Intersection Test Routines          */
/* Different optimizations of my and Ben Trumbore's */
/* code from journals of graphics tools (JGT)       */
/* http://www.acm.org/jgt/                          */
/* by Tomas Moller, May 2000                        */

/* the original jgt code */
int Math::intersect_triangle(float orig[3], float dir[3],
	float vert0[3], float vert1[3], float vert2[3],
	float *t, float *u, float *v)
{
	float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	float det, inv_det;

	/* find vectors for two edges sharing vert0 */
	SUB(edge1, vert1, vert0);
	SUB(edge2, vert2, vert0);

	/* begin calculating determinant - also used to calculate U parameter */
	CROSS(pvec, dir, edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = DOT(edge1, pvec);

	if (det > -EPSILON && det < EPSILON)
		return 0;
	inv_det = 1.0 / det;

	/* calculate distance from vert0 to ray origin */
	SUB(tvec, orig, vert0);

	/* calculate U parameter and test bounds */
	*u = DOT(tvec, pvec) * inv_det;
	if (*u < 0.0 || *u > 1.0)
		return 0;

	/* prepare to test V parameter */
	CROSS(qvec, tvec, edge1);

	/* calculate V parameter and test bounds */
	*v = DOT(dir, qvec) * inv_det;
	if (*v < 0.0 || *u + *v > 1.0)
		return 0;

	/* calculate t, ray intersects triangle */
	*t = DOT(edge2, qvec) * inv_det;

	return 1;
}


/* code rewritten to do tests on the sign of the determinant */
/* the division is at the end in the code                    */
int Math::intersect_triangle1(float orig[3], float dir[3],
	float vert0[3], float vert1[3], float vert2[3],
	float *t, float *u, float *v)
{
	float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	float det, inv_det;

	/* find vectors for two edges sharing vert0 */
	SUB(edge1, vert1, vert0);
	SUB(edge2, vert2, vert0);

	/* begin calculating determinant - also used to calculate U parameter */
	CROSS(pvec, dir, edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = DOT(edge1, pvec);

	if (det > EPSILON)
	{
		/* calculate distance from vert0 to ray origin */
		SUB(tvec, orig, vert0);

		/* calculate U parameter and test bounds */
		*u = DOT(tvec, pvec);
		if (*u < 0.0 || *u > det)
			return 0;

		/* prepare to test V parameter */
		CROSS(qvec, tvec, edge1);

		/* calculate V parameter and test bounds */
		*v = DOT(dir, qvec);
		if (*v < 0.0 || *u + *v > det)
			return 0;

	}
	else if (det < -EPSILON)
	{
		/* calculate distance from vert0 to ray origin */
		SUB(tvec, orig, vert0);

		/* calculate U parameter and test bounds */
		*u = DOT(tvec, pvec);
		/*      printf("*u=%f\n",(float)*u); */
		/*      printf("det=%f\n",det); */
		if (*u > 0.0 || *u < det)
			return 0;

		/* prepare to test V parameter */
		CROSS(qvec, tvec, edge1);

		/* calculate V parameter and test bounds */
		*v = DOT(dir, qvec);
		if (*v > 0.0 || *u + *v < det)
			return 0;
	}
	else return 0;  /* ray is parallell to the plane of the triangle */


	inv_det = 1.0 / det;

	/* calculate t, ray intersects triangle */
	*t = DOT(edge2, qvec) * inv_det;
	(*u) *= inv_det;
	(*v) *= inv_det;

	return 1;
}

/* code rewritten to do tests on the sign of the determinant */
/* the division is before the test of the sign of the det    */
int Math::intersect_triangle2(float orig[3], float dir[3],
	float vert0[3], float vert1[3], float vert2[3],
	float *t, float *u, float *v)
{
	float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	float det, inv_det;

	/* find vectors for two edges sharing vert0 */
	SUB(edge1, vert1, vert0);
	SUB(edge2, vert2, vert0);

	/* begin calculating determinant - also used to calculate U parameter */
	CROSS(pvec, dir, edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = DOT(edge1, pvec);

	/* calculate distance from vert0 to ray origin */
	SUB(tvec, orig, vert0);
	inv_det = 1.0 / det;

	if (det > EPSILON)
	{
		/* calculate U parameter and test bounds */
		*u = DOT(tvec, pvec);
		if (*u < 0.0 || *u > det)
			return 0;

		/* prepare to test V parameter */
		CROSS(qvec, tvec, edge1);

		/* calculate V parameter and test bounds */
		*v = DOT(dir, qvec);
		if (*v < 0.0 || *u + *v > det)
			return 0;

	}
	else if (det < -EPSILON)
	{
		/* calculate U parameter and test bounds */
		*u = DOT(tvec, pvec);
		if (*u > 0.0 || *u < det)
			return 0;

		/* prepare to test V parameter */
		CROSS(qvec, tvec, edge1);

		/* calculate V parameter and test bounds */
		*v = DOT(dir, qvec);
		if (*v > 0.0 || *u + *v < det)
			return 0;
	}
	else return 0;  /* ray is parallell to the plane of the triangle */

	/* calculate t, ray intersects triangle */
	*t = DOT(edge2, qvec) * inv_det;
	(*u) *= inv_det;
	(*v) *= inv_det;

	return 1;
}

/* code rewritten to do tests on the sign of the determinant */
/* the division is before the test of the sign of the det    */
/* and one CROSS has been moved out from the if-else if-else */
int Math::intersect_triangle3(float orig[3], float dir[3],
	float vert0[3], float vert1[3], float vert2[3],
	float *t, float *u, float *v)
{
	float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	float det, inv_det;

	/* find vectors for two edges sharing vert0 */
	SUB(edge1, vert1, vert0);
	SUB(edge2, vert2, vert0);

	/* begin calculating determinant - also used to calculate U parameter */
	CROSS(pvec, dir, edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = DOT(edge1, pvec);

	/* calculate distance from vert0 to ray origin */
	SUB(tvec, orig, vert0);
	inv_det = 1.0 / det;

	CROSS(qvec, tvec, edge1);

	if (det > EPSILON)
	{
		*u = DOT(tvec, pvec);
		if (*u < 0.0 || *u > det)
			return 0;

		/* calculate V parameter and test bounds */
		*v = DOT(dir, qvec);
		if (*v < 0.0 || *u + *v > det)
			return 0;

	}
	else if (det < -EPSILON)
	{
		/* calculate U parameter and test bounds */
		*u = DOT(tvec, pvec);
		if (*u > 0.0 || *u < det)
			return 0;

		/* calculate V parameter and test bounds */
		*v = DOT(dir, qvec);
		if (*v > 0.0 || *u + *v < det)
			return 0;
	}
	else return 0;  /* ray is parallell to the plane of the triangle */

	*t = DOT(edge2, qvec) * inv_det;
	(*u) *= inv_det;
	(*v) *= inv_det;

	return 1;
}


Math::Math()
{
}


Math::~Math()
{
}
