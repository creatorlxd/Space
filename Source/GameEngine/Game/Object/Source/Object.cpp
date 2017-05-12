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
	return true;
}

bool Object::DeleteComponent(const std::string & name)
{
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
