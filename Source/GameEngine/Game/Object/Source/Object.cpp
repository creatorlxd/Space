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
#include "../Include/Object.h"

using namespace SpaceGameEngine;

Vector<std::pair<std::string, std::pair<std::string, int>>> SpaceGameEngine::ReadAssetListFromFile(const std::string & filename)
{
	Vector<std::pair<std::string, std::pair<std::string, int>>> re;
	File file(filename,FileMode::Read);
	std::string componentname, assetname;
	int mode;
	while ((file >> componentname >> assetname >> mode).IfFileReadOver() == false)
	{
		re.push_back(make_pair(componentname, make_pair(assetname, mode)));
	}
	file.Close();

	return re;
}

SpaceGameEngine::Object::Object()
{
	m_pRootComponent = nullptr;
	m_IfUse = true;
	m_IfRun = true;
	m_IfHaveRun = false;
	m_IfChild = false;
	m_pFather = nullptr;
	m_pRenderObject = nullptr;
	m_Mode = ObjectMode::Common;
}

SpaceGameEngine::Object::~Object()
{
	for (auto i : m_Components)
		if (i.second)
			MemoryManager::Delete(i.second);
}

Component * SpaceGameEngine::Object::GetComponent(const std::string & name)
{
	auto result = m_Components.end();
	result=m_Components.find(name);
	if (result != m_Components.end())
	{
		return (*result).second;
	}
	else
	{
		return nullptr;
	}
}

bool SpaceGameEngine::Object::AddComponent(Component * pc)
{
	if (pc)
	{
		if (GetComponent(pc->GetTypeName()) != nullptr)
		{
			ThrowError(L"已有相同类型的组件了");
			pc->CleanUp();
			MemoryManager::Delete(pc);
			return false;
		}
		m_Components.insert(std::make_pair(pc->GetTypeName(), pc));
		pc->SetFatherObject(this);
		return true;
	}
	else
	{
		ThrowError("can not add nullptr as a component");
		return false;
	}
}

bool SpaceGameEngine::Object::DeleteComponent(const std::string & name)
{
	auto component = m_Components.find(name);
	if (component == m_Components.end())
	{
		ThrowError(L"没找到该类型的组件");
		return false;
	}
	if (name == m_pRootComponent->GetTypeName())
	{
		ThrowError("can not delete root component");
	}
	component->second->CleanUp();
	if (component->second->GetFatherComponent())
	{
		for (auto i : component->second->GetChildrenComponent())
			i->Attach(component->second->GetFatherComponent());
		component->second->GetChildrenComponent().clear();
		component->second->GetFatherComponent()->DeleteChildComponent(component->second);
	}
	if (!component->second->GetChildrenComponent().empty())
	{
		for (auto i : component->second->GetChildrenComponent())
			i->SetFatherComponent(nullptr);
	}
	MemoryManager::Delete(component->second);
	m_Components.erase(component);
	return true;
}

void SpaceGameEngine::Object::Start()
{
	for (auto i : m_Components)
	{
		if (i.second->IfUse())
			i.second->Start();
	}
}

void SpaceGameEngine::Object::InitFromFile(const Vector<std::pair<std::string, std::pair<std::string, int>>>& filenames)
{
	for (const auto& i : filenames)
	{
		auto pointer = GetComponent(i.first);
		if (pointer)
		{
			pointer->InitFromFile(i.second.first, i.second.second);
		}
	}
}

void SpaceGameEngine::Object::InitFromFile(const std::string& filename)
{
	InitFromFile(ReadAssetListFromFile(filename));
}

void SpaceGameEngine::Object::Run(float DeltaTime)
{
	if (m_pRootComponent == nullptr)
	{
		ThrowError(L"根组件不能为空");
		return;
	}
	for (auto i : m_RequiredObject)
	{
		if (i)
		{
			if (!i->m_IfHaveRun)
				i->Run(DeltaTime);
		}
	}
	RunComponentOnTree(m_pRootComponent, DeltaTime);
	m_IfHaveRun = true;
	if (!m_Children.empty())
	{
		for (auto i : m_Children)
		{
			if (i->IfRun() && i->IfUse())
				i->Run(DeltaTime);
		}
	}
}

void SpaceGameEngine::Object::EveryFrameCleanUp()
{
	for (auto i : m_Components)
		if (i.second->IfRun() && i.second->IfUse())
			i.second->EveryFrameCleanUp();
}

bool SpaceGameEngine::Object::SetRootComponent(const std::string & name)
{
	auto component = GetComponent(name);
	if (component == nullptr)
	{
		ThrowError(L"没找到该类型的组件");
		return false;
	}
	m_pRootComponent = component;
	return false;
}

