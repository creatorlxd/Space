#include"LightRender.h"





void SetAmbientLight(LPDIRECT3DDEVICE9 g_pd3dDevice, int r,int g, int b)	//设置环境光
{
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(r, g, b));
}

void SetSpecularLightOn(LPDIRECT3DDEVICE9 g_pd3dDevice)						//设置镜面反射光开启
{
	g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}

void SetSpecularLightOff(LPDIRECT3DDEVICE9 g_pd3dDevice)						//设置镜面反射光关闭
{
	g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, false);
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
	m_LightContent.Type = D3DLIGHT_POINT;
	
}

void Light::SetDirectionaLights()
{
	m_LightContent.Type = D3DLIGHT_DIRECTIONAL;

}

void Light::SetSpotLight()
{
	m_LightContent.Type = D3DLIGHT_SPOT;

}

void Light::BeginLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive)
{
}

void Light::EndLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive)
{
}
