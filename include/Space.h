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

//-----------------------------------��FVF�����ʽ��---------------------------------------------

struct CUSTOMVERTEX //����ṹ��
{
	float x, y, z;	//��ά����
	float nx, ny, nz;//���㷨��������
	float u, v;		//��������
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)	//FVF�����ʽ

//----------------------------------------------------------------------------------------------

void InitMaterialFromFile(D3DMATERIAL9 &Material, std::string filename);									//���ļ��г�ʼ������

void OpenAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);																//����������Alpha�ں�
void CloseAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);															//�ر�Alpha�ں�

void OpenDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//������Ȼ���
void SetDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//������Ȼ���
void CloseDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//�ر���Ȼ���

#endif