#pragma once
#include"Graphics.h"
//----------------physics-const-number-----------------
#define g 9.8f

//-----------------------------------------------------
D3DVECTOR operator + (D3DVECTOR v1, D3DVECTOR v2);
D3DVECTOR operator * (D3DVECTOR v1, float f);
D3DVECTOR operator / (D3DVECTOR v1, float f);


//-----------------------------------------------------
class PhysicsComponent
{
public:
	friend class GraphicsComponent;
	PhysicsComponent();
	void GetTime();														//获取或更新时间间隔
	//---------------------------------------------------------------------------------------------------------------
	void SetXYZ(float x, float y, float z);								//临时的设置物体质心坐标的函数
	//---------------------------------------------------------------------------------------------------------------
	void InitPhysicsFromFile(const std::string& filename);						//从文件中初始化物理信息
	void GetG();														//获得物体的重力，并将其加到总合力中
	void RunMovingEngine();											//运行关于移动的物理引擎
	void RunRoundingEngine();											//运行关于旋转的物理引擎
private:
	float m_TimeNow;							//现在的时间
	float m_TimeChange;						//时间差，即时间变化量
//----------------------------------------------------------------------------------------------------------------
	D3DVECTOR m_Position;						//物体质心的坐标
	float m_m;									//物体的质量
	D3DVECTOR m_F;								//物体所受的总的合力
	D3DVECTOR m_a;								//物体的总的加速度
	D3DVECTOR m_v;								//物体的总的速度
	D3DVECTOR m_I;								//物体的转动惯量
	float m_rxv, m_ryv, m_rzv;					//物体的XYZ三轴上的旋转的角度
	float m_rxa, m_rya, m_rza;					//物体的XYZ三轴上的旋转的角度的每秒的变化量
};