#include "stdafx.h"
#include "../Include/Object.h" 

Object::Object()
{
	m_pRootComponent = nullptr;
	m_IfUse = true;
	m_IfRun = true;
}

Object::~Object()
{
	Release();
}

Component * Object::GetComponent(const std::string & name)
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

bool Object::AddComponent(Component * pc)
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

bool Object::DeleteComponent(const std::string & name)
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

void Object::Start()
{
	for (auto i : m_Components)
	{
		if (i.second->IfUse())
			i.second->Start();
	}
}

void Object::InitFromFile(std::vector<std::pair<std::string, std::string>> filenames)
{
	std::fstream file;
	for (auto i : filenames)
	{
		auto component = GetComponent(i.first);
		if (component == nullptr)
		{
			continue;
		}
		file.open(i.second,std::ios::in);
		
		std::string filename;
		int mode=0;

		file >> filename>>mode;
		component->InitFromFile(filename,mode);

		file.close();
	}
}

void Object::InitFromFile(const std::string& filename)
{
	InitFromFile(ReadAssetListFromFile(filename));
}

void Object::Run(float DeltaTime)
{
	if (m_pRootComponent == nullptr)
	{
		ThrowError(L"根组件不能为空");
		return;
	}
	RunComponentOnTree(m_pRootComponent, DeltaTime);
}

void Object::Release()
{
	auto info = GetComponent("InformationComponent");
	if (info)
	{
		info->Run(0.00f);
	}

	m_Components.clear();
	m_pRootComponent = nullptr;
}

bool Object::SetRootComponent(const std::string & name)
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

Component * Object::GetRootComponent()
{
	return m_pRootComponent;
}

bool Object::IfRun()
{
	return m_IfRun;
}

bool Object::IfUse()
{
	return m_IfUse;
}

void Object::ChangeIfRun(bool b)
{
	m_IfRun = b;
}

void Object::ChangeIfUse(bool b)
{
	m_IfUse = b;
}

void RunComponentOnTree(Component * node, float DeltaTime)
{
	if (node->IfRun()&&node->IfUse())
		node->Run(DeltaTime);
	for (auto i : node->GetChildrenComponent())
	{
		RunComponentOnTree(i, DeltaTime);
	}
}
