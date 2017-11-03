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
#include "Game/Object/Include/ObjectManager.h"
using namespace SpaceGameEngine;

ObjectManager* SpaceGameEngine::ObjectManager::sm_pThis = nullptr;

SpaceGameEngine::ObjectManager::ObjectManager()
{
	sm_pThis = this;
}

SpaceGameEngine::ObjectManager::~ObjectManager()
{
	for (auto i : m_Content)
	{
		MemoryManager::Delete(i);
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
	sm_pThis->m_Content.push_back(re);
	return re;
}

bool SpaceGameEngine::ObjectManager::DeleteObject(Object * po)
{
	for (auto i = m_Content.begin(); i != m_Content.end(); i += 1)
	{
		if (*i == po)
		{
			MemoryManager::Delete(po);
			m_Content.erase(i);
			return true;
		}
	}
	return false;
}

void SpaceGameEngine::ObjectManager::Start()
{
	for (auto i : m_Content)
	{
		if (i->IfUse())
			i->Start();
	}
}

void SpaceGameEngine::ObjectManager::Run(float DeltaTime)
{
	for (auto i : m_Content)
	{
		if (i->IfUse() && i->IfRun())
			i->Run(DeltaTime);
	}
}

void SpaceGameEngine::ObjectManager::Release()
{
	for (auto i : m_Content)
	{
		MemoryManager::Delete(i);
	}
	m_Content.clear();
}
