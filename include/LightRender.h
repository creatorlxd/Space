#pragma once
#include "stdafx.h"
#include "space.h"
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
	Light(int &num);
	~Light();
	D3DLIGHT9 m_LightContent;												//光源的具体内容
	void SetLightNumber(int &i);											//设置光源序号
	void SetLightPosition(float x,float y,float z);							//设置光源位置
	void SetLightDirection(float x, float y, float z);						//设置光源的光照方向
	void SetPointLightsFromFile(const std::string& filename);													//设置点光源
	void SetDirectionalLightsFromFile(const std::string& filename);												//设置方向光源
	void SetSpotLightsFromFile(const std::string& filename);													//设置聚光灯
	void RegisterLight(LPDIRECT3DDEVICE9 g_pd3dDevice);						//注册光源
	void BeginLightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//开始渲染光源
	void EndLightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);						//结束渲染光源
private:
	int m_LightNumber;														//光源的ID
													
	//D3DCOLORVALUE m_LightContentDiffuse;									//光源的漫反射颜色值
	//D3DCOLORVALUE m_LightContentSpecular;									//光源的镜面反射颜色值
	//D3DCOLORVALUE m_LightContentAmbient;									//光源的环境光颜色值
	//D3DVECTOR m_LightContentPosition;										//光源的位置
	//D3DVECTOR m_LightContentDirection;										//光源的光照方向
	//float m_LightContentRange;												//光源的光照范围
	//float m_LightContentAttenuation0;										//光源的光亮强度的衰减系数0
	//float m_LightContentAttenuation1;										//光源的光亮强度的衰减系数1
	//float m_LightContentAttenuation2;										//光源的光亮强度的衰减系数2
	//float m_LightContentFalloff;											//聚光灯光源的内光锥的外侧的光亮强度向外光锥的内侧衰减的方式，通常设为1.0f使光亮强度在两个光锥间平滑地过渡
	//float m_LightContentTheta;												//聚光灯光源的光锥的内核弧度
	//float m_LightContentPhi;												//聚光灯光源的光锥的外核弧度




};