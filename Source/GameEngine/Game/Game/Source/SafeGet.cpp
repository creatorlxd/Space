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
