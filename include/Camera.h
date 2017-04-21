#pragma once
#include "stdafx.h"
#include "Space.h"
#include "InputDevice.h"

class Camera								//�����
{
public:
	Camera(KeyboardDevice& keyboard,MouseDevice& mouse)
		:m_KeyBoardDevice(keyboard),m_MouseDevice(mouse),
		m_Position(D3DXVECTOR3(0.00f,0.00f,0.00f)),
		m_LookDirection(D3DXVECTOR3(1,0,0)),m_UpDirection(D3DXVECTOR3(0,1,0)),m_RightDirection(D3DXVECTOR3(0,0,1)),
		m_ViewMatrix(D3DXMATRIX{1,0,0,0,
								0,1,0,0,
								0,0,1,0,
								0,0,0,1}),
		m_ProjectionMatrix(D3DXMATRIX{ 1,0,0,0,
									   0,1,0,0,
									   0,0,1,0,
									   0,0,0,1 }),
		m_TargetPosition(D3DXVECTOR3(0,0,0))
	{}
	~Camera();
	void DirectionsNormalize();				//�����׼��
	void CalculateViewMatrix();				//����ȡ������
	void SetTargetPosition(const D3DXVECTOR3& target);	//����Ŀ��λ��
	void SetPosition(const D3DXVECTOR3& position);		//�����������λ��
	void UseViewMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice);	//ʹ���������ȡ���任�ľ���
	void SetProjectionMatrix(float fovy=D3DX_PI/4,float width=800 ,float height=600 ,float zn=1.0f,float zf=10000.00f);							//����ͶӰ�任
	void UseProjectionMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice);	//ʹ��ͶӰ�任�ľ���

	void MoveAlongXDirection(float units);						//��X��ƽ��
	void MoveAlongYDirection(float units);						//��Y��ƽ��
	void MoveAlongZDirection(float units);						//��Z��ƽ��
	void MoveAlongRightDirection(float units);					//���Լ���X��ƽ��
	void MoveAlongUpDirection(float units);						//���Լ���Y��ƽ��
	void MoveAlongLookDirection(float units);					//���Լ���Z��ƽ��

	void RotationXDirection(float angle);						//��X����ת
	void RotationYDirection(float angle);						//��Y����ת
	void RotationZDirection(float angle);						//��Z����ת
	void RotationRightDirection(float angle);					//���Լ���X����ת
	void RotationUpDirection(float angle);						//���Լ���Y����ת
	void RotationLookDirection(float angle);					//���Լ���Z����ת

private:
	KeyboardDevice& m_KeyBoardDevice;		//�����豸
	MouseDevice& m_MouseDevice;				//����豸
	D3DXVECTOR3 m_UpDirection, m_RightDirection, m_LookDirection;	//���᷽������
	D3DXMATRIX m_ViewMatrix;					//ȡ���任�ľ���
	D3DXMATRIX m_ProjectionMatrix;				//ͶӰ�任�ľ���
	D3DXVECTOR3 m_Position;					//�������λ��
	D3DXVECTOR3 m_TargetPosition;				//�۲�Ŀ���λ��
};