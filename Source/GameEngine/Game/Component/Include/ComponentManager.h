#pragma once
#include "stdafx.h"
#include "Component.h"

class ComponentManager							//���������
{
public:
	ComponentManager();
	~ComponentManager();
	ComponentManager* const GetMainManager();	//��ȡ��ǰ����Ҫ�Ĺ�������ָ��
	
	template<typename T>
	struct NewComponent							//����һ�����
	{
		Component* operator () ()
		{
			if (sm_pThis == nullptr)
			{
				ThrowError(L"��Ҫ�ȶ���һ�����������");
				return nullptr;
			}
			Component* buff = new T();
			sm_pThis->m_Content.push_back(buff);
			return buff;
		}
	};
	bool DeleteComponent(Component* pc);		//ɾ��һ�����
protected:
	static ComponentManager* sm_pThis;			//��ǰ�Ĺ�����ָ��
	std::vector<Component*> m_Content;			//����������
};