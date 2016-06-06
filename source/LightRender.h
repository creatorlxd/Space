#pragma once
#include<d3d9.h>
//
//
//
//
//

void SetAmbientLight(LPDIRECT3DDEVICE9 g_pd3dDevice, int r, int g, int b);	//设置环境光
void SetSpecularLightOn(LPDIRECT3DDEVICE9 g_pd3dDevice);						//设置镜面反射光开启
void SetSpecularLightOff(LPDIRECT3DDEVICE9 g_pd3dDevice);						//设置镜面反射光关闭


class Light																	//光源	
{
public:
	Light();
	~Light();
	void SetPointLights();													//设置点光源
	void SetDirectionaLights();												//设置方向光源
	void SetSpotLight();													//设置聚光灯
	void BeginLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive);					//开始渲染光源
	void EndLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive);						//结束渲染光源
private:
	int m_LightNumber;
	D3DLIGHT9 m_LightContent;



};