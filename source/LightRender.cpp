#include "stdafx.h"
#include "LightRender.h"




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

Light::Light(int &num)
{
	ZeroMemory(&m_LightContent, sizeof(m_LightContent));
	m_LightNumber = num;
	num += 1;
}

Light::~Light()
{

}

void Light::SetLightNumber(int & i)
{
	m_LightNumber = i;
	i += 1;
}

void Light::SetLightNumber(int&& i)
{
	m_LightNumber = i;
}
void Light::SetLightPosition(float x, float y, float z)
{
	m_LightContent.Position = D3DXVECTOR3(x, y, z);
}

void Light::SetLightDirection(float x, float y, float z)
{
	m_LightContent.Direction = D3DXVECTOR3(x, y, z);
}

void Light::SetPointLightsFromFile(const std::string& filename)
{
	m_LightContent.Type = D3DLIGHT_POINT;
	std::fstream file;
	file.open(filename, std::ios::in);
	float r, g, b, a;
	float buffer;
	file >> r >> g >> b >> a;
	m_LightContent.Diffuse = D3DXCOLOR(r, g, b, a);	//光源的漫反射颜色值
	file >> r >> g >> b >> a;
	m_LightContent.Specular = D3DXCOLOR(r, g, b, a);//光源的镜面反射颜色值
	file >> r >> g >> b >> a;
	m_LightContent.Ambient = D3DXCOLOR(r, g, b, a);//光源的环境光颜色值
	

	float x, y, z;
	file >> x >> y >> z;
	m_LightContent.Position = D3DXVECTOR3(x, y, z);	//光源的位置
	file >> x >> y >> z;
	m_LightContent.Direction = D3DXVECTOR3(x, y, z);//光源的光照方向

	file >> buffer;
	m_LightContent.Range = buffer;					//光源的光照范围
	file >> buffer;
	m_LightContent.Attenuation0 = buffer;			//光源的光亮强度的衰减系数0
	file >> buffer;
	m_LightContent.Attenuation1 = buffer;			//光源的光亮强度的衰减系数1
	file >> buffer;
	m_LightContent.Attenuation2 = buffer;			//光源的光亮强度的衰减系数2
	file >> buffer;
	m_LightContent.Falloff = buffer;				//聚光灯光源的内光锥的外侧的光亮强度向外光锥的内侧衰减的方式，通常设为1.0f使光亮强度在两个光锥间平滑地过渡
	file >> buffer;
	m_LightContent.Theta = buffer;					//聚光灯光源的光锥的内核弧度
	file >> buffer;
	m_LightContent.Phi = buffer;					//聚光灯光源的光锥的外核弧度

	file.close();
}

void Light::SetDirectionalLightsFromFile(const std::string& filename)
{
	m_LightContent.Type = D3DLIGHT_DIRECTIONAL;
	std::fstream file;
	file.open(filename, std::ios::in);
	float r, g, b, a;
	float buffer;
	file >> r >> g >> b >> a;
	m_LightContent.Diffuse = D3DXCOLOR(r, g, b, a);	//光源的漫反射颜色值
	file >> r >> g >> b >> a;
	m_LightContent.Specular = D3DXCOLOR(r, g, b, a);//光源的镜面反射颜色值
	file >> r >> g >> b >> a;
	m_LightContent.Ambient = D3DXCOLOR(r, g, b, a);//光源的环境光颜色值


	float x, y, z;
	file >> x >> y >> z;
	m_LightContent.Position = D3DXVECTOR3(x, y, z);	//光源的位置
	file >> x >> y >> z;
	m_LightContent.Direction = D3DXVECTOR3(x, y, z);//光源的光照方向

	file >> buffer;
	m_LightContent.Range = buffer;					//光源的光照范围
	file >> buffer;
	m_LightContent.Attenuation0 = buffer;			//光源的光亮强度的衰减系数0
	file >> buffer;
	m_LightContent.Attenuation1 = buffer;			//光源的光亮强度的衰减系数1
	file >> buffer;
	m_LightContent.Attenuation2 = buffer;			//光源的光亮强度的衰减系数2
	file >> buffer;
	m_LightContent.Falloff = buffer;				//聚光灯光源的内光锥的外侧的光亮强度向外光锥的内侧衰减的方式，通常设为1.0f使光亮强度在两个光锥间平滑地过渡
	file >> buffer;
	m_LightContent.Theta = buffer;					//聚光灯光源的光锥的内核弧度
	file >> buffer;
	m_LightContent.Phi = buffer;					//聚光灯光源的光锥的外核弧度

	file.close();
}

void Light::SetSpotLightsFromFile(const std::string& filename)
{
	m_LightContent.Type = D3DLIGHT_SPOT;
	std::fstream file;
	file.open(filename, std::ios::in);
	float r, g, b, a;
	float buffer;
	file >> r >> g >> b >> a;
	m_LightContent.Diffuse = D3DXCOLOR(r, g, b, a);	//光源的漫反射颜色值
	file >> r >> g >> b >> a;
	m_LightContent.Specular = D3DXCOLOR(r, g, b, a);//光源的镜面反射颜色值
	file >> r >> g >> b >> a;
	m_LightContent.Ambient = D3DXCOLOR(r, g, b, a);//光源的环境光颜色值


	float x, y, z;
	file >> x >> y >> z;
	m_LightContent.Position = D3DXVECTOR3(x, y, z);	//光源的位置
	file >> x >> y >> z;
	m_LightContent.Direction = D3DXVECTOR3(x, y, z);//光源的光照方向

	file >> buffer;
	m_LightContent.Range = buffer;					//光源的光照范围
	file >> buffer;
	m_LightContent.Attenuation0 = buffer;			//光源的光亮强度的衰减系数0
	file >> buffer;
	m_LightContent.Attenuation1 = buffer;			//光源的光亮强度的衰减系数1
	file >> buffer;
	m_LightContent.Attenuation2 = buffer;			//光源的光亮强度的衰减系数2
	file >> buffer;
	m_LightContent.Falloff = buffer;				//聚光灯光源的内光锥的外侧的光亮强度向外光锥的内侧衰减的方式，通常设为1.0f使光亮强度在两个光锥间平滑地过渡
	file >> buffer;
	m_LightContent.Theta = buffer;					//聚光灯光源的光锥的内核弧度
	file >> buffer;
	m_LightContent.Phi = buffer;					//聚光灯光源的光锥的外核弧度

	file.close();
}

void Light::RegisterLight(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetLight(m_LightNumber, &m_LightContent);
}

void Light::BeginLightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->LightEnable(m_LightNumber, true);
}

void Light::EndLightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->LightEnable(m_LightNumber, false);
}

int Light::GetLightNumber()
{
	return m_LightNumber;
}
