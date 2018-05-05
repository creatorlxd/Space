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
		static String Out(const T& obj) = 0;
	};

	template<typename T, bool b>
	struct SerializeCore
	{

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
				if (i.second.m_IfSerialize)
					i.second.m_pMetaData->m_SerializeAction(i.second.CastToMetaObject(obj.T::CastToMetaObject()), si);
			}
		}

		static void Run(const T& obj, SerializeInterface& si)
		{
			SerializeCore<T, IfHaveGetMetaDataMethod<T>::Result>::Run(const_cast<typename std::decay<T>::type&>(obj), si);
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

		static void Run(const T& obj, SerializeInterface& si)
		{
			SerializeCore<T, IfHaveGetMetaDataMethod<T>::Result>::Run(const_cast<typename std::decay<T>::type&>(obj), si);
		}
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

	/*
	serialize container
	*/
	template<typename T>
	struct SerializeCore<Vector<T>, false>
	{
		static void Run(Vector<T>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				Serialize(size, si);
				obj.resize(size);
				for (size_t i = 0; i < size; i++)
					Serialize(obj[i], si);
			}
			else
			{
				size_t size = obj.size();
				Serialize(size, si);
				for (auto& i : obj)
				{
					Serialize(i, si);
				}
			}
		}
	};

	template<typename Key, typename Value>
	struct SerializeCore<Map<Key, Value>, false>
	{
		static void Run(Map<Key, Value>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				Serialize(size, si);
				std::pair<Key, Value> buff;
				for (size_t i = 0; i < size; i++)
				{
					Serialize(buff.first, si);
					Serialize(buff.second, si);
					obj.emplace(std::move(buff));
				}
			}
			else
			{
				size_t size = obj.size();
				Serialize(size, si);
				for (auto& i : obj)
				{
					Serialize(i.first, si);
					Serialize(i.second, si);
				}
			}
		}
	};

	template<typename Key, typename Value>
	struct SerializeCore<HashMap<Key, Value>, false>
	{
		static void Run(HashMap<Key, Value>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				Serialize(size, si);
				std::pair<Key, Value> buff;
				for (size_t i = 0; i < size; i++)
				{
					Serialize(buff.first, si);
					Serialize(buff.second, si);
					obj.emplace(std::move(buff));
				}
			}
			else
			{
				size_t size = obj.size();
				Serialize(size, si);
				for (auto& i : obj)
				{
					Serialize(i.first, si);
					Serialize(i.second, si);
				}
			}
		}
	};

	template<typename T>
	inline void Serialize(T& obj, SerializeInterface& si)
	{
		SerializeCore<std::decay<T>::type, IfHaveGetMetaDataMethod<T>::Result>::Run(obj, si);
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
			unsigned long long number = std::stoull(StringToStdString(str));
			ptr = (T*)number;
		}
		static String Out(T*const& ptr)
		{
			unsigned long long number = (unsigned long long)ptr;
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
		static String Out(const int& i)
		{
			return StdStringToString(std::to_string(i));
		}
	};

	//unsigned int serialize method
	template<>
	struct SerializeMethod<unsigned int>
	{
		static void In(unsigned int& ui, const String& str)
		{
			ui = std::stoul(StringToStdString(str));
		}
		static String Out(const unsigned int& ui)
		{
			return StdStringToString(std::to_string(ui));
		}
	};

	//unsigned long long serialize method
	template<>
	struct SerializeMethod<unsigned long long>
	{
		static void In(unsigned long long& ull, const String& str)
		{
			ull = std::stoull(StringToStdString(str));
		}
		static String Out(const unsigned long long& ull)
		{
			return StdStringToString(std::to_string(ull));
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
		static String Out(const String& s)
		{
			return s;
		}
	};
}