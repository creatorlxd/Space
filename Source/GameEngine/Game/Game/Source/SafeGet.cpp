#include "stdafx.h"
#include "../Include/SafeGet.h"
using namespace SpaceGameEngine;

ComponentManager * SpaceGameEngine::GetComponentManager()
{
	auto pointer = ComponentManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ�����������");
		return nullptr;
	}
	return pointer;
	
}

ObjectManager * SpaceGameEngine::GetObjectManager()
{
	auto pointer = ObjectManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ�����������");
		return nullptr;
	}
	return pointer;
}

MessageManager* SpaceGameEngine::GetMessageManager()
{
	auto pointer = MessageManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ����Ϣ������");
		return nullptr;
	}
	return pointer;
}

Scene * SpaceGameEngine::GetScene()
{
	auto pointer = Scene::GetMainScene();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ������");
		return nullptr;
	}
	return pointer;
}

Game * SpaceGameEngine::GetGame()
{
	auto pointer = Game::GetMainGame();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ����Ϸ��");
		return nullptr;
	}
	return pointer;
}
