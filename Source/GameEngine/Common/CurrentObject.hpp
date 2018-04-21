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
#include "Def.h"

namespace SpaceGameEngine
{
	/*
	CurrentObject<T>代表着T类的唯一当前对象(static)
	T类通过继承CurrentObject<T>来使用它
	在T类构造时要传入T类的this
	*/
	template<typename T>
	class CurrentObject
	{
	public:
		CurrentObject() = delete;
		CurrentObject(T* pthis)
		{
			if (pthis == nullptr)
				THROWERROR("pthis can not be nullptr");
			m_pThis = pthis;
			GetCurrentObjectPtr() = m_pThis;
		}
		virtual ~CurrentObject()
		{
			if (GetCurrentObjectPtr() == m_pThis)
				GetCurrentObjectPtr() = nullptr;
		}
		static T* GetCurrentObject()
		{
			return GetCurrentObjectPtr();
		}
		void SetAsCurrentObject()
		{
			GetCurrentObjectPtr() = m_pThis;
		}
	private:
		static T*& GetCurrentObjectPtr()
		{
			static T * sm_pCurrentObject = nullptr;
			return sm_pCurrentObject;
		}
	private:
		T * m_pThis;
	};
}