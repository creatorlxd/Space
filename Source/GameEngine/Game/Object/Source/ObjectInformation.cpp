#include "stdafx.h"
#include "Game/Object/Include/ObjectInformation.h"

ComponentManager::NewComponent<InformationComponent> InformationComponent::NewComponent;

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

void InformationComponent::Run(float DeltaTime)
{
	if (m_pObject)
		Scene::GetMainScene()->DeleteObjectInformation(m_pObject);
	else
	{
		ThrowError(L"需要先设置其所在的Object");
		return;
	}
}

void InformationComponent::SetObjectInformation(Object * po)
{
	m_pObject = po;
}

bool RegisterObject(const std::string & name, Object * po)
{
	if (!Scene::GetMainScene())
	{
		ThrowError(L"你需要先定义一个Scene");
		return false;
	}
	if (Scene::GetMainScene()->FindObject(name))
	{
		ThrowError(L"该Object已注册过了");
		return false;
	}
	Scene::GetMainScene()->AddObjectInformation(name, po);
	if (po->GetComponent("InformationComponent"))
	{
		ThrowError(L"该Object已拥有一个信息组件");
		return false;
	}
	auto buff = InformationComponent::NewComponent();
	po->AddComponent(buff);
	buff->Attach(po->GetRootComponent());

	auto buff2 = dynamic_cast<InformationComponent*>(buff);
	buff2->SetObjectInformation(po);
}
