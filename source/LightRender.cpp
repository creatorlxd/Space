#include"LightRender.h"
#include<d3d9.h>



void SetAmbientLight(LPDIRECT3DDEVICE9 g_pd3dDevice, int r,int g, int b)	//设置环境光
{
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(r, g, b));
}

void SetSpecularLight(LPDIRECT3DDEVICE9 g_pd3dDevice)						//设置镜面反射光
{
	g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}

Light::Light()
{
	ZeroMemory(&m_LightContent, sizeof(m_LightContent));
}

Light::~Light()
{

}

void Light::SetPointLights()
{
}

void Light::SetDirectionaLights()
{
}

void Light::SetSpotLight()
{
}

void Light::BeginLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive)
{
}

void Light::EndLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive)
{
}
