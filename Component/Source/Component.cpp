#include "stdafx.h"
#include "../Include/Component.h"

Component::Component()
{
	m_TypeName = "NullType";
	m_IfRun = true;
	m_IfUse = true;
}

Component::~Component()
{

}

std::string Component::GetTypeName()
{
	return m_TypeName;
}

void Component::Attach(Component * pc)
{
	pc->m_pChilds.push_back(this);
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
