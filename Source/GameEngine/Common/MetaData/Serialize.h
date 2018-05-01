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
#include "MetaData.h"
#include "Common/StringConverter.h"

namespace SpaceGameEngine
{
	class SerializeInterface
	{
	public:
		enum class IOFlag
		{
			Input,
			Output
		};
		SerializeInterface(IOFlag ioflag);
		virtual ~SerializeInterface();

		template<typename T, bool b>
		friend struct SerializeCore;
	private:
		virtual String Read() = 0;
		virtual void Write(const String& str) = 0;
	private:
		IOFlag m_IOFlag;
		Map<void*, void*> m_PointerPool;
	};

	template<typename T>
	struct SerializeMethod
	{
		static void In(T& obj, const String& str) = 0;
		static String Out(T& obj) = 0;
	};

	template<typename T, bool b>
	struct SerializeCore
	{

	};

	template<typename T>
	struct SerializeCore<T*, false>	//pointer serialize:use pointer pool
	{
		static void Run(T*& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				SerializeMethod<T*>::In(obj, si.Read());
				if (obj&&si.m_PointerPool.find((void*)obj) == si.m_PointerPool.end())
				{
					T* pt = MemoryManager::New<T>();
					SerializeMethod<T>::In(*pt, si.Read());
					si.m_PointerPool[obj] = pt;
				}
				if (obj)
					obj = (T*)si.m_PointerPool[obj];
			}
			else
			{
				si.Write(SerializeMethod<T*>::Out(obj));
				if (obj&&si.m_PointerPool.find((void*)obj) == si.m_PointerPool.end())
				{
					si.Write(SerializeMethod<T>::Out(*obj));
					si.m_PointerPool[obj] = obj;
				}
			}
		}
	};

	template<typename T>
	struct SerializeCore<T*, true>	//pointer serialize:use pointer pool
	{
		static void Run(T*& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				SerializeMethod<T*>::In(obj, si.Read());
				if (obj&&si.m_PointerPool.find((void*)obj) == si.m_PointerPool.end())
				{
					T* pt = MemoryManager::New<T>();
					SerializeMethod<T>::In(*pt, si.Read());
					si.m_PointerPool[obj] = pt;
				}
				if(obj)
					obj = (T*)si.m_PointerPool[obj];
			}
			else
			{
				si.Write(SerializeMethod<T*>::Out(obj));
				if (obj&&si.m_PointerPool.find((void*)obj) == si.m_PointerPool.end())
				{
					si.Write(SerializeMethod<T>::Out(*obj));
					si.m_PointerPool[obj] = obj;
				}
			}
		}
	};

	template<typename T>
	struct SerializeCore<T, true>
	{
		static void Run(T& obj, SerializeInterface& si)
		{
			for (auto& i : T::GetMetaDataCore().m_DirectInheritanceRelation)
			{
				i.second.m_pMetaData->m_SerializeAction(i.second.CastToMetaObject(obj.T::CastToMetaObject()), si);
			}
			for (auto& i : T::GetMetaDataCore().m_MemberVariable)
			{
				i.second.m_pMetaData->m_SerializeAction(i.second.CastToMetaObject(obj.T::CastToMetaObject()), si);
			}
		}
	};

	template<typename T>
	struct SerializeCore<T, false>
	{
		static void Run(T& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				SerializeMethod<T>::In(obj, si.Read());
			}
			else
			{
				si.Write(SerializeMethod<T>::Out(obj));
			}
		}
	};

	template<typename T>
	inline void Serialize(T& obj, SerializeInterface& si)
	{
		SerializeCore<T, IfHaveGetMetaDataMethod<T>::Result>::Run(obj, si);
	}

	template<typename T>
	inline SerializeActionType GetDefaultSerializeAction()
	{
		return [](const MetaObject& obj, SerializeInterface& si)
		{
			Serialize(*obj.Cast<T>(), si);
		};
	}

	//pointer sereialize method
	template<typename T>
	struct SerializeMethod<T*>
	{
		static void In(T*& ptr, const String& str)
		{
			unsigned long number = std::stoul(StringToStdString(str));
			ptr = (T*)number;
		}
		static String Out(T*& ptr)
		{
			unsigned long number = (unsigned long)ptr;
			return StdStringToString(std::to_string(number));
		}
	};

	//int serialize method
	template<>
	struct SerializeMethod<int>
	{
		static void In(int& i, const String& str)
		{
			i = std::stoi(StringToStdString(str));
		}
		static String Out(int& i)
		{
			return StdStringToString(std::to_string(i));
		}
	};

	//String serialize method
	template<>
	struct SerializeMethod<String>
	{
		static void In(String& s, const String& str)
		{
			s = str;
		}
		static String Out(String& s)
		{
			return s;
		}
	};
}