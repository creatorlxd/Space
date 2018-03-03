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
#include "..\Include\GlobalVariable.h"

SpaceGameEngine::GlobalVariableTagClass::~GlobalVariableTagClass()
{

}

void SpaceGameEngine::GlobalVariableTagClass::Release()
{

}

SpaceGameEngine::GlobalVariableManager::~GlobalVariableManager()
{
	Release();
}

SpaceGameEngine::GlobalVariableManager::GlobalVariableManager()
{
	m_IfReleased = false;
}

void SpaceGameEngine::GlobalVariableManager::Insert(GlobalVariableTagClass * ptr)
{
	m_Content.push(ptr);
}

void SpaceGameEngine::GlobalVariableManager::Release()
{
	if (!m_IfReleased)
	{
		while (!m_Content.empty())
		{
			m_Content.top()->Release();
			m_Content.pop();
		}
		m_IfReleased = true;
	}
}

SpaceGameEngine::GlobalVariableManager & SpaceGameEngine::GetGlobalVariableManager()
{
	static GlobalVariableManager g_GlobalVariableManager;
	return g_GlobalVariableManager;
}
