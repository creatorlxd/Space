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
#pragma once
#include "stdafx.h"
#include "Component.h"
#include "ComponentInformationManager.h"
#include "Common/MemoryManager/Include/MemoryManager.h"

#define REGISTERCOMPONENTCLASS(classname) \
SpaceGameEngine::ComponentManager::NewComponent<classname> classname::NewComponent(STRING(classname));

namespace SpaceGameEngine
{
	class ComponentManager							//���������
	{
	public:
		ComponentManager();
		~ComponentManager();
		static ComponentManager* GetMainManager();	//��ȡ��ǰ����Ҫ�Ĺ�������ָ��
		void SetAsMainManager();					//����Ϊ��������
		template<typename T>
		struct NewComponent							//����һ�����
		{
			std::string m_Name;
			NewComponent(const std::string& name);
			Component* operator () ()
			{
				if (sm_pThis == nullptr)
				{
					ThrowError(L"��Ҫ�ȶ���һ�����������");
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
		bool DeleteComponent(Component* pc);		//ɾ��һ�����
		void Release();								//�ͷ�

		static void DestoryComponent(Component* pc);

		static Component* NewComponentByName(const std::string& name);			//ͨ��������������������
	protected:
		static ComponentManager* sm_pThis;			//��ǰ�Ĺ�����ָ��
		Vector<Component*> m_Content;			//����������
		Queue<unsigned int> m_FreeIndexList;
	};

	template<typename T>
	inline ComponentManager::NewComponent<T>::NewComponent(const std::string & name)
	{
		m_Name = name;
		GetComponentInformationManager().AddInformation(ComponentInformation(name, sizeof(T),*this));
	}

	Component* CloneComponent(Component* pc);
}