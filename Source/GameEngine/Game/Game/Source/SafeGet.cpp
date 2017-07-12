#include "stdafx.h"
#include "../Include/SafeGet.h"

ComponentManager * GetComponentManager()
{
	auto pointer = ComponentManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ�����������");
		return nullptr;
	}
	return pointer;
	
}

ObjectManager * GetObjectManager()
{
	auto pointer = ObjectManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ�����������");
		return nullptr;
	}
	return pointer;
}

MessageManager* GetMessageManager()
{
	auto pointer = MessageManager::GetMainManager();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ����Ϣ������");
		return nullptr;
	}
	return pointer;
}

Scene * GetScene()
{
	auto pointer = Scene::GetMainScene();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ������");
		return nullptr;
	}
	return pointer;
}

Game * GetGame()
{
	auto pointer = Game::GetMainGame();
	if (!pointer)
	{
		ThrowError(L"��Ҫ�ȴ���һ����Ϸ��");
		return nullptr;
	}
	return pointer;
}
