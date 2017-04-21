#pragma once
#include "stdafx.h"
#include "Space.h"
#include "InputDevice.h"

class Camera								//摄像机
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
	void DirectionsNormalize();				//方向标准化
	void CalculateViewMatrix();				//计算取景矩阵
	void SetTargetPosition(const D3DXVECTOR3& target);	//设置目标位置
	void SetPosition(const D3DXVECTOR3& position);		//设置摄像机的位置
	void UseViewMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice);	//使用摄像机的取景变换的矩阵
	void SetProjectionMatrix(float fovy=D3DX_PI/4,float width=800 ,float height=600 ,float zn=1.0f,float zf=10000.00f);							//设置投影变换
	void UseProjectionMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice);	//使用投影变换的矩阵

	void MoveAlongXDirection(float units);						//沿X轴平移
	void MoveAlongYDirection(float units);						//沿Y轴平移
	void MoveAlongZDirection(float units);						//沿Z轴平移
	void MoveAlongRightDirection(float units);					//沿自己的X轴平移
	void MoveAlongUpDirection(float units);						//沿自己的Y轴平移
	void MoveAlongLookDirection(float units);					//沿自己的Z轴平移

	void RotationXDirection(float angle);						//沿X轴旋转
	void RotationYDirection(float angle);						//沿Y轴旋转
	void RotationZDirection(float angle);						//沿Z轴旋转
	void RotationRightDirection(float angle);					//沿自己的X轴旋转
	void RotationUpDirection(float angle);						//沿自己的Y轴旋转
	void RotationLookDirection(float angle);					//沿自己的Z轴旋转

private:
	KeyboardDevice& m_KeyBoardDevice;		//键盘设备
	MouseDevice& m_MouseDevice;				//鼠标设备
	D3DXVECTOR3 m_UpDirection, m_RightDirection, m_LookDirection;	//三轴方向向量
	D3DXMATRIX m_ViewMatrix;					//取景变换的矩阵
	D3DXMATRIX m_ProjectionMatrix;				//投影变换的矩阵
	D3DXVECTOR3 m_Position;					//摄像机的位置
	D3DXVECTOR3 m_TargetPosition;				//观察目标的位置
};