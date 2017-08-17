#include "stdafx.h"
#include "../Include/Camera.h" 
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(CameraComponent);

SpaceGameEngine::CameraComponent* SpaceGameEngine::CameraComponent::sm_pThis = nullptr;

SpaceGameEngine::CameraComponent::CameraComponent()
{
	m_TypeName = "CameraComponent";
	m_IfRun = false;
	m_LookDirection = { 0,0,1 };
	m_RightDirection = { 1,0,0 };
	m_UpDirection = { 0,1,0 };
	m_Position = { 0,0,0 };
	sm_pThis = this;
}

SpaceGameEngine::CameraComponent::~CameraComponent()
{
	Release();
}

void SpaceGameEngine::CameraComponent::InitFromFile(const std::string & filename, int mode)
{
	std::fstream file(filename, std::ios::in);
	file >> m_Position.x >> m_Position.y >> m_Position.z;
	file >> m_LookDirection.x >> m_LookDirection.y >> m_LookDirection.z;
	file.close();
}

void SpaceGameEngine::CameraComponent::Release()
{
	if (sm_pThis == this)
	{
		sm_pThis = nullptr;
	}
}

void SpaceGameEngine::CameraComponent::Run(float DeltaTime)
{
	SetAsMainCamera();
}

void SpaceGameEngine::CameraComponent::SetPosition(XMFLOAT3 pos)
{
	m_Position = pos;
}

void SpaceGameEngine::CameraComponent::SetLookDirection(XMFLOAT3 dir)
{
	m_LookDirection = dir;
}

XMFLOAT3 SpaceGameEngine::CameraComponent::GetPosition()
{
	return m_Position;
}

XMFLOAT3 SpaceGameEngine::CameraComponent::GetLookDirection()
{
	return m_LookDirection;
}

XMFLOAT4X4 SpaceGameEngine::CameraComponent::ComputeViewMatrix()
{
	XMFLOAT4X4 re;
	XMVECTOR vbuff;
	vbuff = XMLoadFloat3(&m_LookDirection);
	vbuff = XMVector3Normalize(vbuff);
	XMStoreFloat3(&m_LookDirection, vbuff);
	vbuff = XMVector3Cross(XMVectorSet(0, 1.0f, 0, 1), XMLoadFloat3(&m_LookDirection));
	vbuff = XMVector3Normalize(vbuff);
	XMStoreFloat3(&m_RightDirection, vbuff);
	vbuff = XMVector3Cross(XMLoadFloat3(&m_LookDirection), XMLoadFloat3(&m_RightDirection));
	vbuff = XMVector3Normalize(vbuff);
	XMStoreFloat3(&m_UpDirection, vbuff);

	re._11 = m_RightDirection.x;
	re._12 = m_UpDirection.x;
	re._13 = m_LookDirection.x;
	re._14 = 0;
	re._21 = m_RightDirection.y;
	re._22 = m_UpDirection.y;
	re._23 = m_LookDirection.y;
	re._24 = 0;
	re._31 = m_RightDirection.z;
	re._32 = m_UpDirection.z;
	re._33 = m_LookDirection.z;
	re._34 = 0;
	re._41 = -1 * XMVectorGetX(XMVector3Dot(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_RightDirection)));
	re._42 = -1 * XMVectorGetX(XMVector3Dot(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_UpDirection)));
	re._43 = -1 * XMVectorGetX(XMVector3Dot(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_LookDirection)));
	re._44 = 1;

	return re;
}

void SpaceGameEngine::CameraComponent::SetAsMainCamera()
{
	sm_pThis = this;
}

CameraComponent * SpaceGameEngine::CameraComponent::GetMainCamera()
{
	return sm_pThis;
}
