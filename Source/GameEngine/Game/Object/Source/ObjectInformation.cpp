#include "stdafx.h"
#include "Game/Object/Include/ObjectInformation.h"

ComponentManager::NewComponent<InformationComponent> InformationComponent::NewComponent;

InformationComponent::InformationComponent()
{
	m_TypeName = "InformationComponent";
	m_IfRun = false;
}

InformationComponent::~InformationComponent()
{
	Release();
}

void InformationComponent::Run(float DeltaTime)
{
	if (GetFatherObject())
		Scene::GetMainScene()->DeleteObjectInformation(GetFatherObject());
	else
	{
		ThrowError(L"��Ҫ�����������ڵ�Object");
		return;
	}
}

bool RegisterObject(const std::string & name, Object * po)
{
	if (!Scene::GetMainScene())
	{
		ThrowError(L"����Ҫ�ȶ���һ��Scene");
		return false;
	}
	if (Scene::GetMainScene()->FindObject(name))
	{
		ThrowError(L"��Object��ע�����");
		return false;
	}
	Scene::GetMainScene()->AddObjectInformation(name, po);
	if (po->GetComponent("InformationComponent"))
	{
		ThrowError(L"��Object��ӵ��һ����Ϣ���");
		return false;
	}
	auto buff = InformationComponent::NewComponent();
	po->AddComponent(buff);
	buff->Attach(po->GetRootComponent());
	return true;
}
