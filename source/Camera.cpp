#include "stdafx.h"
#include "Camera.h"

Camera::~Camera()
{
}

void Camera::DirectionsNormalize()
{
	D3DXVec3Normalize(&m_LookDirection, &m_LookDirection);
	D3DXVec3Normalize(&m_UpDirection, &m_UpDirection);
	D3DXVec3Normalize(&m_RightDirection, &m_RightDirection);

	D3DXVec3Cross(&m_UpDirection, &m_LookDirection, &m_RightDirection);
	D3DXVec3Cross(&m_RightDirection, &m_UpDirection, &m_LookDirection);
	D3DXVec3Cross(&m_LookDirection, &m_RightDirection, &m_UpDirection);		//TODO:这是我自己加的，可能有错

	D3DXVec3Normalize(&m_LookDirection, &m_LookDirection);
	D3DXVec3Normalize(&m_UpDirection, &m_UpDirection);
	D3DXVec3Normalize(&m_RightDirection, &m_RightDirection);
}

void Camera::CalculateViewMatrix()
{
	DirectionsNormalize();

	m_ViewMatrix._11 = m_RightDirection.x;
	m_ViewMatrix._12 = m_UpDirection.x;
	m_ViewMatrix._13 = m_LookDirection.x;
	m_ViewMatrix._14 = 0.00f;

	m_ViewMatrix._21 = m_RightDirection.y;
	m_ViewMatrix._22 = m_UpDirection.y;
	m_ViewMatrix._23 = m_LookDirection.y;
	m_ViewMatrix._24 = 0.00f;

	m_ViewMatrix._31 = m_RightDirection.z;
	m_ViewMatrix._32 = m_UpDirection.z;
	m_ViewMatrix._33 = m_LookDirection.z;
	m_ViewMatrix._34 = 0.00f;

	m_ViewMatrix._41 = -D3DXVec3Dot(&m_RightDirection, &m_Position);
	m_ViewMatrix._42 = -D3DXVec3Dot(&m_UpDirection, &m_Position);
	m_ViewMatrix._43 = -D3DXVec3Dot(&m_LookDirection, &m_Position);
	m_ViewMatrix._44 = 1.00f;
}

void Camera::SetTargetPosition(const D3DXVECTOR3 & target)
{
	m_TargetPosition = target;

	m_LookDirection = m_TargetPosition - m_Position;
	DirectionsNormalize();
}

void Camera::SetPosition(const D3DXVECTOR3 & position)
{
	m_Position = position;
}

void Camera::UseViewMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
}

void Camera::SetProjectionMatrix(float fovy, float width, float height, float zn, float zf)
{
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, fovy, (float)((double)width / height), zn, zf);
}

void Camera::UseProjectionMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_ProjectionMatrix);
}

void Camera::MoveAlongXDirection(float units)
{
	m_Position += D3DXVECTOR3(units, 0, 0);
	m_TargetPosition+= D3DXVECTOR3(units, 0, 0);
}

void Camera::MoveAlongYDirection(float units)
{
	m_Position += D3DXVECTOR3(0, units, 0);
	m_TargetPosition += D3DXVECTOR3(0, units, 0);
}

void Camera::MoveAlongZDirection(float units)
{
	m_Position += D3DXVECTOR3(0, 0, units);
	m_TargetPosition += D3DXVECTOR3(0, 0, units);
}

void Camera::MoveAlongRightDirection(float units)
{
	m_Position += m_RightDirection*units;
	m_TargetPosition+= m_RightDirection*units;
}

void Camera::MoveAlongUpDirection(float units)
{
	m_Position += m_UpDirection*units;
	m_TargetPosition += m_UpDirection*units;
}

void Camera::MoveAlongLookDirection(float units)
{
	m_Position += m_LookDirection*units;
	m_TargetPosition += m_LookDirection*units;
}

void Camera::RotationXDirection(float angle)
{
	D3DXMATRIX r;
	D3DXMatrixRotationX(&r, angle);

	D3DXVec3TransformCoord(&m_RightDirection, &m_RightDirection, &r);
	D3DXVec3TransformCoord(&m_UpDirection, &m_UpDirection, &r);
	D3DXVec3TransformCoord(&m_LookDirection, &m_LookDirection, &r);

	D3DXVECTOR3 buff = m_TargetPosition - m_Position;
	m_TargetPosition = m_Position+m_LookDirection * D3DXVec3Length(&buff);
}

void Camera::RotationYDirection(float angle)
{
	D3DXMATRIX r;
	D3DXMatrixRotationY(&r, angle);

	D3DXVec3TransformCoord(&m_RightDirection, &m_RightDirection, &r);
	D3DXVec3TransformCoord(&m_UpDirection, &m_UpDirection, &r);
	D3DXVec3TransformCoord(&m_LookDirection, &m_LookDirection, &r);

	D3DXVECTOR3 buff = m_TargetPosition - m_Position;
	m_TargetPosition = m_Position + m_LookDirection * D3DXVec3Length(&buff);
}

void Camera::RotationZDirection(float angle)
{
	D3DXMATRIX r;
	D3DXMatrixRotationZ(&r, angle);

	D3DXVec3TransformCoord(&m_RightDirection, &m_RightDirection, &r);
	D3DXVec3TransformCoord(&m_UpDirection, &m_UpDirection, &r);
	D3DXVec3TransformCoord(&m_LookDirection, &m_LookDirection, &r);

	D3DXVECTOR3 buff = m_TargetPosition - m_Position;
	m_TargetPosition = m_Position + m_LookDirection * D3DXVec3Length(&buff);
}

void Camera::RotationRightDirection(float angle)
{
	D3DXMATRIX r;
	D3DXMatrixRotationAxis(&r, &m_RightDirection,angle);

	D3DXVec3TransformCoord(&m_UpDirection, &m_UpDirection, &r);
	D3DXVec3TransformCoord(&m_LookDirection, &m_LookDirection, &r);

	D3DXVECTOR3 buff = m_TargetPosition - m_Position;
	m_TargetPosition = m_Position + m_LookDirection * D3DXVec3Length(&buff);
}

void Camera::RotationUpDirection(float angle)
{
	D3DXMATRIX r;
	D3DXMatrixRotationAxis(&r, &m_UpDirection,angle);

	D3DXVec3TransformCoord(&m_RightDirection, &m_RightDirection, &r);
	D3DXVec3TransformCoord(&m_LookDirection, &m_LookDirection, &r);

	D3DXVECTOR3 buff = m_TargetPosition - m_Position;
	m_TargetPosition = m_Position + m_LookDirection * D3DXVec3Length(&buff);
}

void Camera::RotationLookDirection(float angle)
{
	D3DXMATRIX r;
	D3DXMatrixRotationAxis(&r,&m_LookDirection, angle);

	D3DXVec3TransformCoord(&m_RightDirection, &m_RightDirection, &r);
	D3DXVec3TransformCoord(&m_UpDirection, &m_UpDirection, &r);

	D3DXVECTOR3 buff = m_TargetPosition - m_Position;
	m_TargetPosition = m_Position + m_LookDirection * D3DXVec3Length(&buff);
}

void Camera::Run(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	CalculateViewMatrix();
	UseViewMatrix(g_pd3dDevice);
	UseProjectionMatrix(g_pd3dDevice);
}
