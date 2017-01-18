#include "stdafx.h"
#include "LightRender.h"




void SetAmbientLight(LPDIRECT3DDEVICE9 g_pd3dDevice, int r,int g, int b)	//���û�����
{
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(r, g, b));
}

void SetSpecularLightOn(LPDIRECT3DDEVICE9 g_pd3dDevice)						//���þ��淴��⿪��
{
	g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}

void SetSpecularLightOff(LPDIRECT3DDEVICE9 g_pd3dDevice)						//���þ��淴���ر�
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
	m_LightContent.Diffuse = D3DXCOLOR(r, g, b, a);	//��Դ����������ɫֵ
	file >> r >> g >> b >> a;
	m_LightContent.Specular = D3DXCOLOR(r, g, b, a);//��Դ�ľ��淴����ɫֵ
	file >> r >> g >> b >> a;
	m_LightContent.Ambient = D3DXCOLOR(r, g, b, a);//��Դ�Ļ�������ɫֵ
	

	float x, y, z;
	file >> x >> y >> z;
	m_LightContent.Position = D3DXVECTOR3(x, y, z);	//��Դ��λ��
	file >> x >> y >> z;
	m_LightContent.Direction = D3DXVECTOR3(x, y, z);//��Դ�Ĺ��շ���

	file >> buffer;
	m_LightContent.Range = buffer;					//��Դ�Ĺ��շ�Χ
	file >> buffer;
	m_LightContent.Attenuation0 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��0
	file >> buffer;
	m_LightContent.Attenuation1 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��1
	file >> buffer;
	m_LightContent.Attenuation2 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��2
	file >> buffer;
	m_LightContent.Falloff = buffer;				//�۹�ƹ�Դ���ڹ�׶�����Ĺ���ǿ�������׶���ڲ�˥���ķ�ʽ��ͨ����Ϊ1.0fʹ����ǿ����������׶��ƽ���ع���
	file >> buffer;
	m_LightContent.Theta = buffer;					//�۹�ƹ�Դ�Ĺ�׶���ں˻���
	file >> buffer;
	m_LightContent.Phi = buffer;					//�۹�ƹ�Դ�Ĺ�׶����˻���

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
	m_LightContent.Diffuse = D3DXCOLOR(r, g, b, a);	//��Դ����������ɫֵ
	file >> r >> g >> b >> a;
	m_LightContent.Specular = D3DXCOLOR(r, g, b, a);//��Դ�ľ��淴����ɫֵ
	file >> r >> g >> b >> a;
	m_LightContent.Ambient = D3DXCOLOR(r, g, b, a);//��Դ�Ļ�������ɫֵ


	float x, y, z;
	file >> x >> y >> z;
	m_LightContent.Position = D3DXVECTOR3(x, y, z);	//��Դ��λ��
	file >> x >> y >> z;
	m_LightContent.Direction = D3DXVECTOR3(x, y, z);//��Դ�Ĺ��շ���

	file >> buffer;
	m_LightContent.Range = buffer;					//��Դ�Ĺ��շ�Χ
	file >> buffer;
	m_LightContent.Attenuation0 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��0
	file >> buffer;
	m_LightContent.Attenuation1 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��1
	file >> buffer;
	m_LightContent.Attenuation2 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��2
	file >> buffer;
	m_LightContent.Falloff = buffer;				//�۹�ƹ�Դ���ڹ�׶�����Ĺ���ǿ�������׶���ڲ�˥���ķ�ʽ��ͨ����Ϊ1.0fʹ����ǿ����������׶��ƽ���ع���
	file >> buffer;
	m_LightContent.Theta = buffer;					//�۹�ƹ�Դ�Ĺ�׶���ں˻���
	file >> buffer;
	m_LightContent.Phi = buffer;					//�۹�ƹ�Դ�Ĺ�׶����˻���

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
	m_LightContent.Diffuse = D3DXCOLOR(r, g, b, a);	//��Դ����������ɫֵ
	file >> r >> g >> b >> a;
	m_LightContent.Specular = D3DXCOLOR(r, g, b, a);//��Դ�ľ��淴����ɫֵ
	file >> r >> g >> b >> a;
	m_LightContent.Ambient = D3DXCOLOR(r, g, b, a);//��Դ�Ļ�������ɫֵ


	float x, y, z;
	file >> x >> y >> z;
	m_LightContent.Position = D3DXVECTOR3(x, y, z);	//��Դ��λ��
	file >> x >> y >> z;
	m_LightContent.Direction = D3DXVECTOR3(x, y, z);//��Դ�Ĺ��շ���

	file >> buffer;
	m_LightContent.Range = buffer;					//��Դ�Ĺ��շ�Χ
	file >> buffer;
	m_LightContent.Attenuation0 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��0
	file >> buffer;
	m_LightContent.Attenuation1 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��1
	file >> buffer;
	m_LightContent.Attenuation2 = buffer;			//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��2
	file >> buffer;
	m_LightContent.Falloff = buffer;				//�۹�ƹ�Դ���ڹ�׶�����Ĺ���ǿ�������׶���ڲ�˥���ķ�ʽ��ͨ����Ϊ1.0fʹ����ǿ����������׶��ƽ���ع���
	file >> buffer;
	m_LightContent.Theta = buffer;					//�۹�ƹ�Դ�Ĺ�׶���ں˻���
	file >> buffer;
	m_LightContent.Phi = buffer;					//�۹�ƹ�Դ�Ĺ�׶����˻���

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
