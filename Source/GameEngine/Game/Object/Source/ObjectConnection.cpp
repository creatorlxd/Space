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
#include "../Include/ObjectConnection.h"

using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(ConnectComponent);

SpaceGameEngine::ConnectComponent::ConnectComponent()
{
	m_TypeName = STRING(ConnectComponent);
	m_pFatherTransform = nullptr;
	m_pChildTransform = nullptr;
	m_IfInit = false;
}

void SpaceGameEngine::ConnectComponent::Run(float DeltaTime)
{
	if (m_IfInit == false)
		ThrowError("ConnectComponent需要先SetTransform");
	else
	{
		if (m_pFatherTransform->GetFatherObject()->GetComponentByMessage(Event::PositionChange) ||
			m_pFatherTransform->GetFatherObject()->GetComponentByMessage(Event::RotationChange) ||
			m_pFatherTransform->GetFatherObject()->GetComponentByMessage(Event::ScaleChange))
		{
			m_pChildTransform->SetPosition(Add(m_pChildTransform->GetPosition(),Substract(m_pFatherTransform->GetPosition(),m_PositionBuffer)));
			m_pChildTransform->SetRotation(Add(m_pChildTransform->GetRotation(), Substract(m_pFatherTransform->GetRotation(), m_RotationBuffer)));
			m_pChildTransform->SetScale(Add(m_pChildTransform->GetScale(), Substract(m_pFatherTransform->GetScale(), m_ScaleBuffer)));
			m_PositionBuffer = m_pFatherTransform->GetPosition();
			m_RotationBuffer = m_pFatherTransform->GetRotation();
			m_ScaleBuffer = m_pFatherTransform->GetScale();
		}
	}
}

void SpaceGameEngine::ConnectComponent::SetTransform(TransformComponent * father, TransformComponent * child)
{
	m_pFatherTransform = father;
	m_pChildTransform = child;
	if (father)
	{
		m_PositionBuffer = father->GetPosition();
		m_RotationBuffer = father->GetRotation();
		m_ScaleBuffer = father->GetScale();
	}
	m_IfInit = true;
}

void SpaceGameEngine::ConnectObject(Object * father, Object * child)
{
	child->Attach(father);
	child->AddComponent(ConnectComponent::NewComponent());
	child->GetComponent<ConnectComponent>()->SetTransform(father->GetComponent<TransformComponent>(), child->GetComponent<TransformComponent>());
	if (child->GetRootComponent() != nullptr)
	{
		child->GetRootComponent()->Attach(child->GetComponent(STRING(ConnectComponent)));
		child->SetRootComponent(STRING(ConnectComponent));
	}
	else
		ThrowError("RootComponent不能为nullptr");
}

void SpaceGameEngine::DisconObject(Object * child)
{
	if (child == nullptr)
	{
		ThrowError("child参数不能为nullptr");
		return;
	}
	if (child->GetRootComponent()->GetTypeName() != STRING(ConnectComponent))
	{
		ThrowError("DisconObject必须对应ConnectObject使用||使用ConnectObject的对象的RootComponent必须为ConnectComponent");
		return;
	}
	child->Discon();
	auto children_component = child->GetRootComponent()->GetChildrenComponent();
	if (children_component.size() >= 1)
	{
		child->SetRootComponent(children_component[0]->GetTypeName());
	}
	child->DeleteComponent(STRING(ConnectComponent));
}
