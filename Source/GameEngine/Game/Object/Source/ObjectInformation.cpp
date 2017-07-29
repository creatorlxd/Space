#include "stdafx.h"
#include "Game/Object/Include/ObjectInformation.h"
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(InformationComponent);

SpaceGameEngine::InformationComponent::InformationComponent()
{
	m_TypeName = "InformationComponent";
	m_IfRun = false;
}

SpaceGameEngine::InformationComponent::~InformationComponent()
{
	Release();
}

void SpaceGameEngine::InformationComponent::Run(float DeltaTime)
{
	if (GetFatherObject())
		Scene::GetMainScene()->DeleteObjectInformation(GetFatherObject());
	else
	{
		ThrowError(L"��Ҫ�����������ڵ�Object");
		return;
	}
}

bool SpaceGameEngine::RegisterObject(const std::string & name, Object * po)
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
	if (po->GetRootComponent() == nullptr)
	{
		po->SetRootComponent(InformationComponent::NewComponent.m_Name);
		return true;
	}
	else
	{
		buff->Attach(po->GetRootComponent());
		return true;
	}
}
