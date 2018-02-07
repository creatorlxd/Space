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
#include "Game/Object/Include/ObjectManager.h"
using namespace SpaceGameEngine;

ObjectManager* SpaceGameEngine::ObjectManager::sm_pThis = nullptr;

SpaceGameEngine::ObjectManager::ObjectManager()
{
	sm_pThis = this;
}

SpaceGameEngine::ObjectManager::~ObjectManager()
{
	if (m_FreeIndexList.size() == m_Content.size())
	{

	}
	else
	{
		for (auto i : m_Content)
		{
			if (i)
				MemoryManager::Delete(i);
		}
	}
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

ObjectManager * SpaceGameEngine::ObjectManager::GetMainManager()
{
	return sm_pThis;
}

void SpaceGameEngine::ObjectManager::SetAsMainManager()
{
	sm_pThis = this;
}

Object * SpaceGameEngine::ObjectManager::NewObject()
{
	if (sm_pThis == nullptr)
	{
		ThrowError(L"需要先定义一个对象管理器");
		return nullptr;
	}
	auto re = MemoryManager::New<Object>();
	if (!sm_pThis->m_FreeIndexList.empty())
	{
		sm_pThis->m_Content[sm_pThis->m_FreeIndexList.front()] = re;
		sm_pThis->m_FreeIndexList.pop();
	}
	else
		sm_pThis->m_Content.push_back(re);
	return re;
}

void SpaceGameEngine::ObjectManager::DestoryObject(Object * po)
{
	if (po == nullptr)
	{
		ThrowError("can not delete nullptr");
		return;
	}
	if (sm_pThis)
	{
		if (!sm_pThis->DeleteObject(po))
			ThrowError("do not have this object");
	}
	else
		ThrowError("当前未设定对象管理器");
}

bool SpaceGameEngine::ObjectManager::DeleteObject(Object * po)
{
	for (unsigned int i = 0; i < m_Content.size(); i++)
	{
		if (m_Content[i] == po)
		{
			if (po->IfChild() && po->GetFatherObject())
			{
				po->GetFatherObject()->DeleteChildObject(po);
			}
			if (!po->GetChildren().empty())
			{
				for (auto i : po->GetChildren())
					i->SetFatherObject(nullptr);
			}
			po->Clear();
			MemoryManager::Delete(po);
			m_FreeIndexList.push(i);
			m_Content[i] = nullptr;
			return true;
		}
	}
	return false;
}

void SpaceGameEngine::ObjectManager::Start()
{
	for (auto i : m_Content)
	{
		if (i)
			if (i->IfUse())
				i->Start();
	}
}

void SpaceGameEngine::ObjectManager::Run(float DeltaTime)
{
	for (auto i : m_Content)
	{
		if (i)
			if (i->IfUse() && i->IfRun() && (!i->IfChild()))
				i->Run(DeltaTime);
	}
	for (auto i : m_Content)
	{
		if (i)
			if (i->IfUse() && i->IfRun())
				i->EveryFrameCleanUp();
	}
}

void SpaceGameEngine::ObjectManager::Clear()
{
	if (m_FreeIndexList.size() == m_Content.size())
	{

	}
	else
	{
		for (auto i : m_Content)
		{
			if (i)
				MemoryManager::Delete(i);
		}
	}
	m_Content.clear();
	m_FreeIndexList = Queue<unsigned int>();
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

Object * SpaceGameEngine::CloneObject(Object * po)
{
	Queue<std::pair<Component*, Component*>> que;		//first of the pair : component in src ; second : component in dist
	if (po->GetRootComponent())
	{
		Object* re = ObjectManager::NewObject();
		Component* droot = CloneComponent(po->GetRootComponent());
		re->AddComponent(droot);
		re->SetRootComponent(droot->GetTypeName());
		que.push(std::make_pair(po->GetRootComponent(), droot));
		while (!que.empty())
		{
			auto pair = que.front();
			que.pop();
			Component* src = pair.first;
			Component* dis = pair.second;

			if (src->GetChildrenComponent().empty() || src->GetTypeName() == "InformationComponent")
				continue;
			else
			{
				auto container = src->GetChildrenComponent();
				for (auto i = container.begin(); i != container.end(); i++)
				{
					if ((*i)->GetTypeName() == "InformationComponent")
						continue;
					Component* cbuff = CloneComponent(*i);
					re->AddComponent(cbuff);
					cbuff->Attach(dis);
					que.push(std::make_pair(*i, cbuff));
				}
			}
		}

		return re;
	}
	else
	{
		ThrowError("Object need root component");
		return nullptr;
	}
}
