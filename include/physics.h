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
	void GetTime();														//��ȡ�����ʱ����
	//---------------------------------------------------------------------------------------------------------------
	void SetXYZ(float x, float y, float z);								//��ʱ������������������ĺ���
	//---------------------------------------------------------------------------------------------------------------
	void InitPhysicsFromFile(const std::string& filename);						//���ļ��г�ʼ��������Ϣ
	void GetG();														//��������������������ӵ��ܺ�����
	void RunMovingEngine();											//���й����ƶ�����������
	void RunRoundingEngine();											//���й�����ת����������
private:
	float m_TimeNow;							//���ڵ�ʱ��
	float m_TimeChange;						//ʱ����ʱ��仯��
//----------------------------------------------------------------------------------------------------------------
	D3DVECTOR m_Position;						//�������ĵ�����
	float m_m;									//���������
	D3DVECTOR m_F;								//�������ܵ��ܵĺ���
	D3DVECTOR m_a;								//������ܵļ��ٶ�
	D3DVECTOR m_v;								//������ܵ��ٶ�
	D3DVECTOR m_I;								//�����ת������
	float m_rxv, m_ryv, m_rzv;					//�����XYZ�����ϵ���ת�ĽǶ�
	float m_rxa, m_rya, m_rza;					//�����XYZ�����ϵ���ת�ĽǶȵ�ÿ��ı仯��
};