#include "stdafx.h"
#include "physics.h"

D3DVECTOR operator + (D3DVECTOR v1, D3DVECTOR v2)
{
	D3DVECTOR r;
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;
	return r;
}
D3DVECTOR operator * (D3DVECTOR v1, float f)
{
	D3DVECTOR r;
	r = v1;
	r.x *= f;
	r.y *= f;
	r.z *= f;
	return r;
}
D3DVECTOR operator / (D3DVECTOR v1, float f)
{
	D3DVECTOR r;
	r = v1;
	r.x /= f;
	r.y /= f;
	r.z /= f;
	return r;
}