#include "stdafx.h"
#include "../Include/ComponentFactoryManager.h"

ComponentFactoryManager* ComponentFactoryManager::sm_pThis = nullptr;
ComponentFactoryManager g_ComponentFactoryManager;

ComponentFactoryManager::ComponentFactoryManager()
{
	sm_pThis = this;
}

ComponentFactoryManager::~ComponentFactoryManager()
{
	Release();
}

void ComponentFactoryManager::Release()
{
	if (sm_pThis == this)
	{
		sm_pThis = nullptr;
	}
}

ComponentFactoryManager * ComponentFactoryManager::GetMainManager()
{
	return sm_pThis;
}

void ComponentFactoryManager::SetAsMainManager()
{
	sm_pThis = this;
}

bool ComponentFactoryManager::AddComponentFactory(const std::string & name, std::function<Component*(void)> functor)
{
	if (m_Content.find(name) != m_Content.end())
	{
		ThrowError(L"已存在该组件工厂方法");
		return false;
	}
	m_Content.insert(make_pair(name, functor));
	return true;
}

bool ComponentFactoryManager::DeleteComponentFactory(const std::string & name)
{
	auto iter = m_Content.find(name);
	if (iter == m_Content.end())
	{
		ThrowError(L"没有该组件工厂方法");
		return false;
	}
	m_Content.erase(iter);
	return true;
}

std::function<Component*(void)> ComponentFactoryManager::FindComponentFactory(const std::string & name)
{
	auto iter = m_Content.find(name);
	if (iter != m_Content.end())
	{
		return iter->second;
	}
	else
		return std::function<Component*(void)>();
}
