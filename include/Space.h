#pragma once
#include "stdafx.h"
#ifndef SPACE
#define SPACE

#ifdef _UNICODE
#define tcin wcin
#define tfstream wfstream
#else
#define tcin cin
#define tfstream fstream
#endif

using tstring = std::conditional<std::is_same<TCHAR, char>::value, std::string, std::wstring>::type;

template <typename _T> void SafeRelease(_T& p) { if (p) { p->Release(); p = nullptr; } }

//-----------------------------------【FVF顶点格式】---------------------------------------------

struct CUSTOMVERTEX //顶点结构体
{
	float x, y, z;	//三维坐标
	float nx, ny, nz;//顶点法向量坐标
	float u, v;		//纹理坐标
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)	//FVF灵活顶点格式

//----------------------------------------------------------------------------------------------

void InitMaterialFromFile(D3DMATERIAL9 &Material, std::string filename);									//从文件中初始化材质

void OpenAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);																//开启并设置Alpha融合
void CloseAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);															//关闭Alpha融合

void OpenDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//开启深度缓存
void SetDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//设置深度缓存
void CloseDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//关闭深度缓存

#endif