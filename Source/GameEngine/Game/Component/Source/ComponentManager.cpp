#include "stdafx.h"
#include "../Include/ComponentManager.h"
using namespace SpaceGameEngine;

ComponentManager* SpaceGameEngine::ComponentManager::sm_pThis = nullptr;
namespace SpaceGameEngine 
{
	ComponentFactoryManager g_ComponentFactoryManager;
}

SpaceGameEngine::ComponentManager::ComponentManager()
{
	sm_pThis = this;
}

SpaceGameEngine::ComponentManager::~ComponentManager()
{
	for (auto i : m_Content)
	{
		MemoryManager::Delete(i);
	}
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

ComponentManager * SpaceGameEngine::ComponentManager::GetMainManager()
{
	return sm_pThis;
}

void SpaceGameEngine::ComponentManager::SetAsMainManager()
{
	sm_pThis = this;
}

bool SpaceGameEngine::ComponentManager::DeleteComponent(Component * pc)
{
	for (auto i = m_Content.begin(); i != m_Content.end(); i += 1)
	{
		if (*i == pc)
		{
			MemoryManager::Delete(pc);
			m_Content.erase(i);
			return true;
		}
	}
	return false;
}

void SpaceGameEngine::ComponentManager::Release()
{
	for (auto i : m_Content)
	{
		MemoryManager::Delete(i);
	}
	m_Content.clear();
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

Component * SpaceGameEngine::ComponentManager::NewComponentByName(const std::string & name)
{
	std::function<Component*(void)> f = g_ComponentFactoryManager.FindComponentFactory(name);
	return f();
}
