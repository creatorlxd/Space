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
	m_IfRender = true;
}

SpaceGameEngine::Object::~Object()
{
	Release();
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
	if (GetComponent(pc->GetTypeName()) != nullptr)
	{
		ThrowError(L"已有相同类型的组件了");
		return false;
	}
	m_Components.insert(std::make_pair(pc->GetTypeName(),pc));
	pc->SetFatherObject(this);
	return true;
}

bool SpaceGameEngine::Object::DeleteComponent(const std::string & name)
{
	auto component = m_Components.find(name);
	if (component == m_Components.end())
	{
		ThrowError(L"没找到该类型的组件");
		return false;
	}
	Component* father = (*component).second->GetFatherComponent();
	if (father != nullptr)
	{
		father->DeleteChildComponent((*component).second);
		(*component).second->SetFatherComponent(nullptr);
		std::stack<Component*> eraselist;
		for (auto i : (*component).second->GetChildrenComponent())
		{
			eraselist.push(i);
			father->AddChildComponent(i);
		}
		while (!eraselist.empty())
		{
			auto i = eraselist.top();
			eraselist.pop();
			(*component).second->DeleteChildComponent(i);
		}
	}
	(*component).second->SetFatherObject(nullptr);
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
	RunComponentOnTree(m_pRootComponent, DeltaTime);
	m_Message.clear();
}

void SpaceGameEngine::Object::Release()
{
	auto info = GetComponent("InformationComponent");
	if (info)
	{
		info->Run(0.00f);
	}

	m_Components.clear();
	m_Message.clear();
	m_pRootComponent = nullptr;
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

bool SpaceGameEngine::Object::IfRender()
{
	return m_IfRender;
}

void SpaceGameEngine::Object::ChangeIfRender(bool b)
{
	m_IfRender = b;
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

void SpaceGameEngine::RunComponentOnTree(Component * node, float DeltaTime)
{
	if (node->IfRun()&&node->IfUse())
		node->Run(DeltaTime);
	for (auto i : node->GetChildrenComponent())
	{
		SpaceGameEngine::RunComponentOnTree(i, DeltaTime);
	}
}
