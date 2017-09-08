#include "stdafx.h"
#include "../Include/Component.h"
using namespace SpaceGameEngine;

SpaceGameEngine::Component::Component()
{
	m_TypeName = "NullType";
	m_IfRun = true;
	m_IfUse = true;
	m_pFather = nullptr;
	m_pFatherObject = nullptr;
}

SpaceGameEngine::Component::~Component()
{
	Release();
}

std::string SpaceGameEngine::Component::GetTypeName()
{
	return m_TypeName;
}

Component * SpaceGameEngine::Component::GetFatherComponent()
{
	return m_pFather;
}

void SpaceGameEngine::Component::SetFatherComponent(Component * pc)
{
	m_pFather = pc;
}

void SpaceGameEngine::Component::AddChildComponent(Component * pc)
{
	m_Children.push_back(pc);
}

bool SpaceGameEngine::Component::DeleteChildComponent(Component * pc)
{
	auto result = std::find(m_Children.begin(), m_Children.end(),pc);
	if (result == m_Children.end())
	{
		ThrowError(L"û�и������");
		return false;
	}
	m_Children.erase(result);
	return true;
}

Component * SpaceGameEngine::Component::FindChildComponent(const std::string & name)
{
	std::queue<Component*> q;
	for (auto i : m_Children)
	{
		q.push(i);
	}
	while (!q.empty())
	{
		auto i = q.front();
		q.pop();
		if (i->GetTypeName() == name)
		{
			return i;
		}
		else
		{
			for (auto j : i->GetChildrenComponent())
			{
				q.push(j);
			}
		}
	}
	return nullptr;
}

Component * SpaceGameEngine::Component::FindFatherComponent(const std::string & name)
{
	auto cb = this;
	while (cb != nullptr&&cb->GetTypeName() != name)
	{
		cb = cb->GetFatherComponent();
	}
	return cb;
}

std::vector<Component*>& SpaceGameEngine::Component::GetChildrenComponent()
{
	return m_Children;
}

void SpaceGameEngine::Component::InitFromFile(const std::string& filename, int mode)
{

}

void SpaceGameEngine::Component::Start()
{

}

void SpaceGameEngine::Component::Run(float DeltaTime)
{

}

void SpaceGameEngine::Component::Attach(Component * pc)
{
	if (pc)
	{
		m_pFather = pc;
		pc->m_Children.push_back(this);
	}
	else
	{
		ThrowError(L"���ܽ�һ���������һ����ָ��");
		return;
	}
}

void SpaceGameEngine::Component::Release()
{

}

bool SpaceGameEngine::Component::IfRun()
{
	return m_IfRun;
}

bool SpaceGameEngine::Component::IfUse()
{
	return m_IfUse;
}

void SpaceGameEngine::Component::ChangeIfRun(bool b)
{
	m_IfRun = b;
}

void SpaceGameEngine::Component::ChangeIfUse(bool b)
{
	m_IfUse = b;
}

void SpaceGameEngine::Component::SetFatherObject(Object * po)
{
	m_pFatherObject = po;
}

Object * SpaceGameEngine::Component::GetFatherObject()
{
	return m_pFatherObject;
}

void SpaceGameEngine::Component::SetMode(int m)
{
	m_Mode = m;
}

int SpaceGameEngine::Component::GetMode()
{
	return m_Mode;
}
