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
		std::vector<Component*> m_Content;			//����������
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