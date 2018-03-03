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
#include <map>
#include <typeinfo>
#include <vector>

namespace SpaceGameEngine
{
	static std::map<std::string, void*> s_InitializationMap;		//初始值表

	inline void InitInitializationMap()			//初始化初始值表
	{
		s_InitializationMap[typeid(int).name()] = new int(0);
		s_InitializationMap[typeid(float).name()] = new float(0.00f);
		s_InitializationMap[typeid(double).name()] = new double(0.00f);
		s_InitializationMap[typeid(char).name()] = new char(char(0));
		s_InitializationMap[typeid(bool).name()] = new bool(false);
	}

	inline void ReleaseInitializationMap()		//释放初始值表
	{
		for (auto i : s_InitializationMap)
		{
			delete i.second;
		}
	}
	template <typename T>
	inline void GetInitialization(T** c)		//获取该类型的初始值
	{
		auto i = s_InitializationMap.find(typeid(*(*c)).name());
		if (i != s_InitializationMap.end())
		{
			memcpy(*c, (*i).second, sizeof(T));
		}
		else
		{
			s_InitializationMap.insert(std::make_pair(typeid(T).name(), new T()));
			memcpy(*c, s_InitializationMap[typeid(T).name()], sizeof(T));
		}
	}
	template <typename T>
	inline void GetInitialization(std::pair<T**, size_t> c)		//获取该类型的初始值
	{
		auto i = s_InitializationMap.find(typeid(*(*(c.first))).name());
		if (i != s_InitializationMap.end())
		{
			memcpy(*(c.first), (*i).second, c.second * sizeof(T));
		}
		else
		{
			s_InitializationMap.insert(std::make_pair(typeid(T).name(), new T()));
			memcpy(*(c.first), s_InitializationMap[typeid(T).name()], c.second * sizeof(T));
		}
	}

	struct MemoryBlock	//内存块的信息
	{
		void* m_Address;
		size_t m_Size;
		MemoryBlock()
		{
			m_Address = NULL;
			m_Size = 0;
		}
		MemoryBlock(void* address, size_t size)
		{
			m_Address = address;
			m_Size = size;
		}
	};

	bool operator < (const MemoryBlock& m1, const MemoryBlock& m2)
	{
		return (m1.m_Address < m2.m_Address);
	}

	void CleanMemoryBlock(const MemoryBlock& mb)
	{
		memset(mb.m_Address, NULL, mb.m_Size);
	}

	class MemoryManager		//内存管理器（是唯一的）
	{
	protected:
		std::vector<MemoryBlock> m_Memories;
		std::vector<MemoryBlock> m_MemoryBlocks;
		std::vector<MemoryBlock> m_FreeMemoryBlocks;
	public:
		static const size_t m_MemorySize = 0xffffff;
		MemoryManager()
		{
			InitInitializationMap();
		}

		~MemoryManager()
		{
			for (auto i : m_Memories)
			{
				free(i.m_Address);
			}
			ReleaseInitializationMap();
		}

		template<typename T>
		bool ReuseMemory(T** dest)
		{
			if (m_FreeMemoryBlocks.size() == 0)
				return false;
			else
			{
				for (std::vector<MemoryBlock>::iterator i = m_FreeMemoryBlocks.begin(); i != m_FreeMemoryBlocks.end(); i += 1)
				{
					if ((*i).m_Size >= sizeof(T))
					{
						MemoryBlock m((*i).m_Address, sizeof(T));
						m_MemoryBlocks.push_back(m);
						*dest = (T*)((*i).m_Address);
						CleanMemoryBlock(m);
						GetInitialization(dest);
						if ((*i).m_Size == sizeof(T))
						{
							m_FreeMemoryBlocks.erase(i);
						}
						else
						{
							(*i).m_Address = *dest + sizeof(T);
							(*i).m_Size -= sizeof(T);
						}
						return true;
					}
				}
			}
			return false;
		}

