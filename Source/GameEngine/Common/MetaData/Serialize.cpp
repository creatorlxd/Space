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
#include "Serialize.h"

SpaceGameEngine::SerializeObjectManager::~SerializeObjectManager()
{
	for (auto i : m_QueryList)
	{
		THROW_ERROR("all objects which were referred by the serialized pointer must also be serialized");
	}
}

SpaceGameEngine::SerializeObjectManager::SerializeObjectManager()
{

}

void SpaceGameEngine::SerializeObjectManager::AddObject(void * ptr, void* now_ptr)
{
	m_ObjectMap[ptr] = now_ptr;

	//deal with the query of this ptr
	auto iter = m_QueryList.find(ptr);
	if (iter != m_QueryList.end())
	{
		for (auto& i : iter->second)
		{
			if(i)
				*i = now_ptr;
		}
		m_QueryList.erase(iter);
	}
}

void SpaceGameEngine::SerializeObjectManager::QueryObject(void * query_ptr, void ** ptr)
{
	auto iter1 = m_ObjectMap.find(query_ptr);
	if (iter1 != m_ObjectMap.end())
	{
		if (ptr)
			*ptr = iter1->second;
	}
	else
	{
		m_QueryList[query_ptr].push_back(ptr);
	}
}

SpaceGameEngine::SerializeObjectManager & SpaceGameEngine::GetSerializeObjectManager()
{
	static GlobalVariable<SerializeObjectManager> g_SerializeObjectManager;
	return g_SerializeObjectManager.Get();
}

SpaceGameEngine::SerializeInterface::SerializeInterface(IOFlag ioflag)
{
	m_IOFlag = ioflag;
}

SpaceGameEngine::SerializeInterface::~SerializeInterface()
{

}

SpaceGameEngine::SerializeInterface::IOFlag SpaceGameEngine::SerializeInterface::GetIOFlag()
{
	return m_IOFlag;
}