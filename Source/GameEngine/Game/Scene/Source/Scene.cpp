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
#include "../Include/Scene.h" 
using namespace SpaceGameEngine;

Scene* SpaceGameEngine::Scene::sm_pThis = nullptr;

SpaceGameEngine::Scene::Scene()
{
	sm_pThis = this;
}

SpaceGameEngine::Scene::~Scene()
{
	Release();
}

void SpaceGameEngine::Scene::SetAsMainScene()
{
	m_ObjectManager.SetAsMainManager();
	m_ComponentManager.SetAsMainManager();
	m_MessageManager.SetAsMainManager();
	sm_pThis = this;
}

Scene * SpaceGameEngine::Scene::GetMainScene()
{
	return sm_pThis;
}

void SpaceGameEngine::Scene::Start()
{
	static bool ifinit = false;
	if (!ifinit)
	{	
		//添加默认摄像机
		Object* DefaultCamera = ObjectManager::NewObject();
		DefaultCamera->AddComponent(CameraComponent::NewComponent());
		DefaultCamera->AddComponent(TransformComponent::NewComponent());
		DefaultCamera->SetRootComponent(TransformComponent::NewComponent.m_Name);
		DefaultCamera->GetComponent(CameraComponent::NewComponent.m_Name)->Attach(DefaultCamera->GetRootComponent());
		REGISTEROBJECT(DefaultCamera);
		//--------------
		ifinit = true;
	}
	else
	{
		FindObject("DefaultCamera")->GetComponent(CameraComponent::NewComponent.m_Name)->Run(0.0f);
	}
	m_ObjectManager.Start();
	m_GlobalOctree.BuildTree();
}

void SpaceGameEngine::Scene::Run(float DeltaTime)
{
	SpaceEngineWindow->GetEffectShader().m_pDeltaTime->SetFloatVector(reinterpret_cast<float*>(&XMVectorReplicate(DeltaTime)));
	SceneData::m_ViewMatrix = CameraComponent::GetMainCamera()->ComputeViewMatrix();
	SceneData::m_ProjectionMatrix = GetProjectionMatrix(CameraComponent::GetMainCamera()->GetAngle(), (float)(SpaceEngineWindow->GetWindowWidth()) / (float)(SpaceEngineWindow->GetWindowHeight()), CameraComponent::GetMainCamera()->GetNearZ(), CameraComponent::GetMainCamera()->GetFarZ());
	m_MessageManager.Run();
	m_GlobalOctree.Run();
	m_ObjectManager.Run(DeltaTime);
}

void SpaceGameEngine::Scene::Release()
{
	m_ObjectManager.Release();
	m_GlobalOctree.Release();
	m_ComponentManager.Release();
	m_MessageManager.Release();
	m_ObjectInformation.clear();
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

bool SpaceGameEngine::Scene::AddObjectInformation(const std::string & name, Object * po)
{
	if (FindObject(name) != nullptr)
	{
		ThrowError(L"该Object已注册过了");
		return false;
	}
	else
	{
		m_ObjectInformation.insert(std::make_pair(name, po));
		return true;
	}
}

bool SpaceGameEngine::Scene::DeleteObjectInformation(const std::string & name)
{
	auto buff = m_ObjectInformation.find(name);
	if (buff == m_ObjectInformation.end())
	{
		ThrowError(L"该Object还没有注册");
		return false;
	}
	m_ObjectInformation.erase(buff);
	return true;
}

bool SpaceGameEngine::Scene::DeleteObjectInformation(Object * po)
{
	for (auto i = m_ObjectInformation.begin(); i != m_ObjectInformation.end(); i++)
	{
		if ((*i).second == po)
		{
			m_ObjectInformation.erase(i);
			return true;
		}
	}
	ThrowError(L"该Object还没有注册");
	return false;
}

Object * SpaceGameEngine::Scene::FindObject(const std::string & name)
{
	auto re = m_ObjectInformation.find(name);
	if (re == m_ObjectInformation.end())
	{
		return nullptr;
	}
	else
	{
		return (*re).second;
	}
}

std::string SpaceGameEngine::Scene::FindObjectName(Object * po)
{
	for (auto i = m_ObjectInformation.begin(); i != m_ObjectInformation.end(); i++)
	{
		if (i->second == po)
		{
			return i->first;
		}
	}
	return std::string();
}
