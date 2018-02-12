/*
Copyright 2018 creatorlxd

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

	if (m_Mode&ForRenderingMode)
	{
		if (m_pFatherObject->GetRenderObject() == nullptr)
		{
			m_pFatherObject->SetRenderObject(RenderSystem::GetMainRenderSystem()->NewRenderObject());
			m_pFatherObject->GetRenderObject()->m_Type = RenderObjectType::Model;
			m_pFatherObject->GetRenderObject()->m_pObject = m_pFatherObject;
		}
	}
}

void SpaceGameEngine::TransformComponent::Start()
{
	if(m_pFatherObject)
		m_pFatherObject->ProduceMessage(this, Event::TransformAdd);
	if (m_Mode&ForRenderingMode)
	{
		if (m_pFatherObject->GetRenderObject()->m_IfHaveTransform == false)
		{
			m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Position = m_Position;
			m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Rotation = m_Rotation;
			m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Scale = m_Scale;
			m_pFatherObject->GetRenderObject()->m_IfHaveTransform = true;
		}
	}
}

void SpaceGameEngine::TransformComponent::Run(float DeltaTime)
{
	if (m_Mode&ForRenderingMode)
	{
		m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Position = m_Position;
		m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Rotation = m_Rotation;
		m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Scale = m_Scale;
	}
}

void SpaceGameEngine::TransformComponent::CleanUp()
{
	if (m_pFatherObject)
		m_pFatherObject->ProduceMessage(this, Event::TransformDelete);
	if (m_Mode&ForRenderingMode)
	{
		if (m_pFatherObject)
		{
			if (m_pFatherObject->GetRenderObject())
			{
				RenderSystem::GetMainRenderSystem()->DeleteRenderObject(m_pFatherObject->GetRenderObject());
				m_pFatherObject->SetRenderObject(nullptr);
			}
		}
	}
}

void SpaceGameEngine::TransformComponent::Copy(Component * pc)
{
	if (pc)
	{
		if (pc->GetTypeName() == m_TypeName)
		{
			auto src = dynamic_cast<TransformComponent*>(pc);
			m_Mode = src->m_Mode;
			m_pAsset = src->m_pAsset;
			m_Position = src->m_Position;
			m_Rotation = src->m_Rotation;
			m_Scale = src->m_Scale;
			if ((m_Mode&ForRenderingMode)&&m_pFatherObject->GetRenderObject())
			{
				m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Position = m_Position;
				m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Rotation = m_Rotation;
				m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Scale = m_Scale;
				m_pFatherObject->GetRenderObject()->m_IfHaveTransform = true;
			}
		}
		else
		{
			ThrowError("dst's type must equal to src's type");
			return;
		}
	}
	else
		ThrowError("component can not be nullptr");
}

void SpaceGameEngine::TransformComponent::SetPosition(const XMFLOAT3 & position)
{
	if (m_pFatherObject&&position != m_Position)
	{
		m_pFatherObject->ProduceMessage(this,Event::PositionChange);
	}
	m_Position = position;
}

void SpaceGameEngine::TransformComponent::SetRotation(const XMFLOAT3 & rotation)
{
	if (m_pFatherObject&&rotation != m_Rotation)
	{
		m_pFatherObject->ProduceMessage(this, Event::RotationChange);
	}
	m_Rotation = rotation;
}

void SpaceGameEngine::TransformComponent::SetScale(const XMFLOAT3 & scale)
{
	if (m_pFatherObject&&scale != m_Scale)
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