		template<typename T>
		bool ReuseMemory(std::pair<T**, size_t> c)
		{
			if (m_FreeMemoryBlocks.size() == 0)
				return false;
			else
			{
				for (std::vector<MemoryBlock>::iterator i = m_FreeMemoryBlocks.begin(); i != m_FreeMemoryBlocks.end(); i += 1)
				{
					if ((*i).m_Size >= c.second * sizeof(T))
					{
						MemoryBlock m((*i).m_Address, c.second * sizeof(T));
						m_MemoryBlocks.push_back(m);
						*c.first = (T*)((*i).m_Address);
						CleanMemoryBlock(m);
						GetInitialization(c);
						if ((*i).m_Size == c.second * sizeof(T))
						{
							m_FreeMemoryBlocks.erase(i);
						}
						else
						{
							(*i).m_Address = *c.first + c.second * sizeof(T);
							(*i).m_Size -= c.second * sizeof(T);
						}
						return true;
					}
				}
			}
			return false;
		}

		template<typename T>
		void NewObject(T** dest)
		{
			if (!ReuseMemory(dest))
			{
				if (sizeof(T) > m_MemorySize)
				{
					MemoryBlock m;
					m.m_Address = malloc(sizeof(T));
					m.m_Size = sizeof(T);
					m_Memories.push_back(m);
					m_FreeMemoryBlocks.push_back(m);
					ReuseMemory(dest);
				}
				else
				{
					MemoryBlock m;
					m.m_Address = malloc(m_MemorySize);
					m.m_Size = m_MemorySize;
					m_Memories.push_back(m);
					m_FreeMemoryBlocks.push_back(m);
					ReuseMemory(dest);
				}
			}
		}

		template<typename T, typename... TS>
		void NewObject(T** dest, TS**... ts)
		{
			NewObject(dest);
			NewObject(ts...);
		}

		template<typename T>
		void NewObject(std::pair<T**, size_t> c)
		{
			if (!ReuseMemory(c))
			{
				if (c.second * sizeof(T) > m_MemorySize)
				{
					MemoryBlock m;
					m.m_Address = malloc(c.second * sizeof(T));
					m.m_Size = c.second * sizeof(T);
					m_Memories.push_back(m);
					m_FreeMemoryBlocks.push_back(m);
					ReuseMemory(c);
				}
				else
				{
					MemoryBlock m;
					m.m_Address = malloc(m_MemorySize);
					m.m_Size = m_MemorySize;
					m_Memories.push_back(m);
					m_FreeMemoryBlocks.push_back(m);
					ReuseMemory(c);
				}
			}
		}

		template<typename T>
		bool ReleaseObject(T** dest)
		{
			for (std::vector<MemoryBlock>::iterator i = m_MemoryBlocks.begin(); i != m_MemoryBlocks.end(); i += 1)
			{
				if ((*i).m_Address == *dest)
				{
					m_FreeMemoryBlocks.push_back(*i);
					m_MemoryBlocks.erase(i);
					(*dest)->~T();
					*dest = NULL;
					return true;
				}
			}
			return false;
		}

		template<typename T, typename... TS>
		bool ReleaseObject(T** dest, TS**... ts)
		{
			return (Release(dest)&Release(ts...));
		}

	};

	template<typename T>
	class Pointer			//使用内存管理器的指针
	{
	protected:
		MemoryManager& m_MemoryManager;
		T* m_pContent;
	public:
		Pointer(MemoryManager& m) :m_MemoryManager(m), m_pContent(NULL) {}
		~Pointer()
		{
			if (m_pContent)
				m_MemoryManager.ReleaseObject(&m_pContent);
		}
		void InitUnit()
		{
			m_MemoryManager.NewObject(&m_pContent);
		}
		void InitArray(size_t size)
		{
			m_MemoryManager.NewObject(std::make_pair(&m_pContent, size));
		}
		bool operator = (const Pointer&) = delete;
		T& operator * ()
		{
			return *m_pContent;
		}
		T& operator [] (size_t i)
		{
			return *(m_pContent + i);
		}
	};

	template<typename T>
	class UnitPointer :public Pointer<T>	//指向单个对象的指针
	{
	public:
		UnitPointer(MemoryManager& m) :Pointer<T>(m)
		{
			Pointer<T>::InitUnit();
		}
	};

	template<typename T>
	class ArrayPointer :public Pointer<T>	//指向多个对象形成的数组的指针
	{
	public:
		ArrayPointer(MemoryManager& m, size_t size) :Pointer<T>(m)
		{
			Pointer<T>::InitArray(size);
		}
	};

}