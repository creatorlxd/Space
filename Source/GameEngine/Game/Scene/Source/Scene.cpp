#include "stdafx.h"
#include "../Include/Scene.h" 

Scene::Scene()
{

}

Scene::~Scene()
{
	Release();
}

void Scene::SetAsMainScene()
{
	m_ObjectManager.SetAsMainManager();
}

void Scene::Start()
{
	m_ObjectManager.Start();
}

void Scene::Run(float DeltaTime)
{
	m_ObjectManager.Run(DeltaTime);
}

void Scene::Release()
{
	m_ObjectManager.Release();
}
