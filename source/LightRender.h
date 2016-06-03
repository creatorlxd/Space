#pragma once
#include<d3d9.h>
//
//
//
//
//

void SetAmbientLight(LPDIRECT3DDEVICE9 g_pd3dDevice, int r, int g, int b);//设置环境光
void SetSpecularLight(LPDIRECT3DDEVICE9 g_pd3dDevice);					  //设置镜面反射光

class Light																  //光源	
{
public:
	Light();
	~Light();
	

private:
	D3DLIGHT9 LightContent;



};