#pragma once
#include "stdafx.h"
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



HRESULT Direct3D_Init(HWND hwnd, LPDIRECT3DDEVICE9       g_pd3dDevice, int WINDOW_HEIGHT, int WINDOW_WIDTH);//D3DX9初始化

void InitMaterialFromFile(D3DMATERIAL9 &Material, std::string filename);									//从文件中初始化材质

void OpenAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);																//开启并设置Alpha融合
void CloseAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);															//关闭Alpha融合

void OpenDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//开启深度缓存
void SetDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//设置深度缓存
void CloseDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//关闭深度缓存

#endif