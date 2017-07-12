#include "stdafx.h"
#include "../Include/SafeGet.h"

ComponentManager * GetComponentManager()
{
	auto pointer = ComponentManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个组件管理器");
		return nullptr;
	}
	return pointer;
	
}

ObjectManager * GetObjectManager()
{
	auto pointer = ObjectManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个对象管理器");
		return nullptr;
	}
	return pointer;
}

MessageManager* GetMessageManager()
{
	auto pointer = MessageManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个消息管理器");
		return nullptr;
	}
	return pointer;
}

Scene * GetScene()
{
	auto pointer = Scene::GetMainScene();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个场景");
		return nullptr;
	}
	return pointer;
}

Game * GetGame()
{
	auto pointer = Game::GetMainGame();
	if (!pointer)
	{
		ThrowError(L"需要先创建一个游戏类");
		return nullptr;
	}
	return pointer;
}
