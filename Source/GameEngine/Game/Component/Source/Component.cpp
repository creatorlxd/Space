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
#include "../Include/Component.h"
using namespace SpaceGameEngine;

SpaceGameEngine::Component::Component()
{
	m_TypeName = "NullType";
	m_IfRun = true;
	m_IfUse = true;
	m_pFather = nullptr;
	m_pFatherObject = nullptr;
	m_Mode = 0;
	m_pAsset = nullptr;
}

SpaceGameEngine::Component::~Component()
{
	
}

std::string SpaceGameEngine::Component::GetTypeName()
{
	return m_TypeName;
}

Component * SpaceGameEngine::Component::GetFatherComponent()
{
	return m_pFather;
}

void SpaceGameEngine::Component::SetFatherComponent(Component * pc)
{
	m_pFather = pc;
}

void SpaceGameEngine::Component::AddChildComponent(Component * pc)
{
	m_Children.push_back(pc);
}

bool SpaceGameEngine::Component::DeleteChildComponent(Component * pc)
{
	auto result = std::find(m_Children.begin(), m_Children.end(),pc);
	if (result == m_Children.end())
	{
		ThrowError(L"没有该子组件");
		return false;
	}
	m_Children.erase(result);
	return true;
}

Component * SpaceGameEngine::Component::FindChildComponent(const std::string & name)
{
	std::queue<Component*> q;
	for (auto i : m_Children)
	{
		q.push(i);
	}
	while (!q.empty())
	{
		auto i = q.front();
		q.pop();
		if (i->GetTypeName() == name)
		{
			return i;
		}
		else
		{
			for (auto j : i->GetChildrenComponent())
			{
				q.push(j);
			}
		}
	}
	return nullptr;
}

Component * SpaceGameEngine::Component::FindFatherComponent(const std::string & name)
{
	auto cb = this;
	while (cb != nullptr&&cb->GetTypeName() != name)
	{
		cb = cb->GetFatherComponent();
	}
	return cb;
}

Vector<Component*>& SpaceGameEngine::Component::GetChildrenComponent()
{
	return m_Children;
}

void SpaceGameEngine::Component::InitFromFile(const std::string& filename, int mode)
{

}

void SpaceGameEngine::Component::Start()
{

}

void SpaceGameEngine::Component::Run(float DeltaTime)
{

}

void SpaceGameEngine::Component::EveryFrameCleanUp()
{

}

void SpaceGameEngine::Component::Attach(Component * pc)
{
	if (pc)
	{
		m_pFather = pc;
		pc->AddChildComponent(this);
	}
	else
	{
		ThrowError(L"不能将一个组件链向一个空指针");
		return;
	}
}

void SpaceGameEngine::Component::Clear()
{
	m_Children.clear();
	m_IfRun = true;
	m_IfUse = true;
	m_pFather = nullptr;
	m_pFatherObject = nullptr;
	m_Mode = 0;
	m_pAsset = nullptr;
}

bool SpaceGameEngine::Component::IfRun()
{
	return m_IfRun;
}

bool SpaceGameEngine::Component::IfUse()
{
	return m_IfUse;
}

void SpaceGameEngine::Component::ChangeIfRun(bool b)
{
	m_IfRun = b;
}

void SpaceGameEngine::Component::ChangeIfUse(bool b)
{
	m_IfUse = b;
}

void SpaceGameEngine::Component::SetFatherObject(Object * po)
{
	m_pFatherObject = po;
}

Object * SpaceGameEngine::Component::GetFatherObject()
{
	return m_pFatherObject;
}

void SpaceGameEngine::Component::SetMode(int m)
{
	m_Mode = m;
}

int SpaceGameEngine::Component::GetMode()
{
	return m_Mode;
}

const Asset* SpaceGameEngine::Component::GetAsset()
{
	return m_pAsset;
}
