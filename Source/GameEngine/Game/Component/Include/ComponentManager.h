#pragma once
#include "stdafx.h"
#include "Component.h"

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
		Component* operator () ()
		{
			if (sm_pThis == nullptr)
			{
				ThrowError(L"需要先定义一个组件管理器");
				return nullptr;
			}
			Component* buff = new T();
			sm_pThis->m_Content.push_back(buff);
			return buff;
		}
	};
	bool DeleteComponent(Component* pc);		//删除一个组件
	void Release();								//释放
protected:
	static ComponentManager* sm_pThis;			//当前的管理器指针
	std::vector<Component*> m_Content;			//所管理的组件
};