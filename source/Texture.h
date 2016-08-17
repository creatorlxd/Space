#pragma once
#include"space.h"

void SetTextureFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, LPDIRECT3DTEXTURE9 & g_pTexture);
void SetTextureFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname,std::string filename,LPDIRECT3DTEXTURE9 &g_pTexture);
void TexturePrintInit(LPDIRECT3DDEVICE9 g_pd3dDevice);
void TexturePrintInitEx(LPDIRECT3DDEVICE9 g_pd3dDevice, int num = 8);