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
#include "ComponentInformationManager.h"
#include "MemoryManager.h"

#define REGISTERCOMPONENTCLASS(classname) \
ComponentManager::NewComponent<classname> classname::NewComponent(STRING(classname));

namespace SpaceGameEngine
{
	class ComponentManager							//组件管理器
	{
	public:
		ComponentManager();
		~ComponentManager();
		static ComponentManager* GetMainManager();	//获取当前的主要的管理器的指针
		void SetAsMainManager();					//设置为主管理器
		template<typename T>
		struct NewComponent							//创建一个组件
		{
			std::string m_Name;
			NewComponent(const std::string& name);
			Component* operator () ()
			{
				if (sm_pThis == nullptr)
				{
					ThrowError(L"需要先定义一个组件管理器");
					return nullptr;
				}
				Component* buff = MemoryManager::New<T>();
				if (!sm_pThis->m_FreeIndexList.empty())
				{
					sm_pThis->m_Content[sm_pThis->m_FreeIndexList.front()] = buff;
					sm_pThis->m_FreeIndexList.pop();
				}
				else
					sm_pThis->m_Content.push_back(buff);
				return buff;
			}
		};
		bool DeleteComponent(Component* pc);		//删除一个组件
		void Release();								//释放

		static void DestoryComponent(Component* pc);

		static Component* NewComponentByName(const std::string& name);			//通过组件子类名来创建组件
	protected:
		static ComponentManager* sm_pThis;			//当前的管理器指针
		Vector<Component*> m_Content;			//所管理的组件
		Queue<unsigned int> m_FreeIndexList;
	};

	template<typename T>
	inline ComponentManager::NewComponent<T>::NewComponent(const std::string & name)
	{
		m_Name = name;
		g_ComponentInformationManager.AddInformation(ComponentInformation(name, sizeof(T),*this));
	}

	Component* CloneComponent(Component* pc);
}