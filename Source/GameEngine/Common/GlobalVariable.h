﻿/*
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
#include "Common/MemoryManager/AllocatorForSTL.hpp"

namespace SpaceGameEngine
{
	class GlobalVariableCore
	{
	public:
		virtual ~GlobalVariableCore();

		friend class GlobalVariableManager;
	private:
		virtual void Release();
	};

	class GlobalVariableManager
	{
	public:
		friend GlobalVariableManager& GetGlobalVariableManager();
		~GlobalVariableManager();

		template<typename T, typename AllocatorInterface>
		friend class GlobalVariable;
	private:
		GlobalVariableManager();
		void Insert(GlobalVariableCore* ptr);
		void Release();
	private:
		std::stack<GlobalVariableCore*> m_Content;
		bool m_IfReleased;
	};

	GlobalVariableManager& GetGlobalVariableManager();

	template<typename T, typename AllocatorInterface = MemoryManagerAllocatorInterface>
	class GlobalVariable :public GlobalVariableCore
	{
	public:
		template<typename... Arg>
		GlobalVariable(Arg&&... arg)
		{
			m_pContent = AllocatorInterface::template New<T>(std::forward<Arg>(arg)...);
			GetGlobalVariableManager().Insert(this);
		}

		T& Get()
		{
			return *m_pContent;
		}

		virtual ~GlobalVariable()
		{
			GetGlobalVariableManager().Release();
		}
	private:
		virtual void Release()override
		{
			AllocatorInterface::Delete(m_pContent);
		}
	private:
		T * m_pContent;
	};
}