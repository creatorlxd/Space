#pragma once
#include "stdafx.h"
#ifndef SPACE
#define SPACE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }   //����һ����ȫ�ͷź꣬���ں���COM�ӿ�ָ����ͷ�

//-----------------------------------��FVF�����ʽ��---------------------------------------------

struct CUSTOMVERTEX //����ṹ��
{
	float x, y, z;	//��ά����
	float nx, ny, nz;//���㷨��������
	float u, v;		//��������
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)	//FVF�����ʽ

//----------------------------------------------------------------------------------------------



HRESULT Direct3D_Init(HWND hwnd, LPDIRECT3DDEVICE9       g_pd3dDevice, int WINDOW_HEIGHT, int WINDOW_WIDTH);//D3DX9��ʼ��

void InitMaterialFromFile(D3DMATERIAL9 &Material, std::string filename);									//���ļ��г�ʼ������

void OpenAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);																//����������Alpha�ں�
void CloseAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice);															//�ر�Alpha�ں�

void OpenDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//������Ȼ���
void SetDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//������Ȼ���
void CloseDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice);														//�ر���Ȼ���

#endif