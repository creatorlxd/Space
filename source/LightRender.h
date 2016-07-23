#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include"space.h"
#include<string>
//
//
//
//
//

void SetAmbientLight(LPDIRECT3DDEVICE9 g_pd3dDevice, int r, int g, int b);	//���û�����
void SetSpecularLightOn(LPDIRECT3DDEVICE9 g_pd3dDevice);						//���þ��淴��⿪��
void SetSpecularLightOff(LPDIRECT3DDEVICE9 g_pd3dDevice);						//���þ��淴���ر�


class Light																	//��Դ	
{
public:
	Light();
	Light(int &num);
	~Light();
	D3DLIGHT9 m_LightContent;												//��Դ�ľ�������
	void SetPointLightsFromFile(std::string filename);													//���õ��Դ
	void SetDirectionaLightsFromFile(std::string filename);												//���÷����Դ
	void SetSpotLightFromFile(std::string filename);													//���þ۹��
	void BeginLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive);					//��ʼ��Ⱦ��Դ
	void EndLightPrint(LPDIRECT3DDEVICE9 g_pd3dDecive);						//������Ⱦ��Դ
private:
	int m_LightNumber;														//��Դ��ID
													
	//D3DCOLORVALUE m_LightContentDiffuse;									//��Դ����������ɫֵ
	//D3DCOLORVALUE m_LightContentSpecular;									//��Դ�ľ��淴����ɫֵ
	//D3DCOLORVALUE m_LightContentAmbient;									//��Դ�Ļ�������ɫֵ
	//D3DVECTOR m_LightContentPosition;										//��Դ��λ��
	//D3DVECTOR m_LightContentDirection;										//��Դ�Ĺ��շ���
	//float m_LightContentRange;												//��Դ�Ĺ��շ�Χ
	//float m_LightContentAttenuation0;										//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��0
	//float m_LightContentAttenuation1;										//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��1
	//float m_LightContentAttenuation2;										//��Դ�Ĺ���ǿ�ȵ�˥��ϵ��2
	//float m_LightContentFalloff;											//�۹�ƹ�Դ���ڹ�׶�����Ĺ���ǿ�������׶���ڲ�˥���ķ�ʽ��ͨ����Ϊ1.0fʹ����ǿ����������׶��ƽ���ع���
	//float m_LightContentTheta;												//�۹�ƹ�Դ�Ĺ�׶���ں˻���
	//float m_LightContentPhi;												//�۹�ƹ�Դ�Ĺ�׶����˻���




};