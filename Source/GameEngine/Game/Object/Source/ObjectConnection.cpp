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
#include "../Include/ObjectConnection.h"

using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(ConnectComponent);

SpaceGameEngine::ConnectComponent::ConnectComponent()
{
	m_TypeName = STRING(ConnectComponent);
	m_pFatherTransform = nullptr;
	m_pChildTransform = nullptr;
	m_IfInit = false;
	ConnectComponent::m_pFatherObject = nullptr;
	m_pChildObject = nullptr;
}

void SpaceGameEngine::ConnectComponent::Run(float DeltaTime)
{
	if (m_IfInit == false)
		ThrowError("ConnectComponent需要先SetObject");
	else
	{
		if (ConnectComponent::m_pFatherObject&&m_pChildObject)
		{
			if (ConnectComponent::m_pFatherObject->GetComponentByMessage(Event::TransformDelete)==nullptr)
			{
				if (m_pFatherTransform&&m_pChildTransform)
				{
					if (ConnectComponent::m_pFatherObject->GetComponentByMessage(Event::PositionChange) ||
						ConnectComponent::m_pFatherObject->GetComponentByMessage(Event::RotationChange) ||
						ConnectComponent::m_pFatherObject->GetComponentByMessage(Event::ScaleChange))
					{
						m_pChildTransform->SetPosition(Add(m_pChildTransform->GetPosition(), Substract(m_pFatherTransform->GetPosition(), m_PositionBuffer)));
						m_pChildTransform->SetScale(Add(m_pChildTransform->GetScale(), Substract(m_pFatherTransform->GetScale(), m_ScaleBuffer)));
						if (m_pFatherTransform->GetFatherObject()->GetComponentByMessage(Event::RotationChange))
						{
							auto dis = Substract(m_pChildTransform->GetPosition(), m_pFatherTransform->GetPosition());
							auto angle = Substract(m_pFatherTransform->GetRotation(), m_RotationBuffer);
							dis = RotationVector(angle, dis);
							m_pChildTransform->SetPosition(Add(dis, m_pFatherTransform->GetPosition()));
							m_pChildTransform->SetRotation(Add(m_pChildTransform->GetRotation(), angle));
						}
						m_PositionBuffer = m_pFatherTransform->GetPosition();
						m_RotationBuffer = m_pFatherTransform->GetRotation();
						m_ScaleBuffer = m_pFatherTransform->GetScale();
					}
					
				}
				else
				{
					if (ConnectComponent::m_pFatherObject->GetComponentByMessage(Event::TransformAdd))
					{
						m_pFatherTransform = ConnectComponent::m_pFatherObject->GetComponent<TransformComponent>();
						m_pChildTransform = m_pChildObject->GetComponent<TransformComponent>();
					}
				}
			}
			else
			{
				m_pFatherTransform = nullptr;
				m_pChildTransform = nullptr;
			}
		}
	}
}

void SpaceGameEngine::ConnectComponent::SetObject(Object* father, Object* child)
{
	if (father&&child)
	{
		ConnectComponent::m_pFatherObject = father;
		m_pChildObject = child;
		m_pFatherTransform = father->GetComponent<TransformComponent>();
		m_pChildTransform = child->GetComponent<TransformComponent>();
		if (father)
		{
			m_PositionBuffer = m_pFatherTransform->GetPosition();
			m_RotationBuffer = m_pFatherTransform->GetRotation();
			m_ScaleBuffer = m_pFatherTransform->GetScale();
		}
		m_IfInit = true;
	}
	else
		ThrowError("father&child object can not be nullptr");
}

void SpaceGameEngine::ConnectObject(Object * father, Object * child)
{
	child->Attach(father);
	child->AddComponent(ConnectComponent::NewComponent());
	child->GetComponent<ConnectComponent>()->SetObject(father, child);
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
