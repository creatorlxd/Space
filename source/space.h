#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<time.h>
#ifndef SPACE
#define SPACE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }   //定义一个安全释放宏，便于后面COM接口指针的释放

//-----------------------------------【FVF顶点格式】---------------------------------------------

struct CUSTOMVERTEX //顶点结构体
{
	float x, y, z;	//三维坐标
	float nx, ny, nz;//顶点法向量坐标
	float u, v;		//纹理坐标
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)	//FVF灵活顶点格式

//----------------------------------------------------------------------------------------------



HRESULT Direct3D_Init(HWND hwnd, LPDIRECT3DDEVICE9       g_pd3dDevice, int WINDOW_HEIGHT, int WINDOW_WIDTH);
#endif