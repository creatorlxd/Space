#pragma once
#include<d3d9.h>
//
//
//
//
//

void SetAmbientLight(LPDIRECT3DDEVICE9 g_pd3dDevice, int r, int g, int b);//���û�����
void SetSpecularLight(LPDIRECT3DDEVICE9 g_pd3dDevice);					  //���þ��淴���

class Light																  //��Դ	
{
public:
	Light();
	~Light();
	

private:
	D3DLIGHT9 LightContent;



};