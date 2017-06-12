#include "stdafx.h"
#include "../Include/Scene.h" 

Scene* Scene::sm_pThis = nullptr;

Scene::Scene()
{
	sm_pThis = this;
}

Scene::~Scene()
{
	Release();
}

void Scene::SetAsMainScene()
{
	m_ObjectManager.SetAsMainManager();
	sm_pThis = this;
}

Scene * Scene::GetMainScene()
{
	return sm_pThis;
}

void Scene::Start()
{
	m_ObjectManager.Start();
}

void Scene::Run(float DeltaTime)
{
	m_ObjectManager.Run(DeltaTime);
}

void Scene::Release()
{
	m_ObjectManager.Release();
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

bool Scene::AddObjectInformation(const std::string & name, Object * po)
{
	if (FindObject(name) != nullptr)
	{
		ThrowError(L"该Object已注册过了");
		return false;
	}
	else
	{
		m_ObjectInformation.insert(std::make_pair(name, po));
		return true;
	}
}

bool Scene::DeleteObjectInformation(const std::string & name)
{
	auto buff = m_ObjectInformation.find(name);
	if (buff == m_ObjectInformation.end())
	{
		ThrowError(L"该Object还没有注册");
		return false;
	}
	m_ObjectInformation.erase(buff);
	return true;
}

bool Scene::DeleteObjectInformation(Object * po)
{
	for (auto i = m_ObjectInformation.begin(); i != m_ObjectInformation.end(); i++)
	{
		if ((*i).second == po)
		{
			m_ObjectInformation.erase(i);
			return true;
		}
	}
	ThrowError(L"该Object还没有注册");
	return false;
}

Object * Scene::FindObject(const std::string & name)
{
	auto re = m_ObjectInformation.find(name);
	if (re == m_ObjectInformation.end())
	{
		return nullptr;
	}
	else
	{
		return (*re).second;
	}
}
