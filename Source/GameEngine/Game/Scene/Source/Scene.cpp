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
	//���Ĭ�������
	Object* DefaultCamera=ObjectManager::NewObject();
	DefaultCamera->AddComponent(CameraComponent::NewComponent());
	DefaultCamera->AddComponent(TransformComponent::NewComponent());
	DefaultCamera->SetRootComponent(TransformComponent::NewComponent.m_Name);
	DefaultCamera->GetComponent(CameraComponent::NewComponent.m_Name)->Attach(DefaultCamera->GetRootComponent());
	REGISTEROBJECT(DefaultCamera);
	//--------------

	m_ObjectManager.Start();
}

void SpaceGameEngine::Scene::Run(float DeltaTime)
{
	if (CameraComponent::GetMainCamera())
	{
		Window::GetMainWindow()->GetVertexShader().m_SceneData.m_ViewMatrix = CameraComponent::GetMainCamera()->ComputeViewMatrix();
	}
	else
	{
		ThrowError(L"����Ҫ��һ�������");
	}
	Window::GetMainWindow()->GetVertexShader().m_SceneData.m_DeltaTime = XMFLOAT4(DeltaTime, DeltaTime, DeltaTime, DeltaTime);
	Window::GetMainWindow()->GetVertexShader().m_SceneData.m_ProjectionMatrix = GetProjectionMatrix(XM_PIDIV4, (float)((float)Window::GetMainWindow()->GetWindowWidth() / (float)Window::GetMainWindow()->GetWindowHeight()));
	Window::GetMainWindow()->GetVertexShader().SetConstantBuffer(Window::GetMainWindow()->GetD3DDevice(), Window::GetMainWindow()->GetD3DDeviceContext(), Window::GetMainWindow()->GetVertexShader().SceneDataIndex, Window::GetMainWindow()->GetVertexShader().m_SceneData);
	m_MessageManager.Run();
	m_ObjectManager.Run(DeltaTime);
}

void SpaceGameEngine::Scene::Release()
{
	m_ObjectManager.Release();
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
		ThrowError(L"��Object��ע�����");
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
		ThrowError(L"��Object��û��ע��");
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
	ThrowError(L"��Object��û��ע��");
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
