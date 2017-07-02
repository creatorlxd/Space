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

#define STRING(str) #str

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

using tstring = std::conditional<std::is_same<TCHAR, char>::value, std::string, std::wstring>::type;

template <typename _T> void SafeRelease(_T& p) { if (p) { p->Release(); p = nullptr; } }

//-----------------------------------��FVF�����ʽ��---------------------------------------------

struct CUSTOMVERTEX //����ṹ��
{
	float x, y, z;	//��ά����
	float nx, ny, nz;//���㷨��������
	float u, v;		//��������
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)	//FVF�����ʽ

namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
	XMGLOBALCONST XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
}

//----------------------------------------------------------------------------------------------
tstring StringToTString(const std::string& str);				//stringתwstring,Ŀǰֻ֧��Ӣ��

std::string TStringToString(const tstring& tstr);				//wstringתstring,Ŀǰֻ֧��Ӣ��

void InitMaterialFromFile(D3DMATERIAL9 &Material, std::string filename);				//���ļ��г�ʼ������

void SetViewPort(LPDIRECT3DDEVICE9 g_pd3dDevice,DWORD width=800, DWORD height=600);												//�����ӿڱ仯

void OpenAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);											//����������Alpha�ں�
void CloseAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);										//�ر�Alpha�ں�

void OpenDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);									//������Ȼ���
void SetDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);									//������Ȼ���
void CloseDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);									//�ر���Ȼ���

float GetDeltaTime();																	//��ȡʱ����

//TODO:�����Ĵ���
void ThrowError(const tstring& errormessege);										//����

std::vector<std::pair<std::string, std::string> > ReadAssetListFromFile(const std::string& filename);	//���ļ��ж�ȡ�ʲ��ļ��б�
#endif