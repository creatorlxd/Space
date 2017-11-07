/*
Copyright 2017 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "stdafx.h"
#include "../Include/Camera.h" 
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(CameraComponent);

SpaceGameEngine::CameraComponent* SpaceGameEngine::CameraComponent::sm_pThis = nullptr;

SpaceGameEngine::CameraComponent::CameraComponent()
{
	m_TypeName = "CameraComponent";
	m_IfRun = false;
	m_LookDirection = { 0,0,1 ,0};
	m_RightDirection = { 1,0,0 ,0};
	m_UpDirection = { 0,1,0 ,0};
	m_Position = { 0,0,0 ,1};
	m_Angle = XM_PIDIV4;
	m_NearZ = 1.0f;
	m_FarZ = 1000.0f;
	sm_pThis = this;
	m_pTransform = nullptr;
}

SpaceGameEngine::CameraComponent::~CameraComponent()
{
	Release();
}

void SpaceGameEngine::CameraComponent::Release()
{
	if (sm_pThis == this)
	{
		sm_pThis = nullptr;
	}
}

void SpaceGameEngine::CameraComponent::Start()
{
	InitTransform();
}

void SpaceGameEngine::CameraComponent::Run(float DeltaTime)
{
	SetAsMainCamera();
}

XMFLOAT4X4 SpaceGameEngine::CameraComponent::ComputeViewMatrix()
{
	if (m_pTransform == nullptr)
	{
		ThrowError(L"缺少Transform组件");
		return XMFLOAT4X4();
	}
	m_Position = XMFLOAT4(m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, m_pTransform->GetPosition().z,1.0f);
	m_LookDirection = { 0,0,1,0 };
	RotationLookDirection(m_pTransform->GetRotation());

	XMFLOAT4X4 re;
	XMVECTOR vbuff;
	vbuff = XMLoadFloat4(&m_LookDirection);
	vbuff = XMVector3Normalize(vbuff);
	XMStoreFloat4(&m_LookDirection, vbuff);
	vbuff = XMVector3Cross(XMVectorSet(0, 1.0f, 0, 0), XMLoadFloat4(&m_LookDirection));
	vbuff = XMVector3Normalize(vbuff);
	XMStoreFloat4(&m_RightDirection, vbuff);
	vbuff = XMVector3Cross(XMLoadFloat4(&m_LookDirection), XMLoadFloat4(&m_RightDirection));
	vbuff = XMVector3Normalize(vbuff);
	XMStoreFloat4(&m_UpDirection, vbuff);

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
	re._41 = -1 * XMVectorGetX(XMVector3Dot(XMLoadFloat4(&m_Position), XMLoadFloat4(&m_RightDirection)));
	re._42 = -1 * XMVectorGetX(XMVector3Dot(XMLoadFloat4(&m_Position), XMLoadFloat4(&m_UpDirection)));
	re._43 = -1 * XMVectorGetX(XMVector3Dot(XMLoadFloat4(&m_Position), XMLoadFloat4(&m_LookDirection)));
	re._44 = 1;

	return re;
}

void SpaceGameEngine::CameraComponent::GoForward(float dis)
{
	XMVECTOR v1, v2;
	v1 = XMLoadFloat4(&m_Position);
	v2 = XMLoadFloat4(&m_LookDirection);
	v1 = v1 + dis*v2;
	XMStoreFloat4(&m_Position, v1);
	UpdatePosition();
}

void SpaceGameEngine::CameraComponent::GoUp(float dis)
{
	XMVECTOR v1, v2;
	XMFLOAT3 up(0, 1, 0);
	v1 = XMLoadFloat4(&m_Position);
	v2 = XMLoadFloat3(&up);
	v1 = v1 + dis*v2;
	XMStoreFloat4(&m_Position, v1);
	UpdatePosition();
}

void SpaceGameEngine::CameraComponent::GoRight(float dis)
{
	XMVECTOR v1, v2;
	v1 = XMLoadFloat4(&m_Position);
	v2 = XMLoadFloat4(&m_RightDirection);
	v1 = v1 + dis*v2;
	XMStoreFloat4(&m_Position, v1);
	UpdatePosition();
}

void SpaceGameEngine::CameraComponent::RotationLookDirection(XMFLOAT3 rotate)
{
	XMMATRIX mbuff = XMMatrixRotationY(rotate.y);
	XMMATRIX m = XMMatrixRotationX(rotate.x);
	XMVECTOR v = XMLoadFloat4(&m_LookDirection);
	m = m*mbuff;
	mbuff = XMMatrixRotationZ(rotate.z);
	m = m*mbuff;
	v = XMVector3Transform(v, m);
	XMStoreFloat4(&m_LookDirection, v);
}

void SpaceGameEngine::CameraComponent::SetAsMainCamera()
{
	sm_pThis = this;
}

CameraComponent * SpaceGameEngine::CameraComponent::GetMainCamera()
{
	return sm_pThis;
}

void SpaceGameEngine::CameraComponent::InitTransform()
{
	Component* cb = this;
	while(cb->GetTypeName()!=TransformComponent::NewComponent.m_Name)
	{
		cb = cb->GetFatherComponent();
		if (cb == nullptr)
		{
			ThrowError(L"缺少Transform组件");
			return;
		}
	}
	m_pTransform = dynamic_cast<TransformComponent*>(cb);
}

TransformComponent * SpaceGameEngine::CameraComponent::GetTransform()
{
	return m_pTransform;
}

float SpaceGameEngine::CameraComponent::GetAngle()
{
	return m_Angle;
}

void SpaceGameEngine::CameraComponent::SetAngle(float f)
{
	m_Angle = f;
}

float SpaceGameEngine::CameraComponent::GetNearZ()
{
	return m_NearZ;
}

void SpaceGameEngine::CameraComponent::SetNearZ(float f)
{
	m_NearZ = f;
}

float SpaceGameEngine::CameraComponent::GetFarZ()
{
	return m_FarZ;
}

void SpaceGameEngine::CameraComponent::SetFarZ(float f)
{
	m_FarZ = f;
}

void SpaceGameEngine::CameraComponent::UpdatePosition()
{
	if (m_pTransform == nullptr)
	{
		ThrowError(L"缺少Transform组件");
		return;
	}
	m_pTransform->SetPosition(XMFLOAT3(m_Position.x,m_Position.y,m_Position.z));
}
