/*
Copyright 2018 creatorlxd

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
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

void SpaceGameEngine::Scene::SetAsMainScene()
{
	m_ObjectManager.SetAsMainManager();
	m_ComponentManager.SetAsMainManager();
	m_MessageManager.SetAsMainManager();
	m_LightManager.SetAsMainManager();
	m_RenderSystem.SetAsMainRenderSystem();
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
	m_RenderSystem.m_pGlobalOctree = &m_GlobalOctree;
	m_RenderSystem.Init();
	m_GlobalOctree.BuildTree();
}

void SpaceGameEngine::Scene::Run(float DeltaTime)
{
	XMFLOAT3 camera_pos3 = CameraComponent::GetMainCamera()->GetTransform()->GetPosition();
	XMFLOAT4 camera_pos4(camera_pos3.x, camera_pos3.y, camera_pos3.z, 1.0f);
	XMVECTOR vbuff = XMLoadFloat4(&camera_pos4);
	SceneData::m_ViewMatrix = CameraComponent::GetMainCamera()->ComputeViewMatrix();
	SceneData::m_ProjectionMatrix = GetProjectionMatrix(CameraComponent::GetMainCamera()->GetAngle(), (float)(SpaceEngineWindow->GetWindowWidth()) / (float)(SpaceEngineWindow->GetWindowHeight()), CameraComponent::GetMainCamera()->GetNearZ(), CameraComponent::GetMainCamera()->GetFarZ());
	
	struct Lights
	{
		Light m_Content[LightManager::MaxLightSize];
		uint32_t m_Size[4];
	};
	static Lights lights;
	lights.m_Size[0] = 0;
	auto lights_buff = m_LightManager.GetLight(CameraComponent::GetMainCamera()->GetTransform());
	for (const auto i : lights_buff)
	{
		lights.m_Content[lights.m_Size[0]++] = i;
	}
	
	auto shaders = SpaceEngineWindow->GetDefaultEffectShader();
	for (auto i : shaders)
	{
		i->m_pDeltaTime->SetFloatVector(reinterpret_cast<float*>(&XMVectorReplicate(DeltaTime)));
		i->m_pCameraPosition->SetFloatVector(reinterpret_cast<float*>(&vbuff));
		i->m_pLights->SetRawValue(&lights, 0, sizeof(lights));
	}

	m_MessageManager.Run();
	m_GlobalOctree.Run();
	m_ObjectManager.Run(DeltaTime);
	m_RenderSystem.Render();
}

void SpaceGameEngine::Scene::Clear()
{
	m_ObjectManager.Clear();
	m_GlobalOctree.Clear();
	m_ComponentManager.Clear();
	m_MessageManager.Clear();
	m_ObjectInformation.clear();
	m_LightManager.Clear();
	m_RenderSystem.Clear();
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

void SpaceGameEngine::Scene::DeleteObject(Object * po)
{
	if (po)
	{
		if (po->GetRenderObject())
		{
			m_RenderSystem.DeleteRenderObject(po->GetRenderObject());
			po->SetRenderObject(nullptr);
		}
		m_ObjectManager.DeleteObject(po);
	}
	else
		ThrowError("can not delete nullptr");
}
