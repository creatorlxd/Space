#include "stdafx.h"
#include "../Include/ComponentManager.h"

ComponentManager* ComponentManager::sm_pThis = nullptr;

ComponentManager::ComponentManager()
{
	sm_pThis = this;
}

ComponentManager::~ComponentManager()
{
	for (auto i : m_Content)
	{
		delete i;
	}
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

ComponentManager * ComponentManager::GetMainManager()
{
	return sm_pThis;
}

void ComponentManager::SetAsMainManager()
{
	sm_pThis = this;
}

bool ComponentManager::DeleteComponent(Component * pc)
{
	for (auto i = m_Content.begin(); i != m_Content.end(); i += 1)
	{
		if (*i == pc)
		{
			delete pc;
			m_Content.erase(i);
			return true;
		}
	}
	return false;
}

void ComponentManager::Release()
{
	for (auto i : m_Content)
	{
		delete i;
	}
	m_Content.clear();
}