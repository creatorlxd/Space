#include "stdafx.h"
#include "../Include/ComponentFactoryManager.h"
using namespace SpaceGameEngine;

ComponentFactoryManager* SpaceGameEngine::ComponentFactoryManager::sm_pThis = nullptr;

SpaceGameEngine::ComponentFactoryManager::ComponentFactoryManager()
{
	sm_pThis = this;
}

SpaceGameEngine::ComponentFactoryManager::~ComponentFactoryManager()
{
	Release();
}

void SpaceGameEngine::ComponentFactoryManager::Release()
{
	if (sm_pThis == this)
	{
		sm_pThis = nullptr;
	}
}

ComponentFactoryManager * SpaceGameEngine::ComponentFactoryManager::GetMainManager()
{
	return sm_pThis;
}

void SpaceGameEngine::ComponentFactoryManager::SetAsMainManager()
{
	sm_pThis = this;
}

bool SpaceGameEngine::ComponentFactoryManager::AddComponentFactory(const std::string & name, std::function<Component*(void)> functor)
{
	if (m_Content.find(name) != m_Content.end())
	{
		ThrowError(L"已存在该组件工厂方法");
		return false;
	}
	m_Content.insert(make_pair(name, functor));
	return true;
}

bool SpaceGameEngine::ComponentFactoryManager::DeleteComponentFactory(const std::string & name)
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

std::function<Component*(void)> SpaceGameEngine::ComponentFactoryManager::FindComponentFactory(const std::string & name)
{
	auto iter = m_Content.find(name);
	if (iter != m_Content.end())
	{
		return iter->second;
	}
	else
		return std::function<Component*(void)>();
}
