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
	m_IfInit = false;
}

SpaceGameEngine::Scene::~Scene()
{
	for (auto i : m_Content)
		MemoryManager::Delete(i.second);
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

void SpaceGameEngine::Scene::SetAsMainScene()
{
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
	if (!m_IfInit)
	{	
		//添加默认摄像机
		Object* DefaultCamera = NewObject("DefaultCamera");
		DefaultCamera->AddComponent(CameraComponent::NewComponent());
		DefaultCamera->AddComponent(TransformComponent::NewComponent());
		DefaultCamera->SetRootComponent(TransformComponent::NewComponent.m_Name);
		DefaultCamera->GetComponent(CameraComponent::NewComponent.m_Name)->Attach(DefaultCamera->GetRootComponent());
		//--------------
		m_IfInit = true;
	}
	else
	{
		GetObjectByName("DefaultCamera")->GetComponent(CameraComponent::NewComponent.m_Name)->Run(0.0f);
	}
	
	for (auto i : m_Content)
	{
		if (i.second)
			if (i.second->IfUse())
				i.second->Start();
	}

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
	
	for (auto i : m_Content)
	{
		if (i.second)
			if (i.second->IfUse() && i.second->IfRun() && (!i.second->IfChild()))
				i.second->Run(DeltaTime);
	}
	for (auto i : m_Content)
	{
		if (i.second)
			if (i.second->IfUse() && i.second->IfRun())
				i.second->EveryFrameCleanUp();
	}

	m_GlobalOctree.Run();
	m_RenderSystem.Render();
	
	for (auto i : m_Content)
	{
		if (i.second)
			if (i.second->IfUse() && i.second->IfRun())
				i.second->ClearMessage();
	}
}

Object * SpaceGameEngine::Scene::NewObject(const std::string name)
{
	if (GetObjectByName(name) != nullptr)
	{
		ThrowError(L"Object的Name重复了");
		return nullptr;
	}
	else
	{
		auto re = MemoryManager::New<Object>();
		m_Content.insert(std::make_pair(name, re));
		return re;
	}
}

Object * SpaceGameEngine::Scene::GetObjectByName(const std::string name)
{
	auto iter = m_Content.find(name);
	if (iter != m_Content.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

bool SpaceGameEngine::Scene::DeleteObject(Object * po)
{
	if (po)
	{
		auto iter = m_Content.end();
		for (auto i=m_Content.begin();i!=m_Content.end();i++)
		{
			if (i->second == po)
			{
				iter = i;
				break;
			}
		}
		if (iter != m_Content.end())
		{
			iter->second->ReleaseComponentWhenRuntime();
			if (po->GetRenderObject())
			{
				m_RenderSystem.DeleteRenderObject(po->GetRenderObject());
				po->SetRenderObject(nullptr);
			}
			if (iter->second->GetFatherObject()&& iter->second->IfChild())
			{
				iter->second->GetFatherObject()->DeleteChildObject(iter->second);
			}
			if (!iter->second->GetChildren().empty())
			{
				for (auto i : iter->second->GetChildren())
				{
					DisconObject(i);
				}
			}
			MemoryManager::Delete(iter->second);
			m_Content.erase(iter);
			return true;
		}
		else
		{
			ThrowError("do not have this object in scene");
			return false;
		}
	}
	else
	{
		ThrowError("can not delete nullptr");
		return false;
	}
}

bool SpaceGameEngine::Scene::DeleteObject(const std::string name)
{
	return DeleteObject(GetObjectByName(name));
}

void SpaceGameEngine::CopyObject(Object * dst, Object * src)
{
	if (dst&&src)
	{
		if (src->GetRootComponent())
		{
			Queue<std::pair<Component*, Component*>> que;		//pair<dst's component,src's component>
			if (src->GetRenderObject())
			{
				dst->SetRenderObject(RenderSystem::GetMainRenderSystem()->NewRenderObject());
				dst->GetRenderObject()->m_Type = src->GetRenderObject()->m_Type;
				dst->GetRenderObject()->m_pObject = dst;
			}
			if (src->IfChild() && src->GetRootComponent()->GetTypeName() == STRING(ConnectComponent))
			{
				dst->AddComponent(MemoryManager::New<Component>());
				dst->SetRootComponent(STRING(Component));
			}
			else
			{
				dst->AddComponent(NewComponentByTypeName(src->GetRootComponent()->GetTypeName()));
				dst->SetRootComponent(src->GetRootComponent()->GetTypeName());
				dst->GetRootComponent()->Copy(src->GetRootComponent());
			}
			que.push(std::make_pair(dst->GetRootComponent(), src->GetRootComponent()));

			while (!que.empty())
			{
				auto pair = que.front();
				que.pop();
				auto _dst = pair.first;
				auto _src = pair.second;

				if (_src->GetChildrenComponent().empty())
					continue;
				else
				{
					auto contianer = _src->GetChildrenComponent();
					for (auto i : contianer)
					{
						dst->AddComponent(NewComponentByTypeName(i->GetTypeName()));
						auto ndst = dst->GetComponent(i->GetTypeName());
						ndst->Copy(i);
						ndst->Attach(_dst);
						que.push(std::make_pair(ndst, i));
					}
				}
			}

			if (SpaceEngineWindow->IfBegin())
			{
				dst->Start();
				dst->GetRenderObject()->m_pGlobalOctree = &Scene::GetMainScene()->m_GlobalOctree;
				dst->GetRenderObject()->Init();
			}
		}
		else
			ThrowError("src object must set root component");
	}
	else
	{
		ThrowError("can not copy nullptr");
	}
}
