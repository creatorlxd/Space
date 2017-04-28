#pragma once
#include"space.h"

void SetTextureFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, LPDIRECT3DTEXTURE9 & g_pTexture);//从文件初始化纹理
void SetTextureFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname,const std::string& filename,LPDIRECT3DTEXTURE9 &g_pTexture);//SetTextureFromFile的升级版
void TexturePrintInit(LPDIRECT3DDEVICE9 g_pd3dDevice);//纹理绘制状态的初始化
void TexturePrintInitEx(LPDIRECT3DDEVICE9 g_pd3dDevice);//TexturePrintInit的升级版