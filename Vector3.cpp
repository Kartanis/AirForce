//---------------------------------------------------------------------
// CVector3.cpp
#include "Vector3.h"
CVector3::CVector3()
{
	x = y = z = 0.0;
}
CVector3::CVector3(float f)
{
	x = f; y = f; z = f;
}
CVector3::CVector3(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
}
CVector3::CVector3(const CVector3 &Vect)
{
	x = Vect.x;
	y = Vect.y;
	z = Vect.z;
}
void CVector3::operator =(float f)
{
	x = f;
	y = f;
	z = f;
}
void CVector3::operator =(CVector3 Vect)
{
	x = Vect.x;
	y = Vect.y;
	z = Vect.z;
}
Vector addition / subtraction / multiplication / division with another Vector
CVector3 CVector3::operator+(CVector3 Vect)
{
	return CVector3(Vect.x + x, Vect.y + y, Vect.z + z);
}
CVector3 CVector3::operator-(CVector3 Vect)
{
	return CVector3(x - Vect.x, y - Vect.y, z - Vect.z);
}
CVector3 CVector3::operator*(CVector3 Vect)
{
	return CVector3(x*Vect.x, y*Vect.y, z*Vect.z);
}
CVector3 CVector3::operator/(CVector3 Vect)
{
	return CVector3(x / Vect.x, y / Vect.y, z / Vect.z);
}
Vector addition / subtraction / multiplication / division with a scalar.
CVector3 CVector3::operator +(float f)
{
	return CVector3(x + f, y + f, z + f);
}
CVector3 CVector3::operator -(float f)
{
	return CVector3(x - f, y - f, z - f);
}
CVector3 CVector3::operator *(float f)
{
	return CVector3(x*f, y*f, z*f);
}
CVector3 CVector3::operator /(float f)
{
	float recip;
	if (f < 0.000001f)  f = 1.0f;
	recip = 1.0 / f;
	return CVector3(x*recip, y*recip, z*recip);
}
Vector addition / subtraction / multiplication / division with another Vector
void CVector3::operator +=(CVector3 Vect)
{
	x += Vect.x;
	y += Vect.y;
	z += Vect.z;
}
void CVector3::operator -=(CVector3 Vect)
{
	x -= Vect.x;
	y -= Vect.y;
	z -= Vect.z;
}
void CVector3::operator *=(CVector3 Vect)
{
	x *= Vect.x;
	y *= Vect.y;
	z *= Vect.z;
}
void CVector3::operator /=(CVector3 Vect)
{
	x /= Vect.x;
	y /= Vect.y;
	z /= Vect.z;
}
Vector addition / subtraction / multiplication / division with a scalar.
CVector3 CVector3::operator +=(float f)
{
	return CVector3(x + f, y + f, z + f);
}
CVector3 CVector3::operator -=(float f)
{
	return CVector3(x - f, y - f, z - f);
}
CVector3 CVector3::operator *=(float f)
{
	return CVector3(x*f, y*f, z*f);
}
CVector3 CVector3::operator /=(float f)
{
	float recip;
	if (f < 0.000001f)  f = 1.0f;
	recip = 1.0 / f;
	return CVector3(x*recip, y*recip, z*recip);
}
Magnitude(), Dot(), Cross(), and Normalize() Functions
float CVector3::Magnitude()
{
	return(sqrt((x*x) + (y*y) + (z*z)));
}
float CVector3::Dot(CVector3 Vect)
{
	return(x*Vect.x + y*Vect.y + z*Vect.z);
}
CVector3 CVector3::Cross(CVector3 Vector1, CVector3 Vector2)
{
	x = ((Vector1.y*Vector2.z) - (Vector1.z*Vector2.y));
	y = ((Vector1.z*Vector2.x) - (Vector1.x*Vector2.z));
	z = ((Vector1.x*Vector2.y) - (Vector1.y*Vector2.x));
}
void CVector3::Normalize()
{
	float magnitude;
	magnitude = Magnitude();
	if (magnitude < 0.0000001f) magnitude = 1.0f;
	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}
void CVector3::DivideVectorByScaler(CVector3 Vector1, float f)
{
	x = Vector1.x / f;
	y = Vector1.y / f;
	z = Vector1.z / f;
}