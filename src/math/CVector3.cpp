/*
 * CVector.cpp
 *
 *  Created on: 15 ���� 2015 �.
 *      Author: ������
 */

#include <math/CVector3.h>

CVector3::CVector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;

}

CVector3::CVector3() : CVector3(0.0f, 0.0f, 0.0f){
}

CVector3::~CVector3() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator <<(std::ostream& os, const CVector3& vec)
{
	os << '[' << vec.x << ", " << vec.y << ", " << vec.z << ']';
	return os;
}