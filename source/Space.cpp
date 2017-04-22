#include "stdafx.h"
#include "Space.h"

void InitMaterialFromFile(D3DMATERIAL9 &Material, std::string filename)
{
	std::fstream file;
	file.open(filename, std::ios::in);
	float r, g, b, a;				//均介于0.0~~1.0之间
	file >> r >> g >> b >> a;
	Material.Ambient = D3DXCOLOR(r, g, b, a);		//反射环境光的颜色值
	file >> r >> g >> b >> a;
	Material.Diffuse = D3DXCOLOR(r, g, b, a);		//漫反射的颜色值
	file >> r >> g >> b >> a;
	Material.Specular = D3DXCOLOR(r, g, b, a);		//镜面反射的颜色值
	file >> r >> g >> b >> a;
	Material.Emissive = D3DXCOLOR(r, g, b, a);		//自发光的颜色值

	float Power;
	file >> Power;
	Material.Power = Power;

	file.close();
}

void SetViewPort(LPDIRECT3DDEVICE9 g_pd3dDevice, DWORD width, DWORD height)
{
	D3DVIEWPORT9 vp = { 0,0,width,height,0,1 };
	g_pd3dDevice->SetViewport(&vp);
}

void OpenAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}

void CloseAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void OpenDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, true);
}

void SetDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void CloseDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
}

float GetTimeChange()
{
	static float TimeNow=0.00f;
	static float TimeBuffer = 0.00f;
	static float TimeChange = 0.00f;
	if (TimeNow == 0.00f)
	{
		TimeNow = timeGetTime()*0.001f;
		return GetTimeChange();
	}
	else
	{
		TimeBuffer = timeGetTime()*0.001f;
		TimeChange = TimeBuffer - TimeNow;
		TimeNow = timeGetTime()*0.001f;
		return TimeChange;
	}
}