Component * SpaceGameEngine::Object::GetRootComponent()
{
	return m_pRootComponent;
}

bool SpaceGameEngine::Object::IfRun()
{
	return m_IfRun;
}

bool SpaceGameEngine::Object::IfUse()
{
	return m_IfUse;
}

void SpaceGameEngine::Object::ChangeIfRun(bool b)
{
	m_IfRun = b;
}

void SpaceGameEngine::Object::ChangeIfUse(bool b)
{
	m_IfUse = b;
}

void SpaceGameEngine::Object::ClearRunState()
{
	m_IfHaveRun = false;
}

bool SpaceGameEngine::Object::GetIfHaveRun()
{
	return m_IfHaveRun;
}

void SpaceGameEngine::Object::ProduceMessage(Component * from, unsigned int message)
{
	m_Message.insert(std::make_pair(message, from));
}

Component * SpaceGameEngine::Object::GetComponentByMessage(unsigned int message)
{
	Component* re = nullptr;
	auto iter = m_Message.find(message);
	if (iter != m_Message.end())
	{
		re = iter->second;
	}
	return re;
}

void SpaceGameEngine::Object::ClearMessage()
{
	m_Message.clear();
}

Vector<Object*>& SpaceGameEngine::Object::GetChildren()
{
	return m_Children;
}

void SpaceGameEngine::Object::AddChildObject(Object * po)
{
	if (po)
		m_Children.push_back(po);
	else
		ThrowError("不能将空对象指针作为子对象");
}

void SpaceGameEngine::Object::DeleteChildObject(Object * po)
{
	auto iter = std::find(m_Children.begin(), m_Children.end(), po);
	if (iter == m_Children.end())
		ThrowError("没有该子对象");
	else
		m_Children.erase(iter);
}

SpaceGameEngine::Object* SpaceGameEngine::Object::GetFatherObject()
{
	return m_pFather;
}

void SpaceGameEngine::Object::SetFatherObject(Object * po)
{
	m_pFather = po;
	if (po == nullptr)
		m_IfChild = false;
	else
		m_IfChild = true;
}

bool SpaceGameEngine::Object::IfChild()
{
	return m_IfChild;
}

void SpaceGameEngine::Object::SetRenderObject(RenderObject * pro)
{
	m_pRenderObject = pro;
}

RenderObject * SpaceGameEngine::Object::GetRenderObject()
{
	return m_pRenderObject;
}

void SpaceGameEngine::Object::Attach(Object* po)
{
	if (po == nullptr)
		ThrowError("不能链上空指针");
	else
	{
		po->AddChildObject(this);
		m_pFather = po;
		m_IfChild = true;
	}
}

void SpaceGameEngine::Object::Discon()
{
	if (m_IfChild)
	{
		m_IfChild = false;
		m_pFather->DeleteChildObject(this);
		m_pFather = nullptr;
	}
	else
		ThrowError("该对象不是子对象");
}

void SpaceGameEngine::Object::ReleaseComponentWhenRuntime()
{
	for (auto i : m_Components)
		i.second->CleanUp();
}

void SpaceGameEngine::Object::RequireObject(Object * po)
{
	if (po)
	{
		while (po->m_IfChild&&po->m_pFather)
			po = po->m_pFather;
		auto iter = std::find(m_RequiredObject.begin(), m_RequiredObject.end(), po);
		if (iter != m_RequiredObject.end())
		{
			//ThrowError("can not require a object which have already be required");
		}
		else
		{
			m_RequiredObject.push_back(po);
		}
	}
	else
		ThrowError("object can not be nullptr");
}

void SpaceGameEngine::Object::UnrequireObject(Object * po)
{
	if (po)
	{
		while (po->m_IfChild&&po->m_pFather)
			po = po->m_pFather;
		auto iter = std::find(m_RequiredObject.begin(), m_RequiredObject.end(), po);
		if (iter != m_RequiredObject.end())
		{
			m_RequiredObject.erase(iter);
		}
		else
		{
			//ThrowError("can not find this required object");
		}
	}
	else
		ThrowError("object can not be nullptr");
}

const Vector<Object*>& SpaceGameEngine::Object::GetRequiredObject()
{
	return m_RequiredObject;
}

void SpaceGameEngine::Object::SetMode(ObjectMode mode)
{
	m_Mode = mode;
}

ObjectMode SpaceGameEngine::Object::GetMode()
{
	return m_Mode;
}

void SpaceGameEngine::RunComponentOnTree(Component * node, float DeltaTime)
{
	if (node)
	{
		if (node->IfRun() && node->IfUse())
			node->Run(DeltaTime);
		for (auto i : node->GetChildrenComponent())
		{
			SpaceGameEngine::RunComponentOnTree(i, DeltaTime);
		}
	}
}
