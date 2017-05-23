#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"

ObjectManager* ObjectManager::sm_pThis = nullptr;

ObjectManager::ObjectManager()
{
	sm_pThis = this;
}

ObjectManager::~ObjectManager()
{
	for (auto i : m_Content)
	{
		delete i;
	}
	sm_pThis = nullptr;
}

ObjectManager * const ObjectManager::GetMainManager()
{
	return sm_pThis;
}

Object * ObjectManager::NewObject()
{
	if (sm_pThis == nullptr)
	{
		ThrowError(L"需要先定义一个对象管理器");
		return nullptr;
	}
	auto re = new Object();
	sm_pThis->m_Content.push_back(re);
	return re;
}

bool ObjectManager::DeleteObject(Object * po)
{
	for (auto i = m_Content.begin(); i != m_Content.end(); i += 1)
	{
		if (*i == po)
		{
			delete po;
			m_Content.erase(i);
			return true;
		}
	}
	return false;
}

void ObjectManager::Start()
{
	for (auto i : m_Content)
	{
		if (i->IfUse())
			i->Start();
	}
}

void ObjectManager::Run(float DeltaTime)
{
	for (auto i : m_Content)
	{
		if (i->IfUse() && i->IfRun())
			i->Run(DeltaTime);
	}
}
