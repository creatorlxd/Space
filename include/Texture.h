#pragma once
#include"space.h"

void SetTextureFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, LPDIRECT3DTEXTURE9 & g_pTexture);//���ļ���ʼ������
void SetTextureFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname,const std::string& filename,LPDIRECT3DTEXTURE9 &g_pTexture);//SetTextureFromFile��������
void TexturePrintInit(LPDIRECT3DDEVICE9 g_pd3dDevice);//�������״̬�ĳ�ʼ��
void TexturePrintInitEx(LPDIRECT3DDEVICE9 g_pd3dDevice);//TexturePrintInit��������