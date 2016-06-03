#pragma once
#include<d3d9.h>
//
//
//
//
//

void SetAmbientLight(LPDIRECT3DDEVICE9 g_pd3dDevice, int r, int g, int b);	//���û�����
void SetSpecularLight(LPDIRECT3DDEVICE9 g_pd3dDevice);						//���þ��淴���

class Light																	//��Դ	
{
public:
	Light();
	~Light();
	void SetPointLights();													//���õ��Դ
	void SetDirectionaLights();												//���÷����Դ
	void SetSpotLight();													//���þ۹��
	void BeginLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive);					//��ʼ��Ⱦ��Դ
	void EndLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive);						//������Ⱦ��Դ
private:
	D3DLIGHT9 m_LightContent;



};