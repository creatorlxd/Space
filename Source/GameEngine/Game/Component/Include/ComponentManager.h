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
#include "ComponentFactoryManager.h"
#include "MemoryManager.h"

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
				sm_pThis->m_Content.push_back(buff);
				return buff;
			}
		};
		bool DeleteComponent(Component* pc);		//ɾ��һ�����
		void Release();								//�ͷ�

		static Component* NewComponentByName(const std::string& name);			//ͨ��������������������
	protected:
		static ComponentManager* sm_pThis;			//��ǰ�Ĺ�����ָ��
		Vector<Component*> m_Content;			//����������
	};

	extern ComponentFactoryManager g_ComponentFactoryManager;

	template<typename T>
	inline ComponentManager::NewComponent<T>::NewComponent(const std::string & name)
	{
		m_Name = name;
		auto pointer = ComponentFactoryManager::GetMainManager();
		if (!pointer)
		{
			ThrowError(L"���봴��һ�������������������");
			return;
		}
		pointer->AddComponentFactory(name, *this);
	}

}