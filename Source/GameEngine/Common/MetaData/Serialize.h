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
	class SerializeObjectManager
	{
	public:
		template<typename T, bool b>
		friend struct SerializeCore;
		template<typename T>
		friend inline void Serialize(T& obj, SerializeInterface& si);
		friend class MemoryManager;

		~SerializeObjectManager();
	private:
		SerializeObjectManager();

		void AddObject(void* ptr, void* now_ptr);
		void QueryObject(void* query_ptr, void ** ptr);
	private:
		Map<void*, void*> m_ObjectMap;
		Map<void*, Vector<void**>> m_QueryList;
	};

	SerializeObjectManager& GetSerializeObjectManager();

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
		IOFlag GetIOFlag();

		template<typename T, bool b>
		friend struct SerializeCore;
	private:
		virtual String Read() = 0;
		virtual void Write(const String& str) = 0;
	private:
		IOFlag m_IOFlag;
	};

	template<typename T>
	inline void Serialize(T& obj, SerializeInterface& si);

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
	struct SerializeCore<T*, false>	//pointer serialize
	{
		static void Run(T*& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				T* ptr = nullptr;
				SerializeMethod<T*>::In(ptr, si.Read());
				if (ptr)
					GetSerializeObjectManager().QueryObject(ptr, (void**)&obj);
				else
					obj = ptr;
			}
			else
			{
				si.Write(SerializeMethod<T*>::Out(obj));
			}
		}
	};

	template<typename T>
	struct SerializeCore<T*, true>	//pointer serialize:just serialize ptr directly
	{
		static void Run(T*& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				SerializeMethod<T*>::In(obj, si.Read());
			}
			else
			{
				si.Write(SerializeMethod<T*>::Out(obj));
			}
		}
	};

	/*
	serialize vector
	*/
	template<typename T>
	struct SerializeCore<Vector<T>, false>
	{
		static void Run(Vector<T>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t,false>::Run(size, si);
				obj.resize(size);
				for (size_t i = 0; i < size; i++)
					Serialize(obj[i], si);
			}
			else
			{
				size_t size = obj.size();
				SerializeCore<size_t, false>::Run(size, si);
				for (auto& i : obj)
				{
					Serialize(i, si);
				}
			}
		}
	};

	/*
	serialize map
	copy no safe
	*/
	template<typename Key, typename Value>
	struct SerializeCore<Map<Key, Value>, false>
	{
		static void Run(Map<Key, Value>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t, false>::Run(size, si);
				std::pair<Key, Value> buff;
				Key* buffptr1;
				Value* buffptr2;
				for (size_t i = 0; i < size; i++)
				{
					SerializeCore<Key*, true>::Run(buffptr1, si);
					SerializeCore<Key,IfHaveGetMetaDataMethod<Key>::Result>::Run(buff.first, si);
					SerializeCore<Value*, true>::Run(buffptr2, si);
					SerializeCore<Value,IfHaveGetMetaDataMethod<Value>::Result>::Run(buff.second, si);
					auto iterpair = obj.emplace(std::move(buff));
					GetSerializeObjectManager().AddObject(buffptr1, const_cast<Key*>(&iterpair.first->first));
					GetSerializeObjectManager().AddObject(buffptr2, &iterpair.first->second);
				}
			}
			else
			{
				size_t size = obj.size();
				SerializeCore<size_t, false>::Run(size, si);
				for (auto& i : obj)
				{
					Serialize(i.first, si);
					Serialize(i.second, si);
				}
			}
		}
	};

	/*
	serialize hashmap
	copy no safe
	*/
	template<typename Key, typename Value>
	struct SerializeCore<HashMap<Key, Value>, false>
	{
		static void Run(HashMap<Key, Value>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t, false>::Run(size, si);
				std::pair<Key, Value> buff;
				Key* buffptr1;
				Value* buffptr2;
				for (size_t i = 0; i < size; i++)
				{
					SerializeCore<Key*, true>::Run(buffptr1, si);
					SerializeCore<Key, IfHaveGetMetaDataMethod<Key>::Result>::Run(buff.first, si);
					SerializeCore<Value*, true>::Run(buffptr2, si);
					SerializeCore<Value, IfHaveGetMetaDataMethod<Value>::Result>::Run(buff.second, si);
					auto iterpair = obj.emplace(std::move(buff));
					GetSerializeObjectManager().AddObject(buffptr1, const_cast<Key*>(&iterpair.first->first));
					GetSerializeObjectManager().AddObject(buffptr2, &iterpair.first->second);
				}
			}
			else
			{
				size_t size = obj.size();
				SerializeCore<size_t, false>::Run(size, si);
				for (auto& i : obj)
				{
					Serialize(i.first, si);
					Serialize(i.second, si);
				}
			}
		}
	};

	/*
	serialize deque
	copy no safe
	data would be broken when serialize out
	*/
	template<typename T>
	struct SerializeCore<Deque<T>, false>
	{
		static void Run(Deque<T>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t, false>::Run(size, si);
				T buff;
				T* buffptr;
				for (size_t i = 0; i < size; i++)
				{
					SerializeCore<T*, true>::Run(buffptr, si);
					SerializeCore<T,IfHaveGetMetaDataMethod<T>::Result>::Run(buff, si);
					obj.emplace_back(std::move(buff));
					GetSerializeObjectManager().AddObject(buffptr, &obj.back());
				}
			}
			else
			{
				size_t size = obj.size();
				SerializeCore<size_t, false>::Run(size, si);
				for (size_t i = 0; i < size; i++)
				{
					Serialize(obj.front(), si);
					obj.pop_front();
				}
			}
		}
	};

	/*
	serialize queue
	copy no safe
	data would be broken when serialize out
	*/
	template<typename T>
	struct SerializeCore<Queue<T>, false>
	{
		static void Run(Queue<T>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t, false>::Run(size, si);
				T buff;
				T* buffptr;
				for (size_t i = 0; i < size; i++)
				{
					SerializeCore<T*, true>::Run(buffptr, si);
					SerializeCore<T,IfHaveGetMetaDataMethod<T>::Result>::Run(buff, si);
					obj.emplace(std::move(buff));
					GetSerializeObjectManager().AddObject(buffptr, &obj.back());
				}
			}
			else
			{
				size_t size = obj.size();
				SerializeCore<size_t, false>::Run(size, si);
				for (size_t i = 0; i < size; i++)
				{
					Serialize(obj.front(), si);
					obj.pop();
				}
			}
		}
	};

	/*
	serialize stack
	copy no safe
	data would be broken when serialize out
	*/
	template<typename T>
	struct SerializeCore<Stack<T>, false>
	{
		static void Run(Stack<T>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t, false>::Run(size, si);
				T buff;
				T* buffptr;
				for (size_t i = 0; i < size; i++)
				{
					SerializeCore<T*, true>::Run(buffptr, si);
					SerializeCore<T,IfHaveGetMetaDataMethod<T>::Result>::Run(buff, si);
					obj.emplace(std::move(buff));
					GetSerializeObjectManager().AddObject(buffptr, &obj.top());
				}
			}
			else
			{
				size_t size = obj.size();
				SerializeCore<size_t, false>::Run(size, si);
				Vector<std::pair<T,T*>> vec_buffer;
				while (!obj.empty())
				{
					vec_buffer.emplace_back(std::move(std::make_pair(std::move(obj.top()),&obj.top())));
					obj.pop();
				}
				for (auto i = vec_buffer.rbegin(); i != vec_buffer.rend(); i++)
				{
					SerializeCore<T*, true>::Run(i->second, si);
					SerializeCore<T, IfHaveGetMetaDataMethod<T>::Result>::Run(i->first, si);
				}
			}
		}
	};

	/*
	serialize list
	*/
	template<typename T>
	struct SerializeCore<List<T>, false>
	{
		static void Run(List<T>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t, false>::Run(size, si);
				obj.resize(size);
				for (auto& i : obj)
				{
					Serialize(i, si);
				}
			}
			else
			{
				size_t size = obj.size();
				SerializeCore<size_t, false>::Run(size, si);
				for (auto& i : obj)
				{
					Serialize(i, si);
				}
			}
		}
	};

	/*
	serialize forward_list
	*/
	template<typename T>
	struct SerializeCore<ForwardList<T>, false>
	{
		static void Run(ForwardList<T>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t, false>::Run(size, si);
				obj.resize(size);
				for (auto& i : obj)
				{
					Serialize(i, si);
				}
			}
			else
			{
				size_t size = std::distance(obj.begin(), obj.end());
				SerializeCore<size_t, false>::Run(size, si);
				for (auto& i : obj)
				{
					Serialize(i, si);
				}
			}
		}
	};

	/*
	serialize set
	copy no safe
	*/
	template<typename T>
	struct SerializeCore<Set<T>, false>
	{
		static void Run(Set<T>& obj, SerializeInterface& si)
		{
			if (si.m_IOFlag == SerializeInterface::IOFlag::Input)
			{
				size_t size;
				SerializeCore<size_t, false>::Run(size, si);
				T buff;
				T* buffptr;
				for (size_t i = 0; i < size; i++)
				{
					SerializeCore<T*, true>::Run(buffptr, si);
					SerializeCore<T,IfHaveGetMetaDataMethod<T>::Result>::Run(buff, si);
					auto iterpair = obj.emplace(std::move(buff));
					GetSerializeObjectManager().AddObject(buffptr, const_cast<T*>(&(*iterpair.first)));
				}
			}
			else
			{
				size_t size = obj.size();
				SerializeCore<size_t, false>::Run(size, si);
				for (auto& i : obj)
				{
					Serialize(i, si);
				}
			}
		}
	};

	template<typename T>
	inline void Serialize(T& obj, SerializeInterface& si)
	{
		T* ptr = &obj;
		SerializeCore<T*, true>::Run(ptr, si);
		if (si.GetIOFlag() == SerializeInterface::IOFlag::Input)
			GetSerializeObjectManager().AddObject(ptr, &obj);
		SerializeCore<T, IfHaveGetMetaDataMethod<T>::Result>::Run(obj, si);
	}

	template<typename T>
	inline void Serialize(const T& obj, SerializeInterface& si)
	{
		Serialize(const_cast<T&>(obj), si);
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

	//long long serialize method
	template<>
	struct SerializeMethod<long long>
	{
		static void In(long long& ll, const String& str)
		{
			ll = std::stoll(StringToStdString(str));
		}
		static String Out(const long long& ll)
		{
			return StdStringToString(std::to_string(ll));
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

	template<>
	struct SerializeMethod<float>
	{
		static void In(float& f, const String& str)
		{
			f = std::stof(StringToStdString(str));
		}
		static String Out(const float& f)
		{
			return StdStringToString(std::to_string(f));
		}
	};

	template<>
	struct SerializeMethod<double>
	{
		static void In(double& d, const String& str)
		{
			d = std::stod(StringToStdString(str));
		}
		static String Out(const double& d)
		{
			return StdStringToString(std::to_string(d));
		}
	};

	template<>
	struct SerializeMethod<bool>
	{
		static void In(bool& b, const String& str)
		{
			b = (str == "true" ? true : (str == "false" ? false : (THROWERROR("bool serialize error"), false)));
		}
		static String Out(const bool& b)
		{
			return (b ? "true" : "false");
		}
	};

	//char serialize method
	template<>
	struct SerializeMethod<char>
	{
		static void In(char& c, const String& str)
		{
			c = str[0];
		}
		static String Out(const char& c)
		{
			return String(1, c);
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