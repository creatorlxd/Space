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
#include "../Include/Transform.h" 
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(TransformComponent);

SpaceGameEngine::TransformComponent::TransformComponent()
{
	m_TypeName = "TransformComponent";
	m_Position = { 0,0,0 };
	m_Rotation = { 0,0,0 };
	m_Scale = { 1,1,1 };
}

SpaceGameEngine::TransformComponent::~TransformComponent()
{

}

void SpaceGameEngine::TransformComponent::InitFromFile(const std::string & filename, int mode)
{
	m_Mode = mode;
	
	const TransformAsset* ta = ReadAssetFromFile<TransformAsset>(filename);
	m_Position = ta->m_Position;
	m_Rotation = ta->m_Rotation;
	m_Scale = ta->m_Scale;
}

void SpaceGameEngine::TransformComponent::Run(float DeltaTime)
{
	if (m_Mode&ForRenderingMode)
	{
		XMMATRIX mrebuff, mbuff;
		mbuff = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		mrebuff = mbuff;
		mbuff = XMMatrixRotationX(m_Rotation.x);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixRotationY(m_Rotation.y);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixRotationZ(m_Rotation.z);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);

		auto inversetransposemat = InverseTransposeMatrix(mrebuff);

		XMMATRIX result = mrebuff*XMLoadFloat4x4(&SceneData::m_ViewMatrix)*XMLoadFloat4x4(&SceneData::m_ProjectionMatrix);
		SpaceEngineWindow->GetEffectShader().m_pWorldViewProjMatrix->SetMatrix(reinterpret_cast<float*>(&result));
		SpaceEngineWindow->GetEffectShader().m_pInverseTransposeMatrix->SetMatrix(reinterpret_cast<float*>(&inversetransposemat));
	}
}

void SpaceGameEngine::TransformComponent::SetPosition(const XMFLOAT3 & position)
{
	if (m_pFatherObject)
	{
		m_pFatherObject->ProduceMessage(this,Event::PositionChange);
	}
	m_Position = position;
}

void SpaceGameEngine::TransformComponent::SetRotation(const XMFLOAT3 & rotation)
{
	if (m_pFatherObject)
	{
		m_pFatherObject->ProduceMessage(this, Event::RotationChange);
	}
	m_Rotation = rotation;
}

void SpaceGameEngine::TransformComponent::SetScale(const XMFLOAT3 & scale)
{
	if (m_pFatherObject)
	{
		m_pFatherObject->ProduceMessage(this, Event::ScaleChange);
	}
	m_Scale = scale;
}

XMFLOAT3 SpaceGameEngine::TransformComponent::GetPosition()
{
	return m_Position;
}

XMFLOAT3 SpaceGameEngine::TransformComponent::GetRotation()
{
	return m_Rotation;
}

XMFLOAT3 SpaceGameEngine::TransformComponent::GetScale()
{
	return m_Scale;
}
