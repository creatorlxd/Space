#pragma once
#include "stdafx.h"
#include "Component.h"

class ComponentManager							//组件管理器
{
public:
	ComponentManager();
	~ComponentManager();
	ComponentManager* const GetMainManager();	//获取当前的主要的管理器的指针
	
	template<typename T>
	struct NewComponent							//创建一个组件
	{
		Component* operator () ()
		{
			Component* buff = new T();
			sm_pThis->m_Content.push_back(buff);
			return buff;
		}
	};
	bool DeleteComponent(Component* pc);		//删除一个组件
protected:
	static ComponentManager* sm_pThis;			//当前的管理器指针
	std::vector<Component*> m_Content;			//所管理的组件
};