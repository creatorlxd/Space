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
#include "ComponentInformationManager.h"

/*
REGISTER_COMPONENT必须要被使用在Component子类的public域中
*/
#define REGISTER_COMPONENT(classname)	\
static SpaceGameEngine::ComponentFactory<classname>& GetComponentFactory()\
{\
	static GlobalVariable<ComponentFactory<classname>> g_ComponentFactory(STRING(classname));\
	return g_ComponentFactory.Get();\
}\
static SpaceGameEngine::Component* NewComponent(){return GetComponentFactory()();}\
private:\
inline static ComponentFactory<classname>& sm_ComponentFactory=GetComponentFactory();\
public:

namespace SpaceGameEngine
{
	template<typename T>
	struct ComponentFactory							//创建一个组件
	{
		String m_Name;
		ComponentFactory(const String& name);
		Component* operator () ()
		{
			return MemoryManager::New<T>();
		}
	};
	template<typename T>
	inline ComponentFactory<T>::ComponentFactory(const String & name)
	{
		m_Name = name;
		GetComponentInformationManager().AddInformation(ComponentInformation(name, sizeof(T), *this));
	}

	Component* NewComponentByTypeName(const String type_name);
}