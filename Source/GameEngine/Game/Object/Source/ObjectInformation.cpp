#include "stdafx.h"
#include "Game/Object/Include/ObjectInformation.h"

InformationComponent::InformationComponent()
{
	m_TypeName = "InformationComponent";
	m_pObject = nullptr;
	m_IfRun = false;
}

InformationComponent::~InformationComponent()
{
	Release();
}

void InformationComponent::Run()
{
	if (m_pObject)
		Scene::GetMainScene()->DeleteObjectInformation(m_pObject);
	else
	{
		ThrowError(L"��Ҫ�����������ڵ�Object");
		return;
	}
}

void InformationComponent::SetObjectInformation(Object * po)
{
	m_pObject = po;
}
