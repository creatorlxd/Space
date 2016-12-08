#pragma once
#include<d3d9.h>
#include<d3dx9.h>

//----------------physics-const-number-----------------
#define g 9.8f

//-----------------------------------------------------
D3DVECTOR operator + (D3DVECTOR v1, D3DVECTOR v2);
D3DVECTOR operator * (D3DVECTOR v1, float f);
D3DVECTOR operator / (D3DVECTOR v1, float f);