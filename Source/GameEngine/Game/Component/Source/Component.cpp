#include "stdafx.h"
#include "../Include/Component.h"

Component::Component()
{
	m_TypeName = "NullType";
	m_IfRun = true;
	m_IfUse = true;
	m_pFather = nullptr;
}

Component::~Component()
{
	Release();
}

std::string Component::GetTypeName()
{
	return m_TypeName;
}

Component * Component::GetFatherComponent()
{
	return m_pFather;
}

void Component::SetFatherComponent(Component * pc)
{
	m_pFather = pc;
}

void Component::AddChildComponent(Component * pc)
{
	m_Children.push_back(pc);
}

bool Component::DeleteChildComponent(Component * pc)
{
	auto result = std::find(m_Children.begin(), m_Children.end(),pc);
	if (result == m_Children.end())
	{
		ThrowError(L"没有该子组件");
		return false;
	}
	m_Children.erase(result);
	return true;
}

Component * Component::FindChildComponent(const std::string & name)
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

std::vector<Component*>& Component::GetChildrenComponent()
{
	return m_Children;
}

void Component::InitFromFile(const std::string& filename, int mode)
{

}

void Component::Start()
{

}

void Component::Run(float DeltaTime)
{

}

void Component::Attach(Component * pc)
{
	if (pc)
	{
		m_pFather = pc;
		pc->m_Children.push_back(this);
	}
	else
	{
		ThrowError(L"不能将一个组件链向一个空指针");
		return;
	}
}

void Component::Release()
{

}

bool Component::IfRun()
{
	return m_IfRun;
}

bool Component::IfUse()
{
	return m_IfUse;
}

void Component::ChangeIfRun(bool b)
{
	m_IfRun = b;
}

void Component::ChangeIfUse(bool b)
{
	m_IfUse = b;
}
