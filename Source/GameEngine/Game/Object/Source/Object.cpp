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
	}
	m_Components.erase(component);
	return true;
}

void Object::Start()
{

}

void Object::InitFromFile(std::vector<std::pair<std::string, std::string>> filenames)
{

}

void Object::Run(float DeltaTime)
{

}

void Object::Release()
{

}

bool Object::SetRootComponent(const std::string & name)
{
	return true;
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
