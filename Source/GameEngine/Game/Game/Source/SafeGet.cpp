#include "stdafx.h"
#include "../Include/SafeGet.h"
using namespace SpaceGameEngine;

ComponentManager * SpaceGameEngine::GetComponentManager()
{
	auto pointer = ComponentManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个组件管理器");
		return nullptr;
	}
	return pointer;
	
}

ObjectManager * SpaceGameEngine::GetObjectManager()
{
	auto pointer = ObjectManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个对象管理器");
		return nullptr;
	}
	return pointer;
}

MessageManager* SpaceGameEngine::GetMessageManager()
{
	auto pointer = MessageManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个消息管理器");
		return nullptr;
	}
	return pointer;
}

Scene * SpaceGameEngine::GetScene()
{
	auto pointer = Scene::GetMainScene();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个场景");
		return nullptr;
	}
	return pointer;
}

Game * SpaceGameEngine::GetGame()
{
	auto pointer = Game::GetMainGame();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个游戏类");
		return nullptr;
	}
	return pointer;
}
