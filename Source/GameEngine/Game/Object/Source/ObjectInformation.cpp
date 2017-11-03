/*
Copyright 2017 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
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
		ThrowError(L"需要先设置其所在的Object");
		return;
	}
}

bool SpaceGameEngine::RegisterObject(const std::string & name, Object * po)
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
