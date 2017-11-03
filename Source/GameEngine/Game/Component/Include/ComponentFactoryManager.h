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
#pragma once
#include "stdafx.h"
#include "Component.h"
namespace SpaceGameEngine
{
	class ComponentFactoryManager			//�����������������
	{
	public:
		ComponentFactoryManager();
		~ComponentFactoryManager();
		void Release();

		static ComponentFactoryManager* GetMainManager();
		void SetAsMainManager();

		bool AddComponentFactory(const std::string& name, std::function<Component*(void)> functor);
		bool DeleteComponentFactory(const std::string& name);
		std::function<Component*(void)> FindComponentFactory(const std::string& name);
	private:
		Map<std::string, std::function<Component*(void)> > m_Content;

		static ComponentFactoryManager* sm_pThis;
	};

#define REGISTERCOMPONENTCLASS(name) SpaceGameEngine::ComponentManager::NewComponent<name> name::NewComponent(#name)
}