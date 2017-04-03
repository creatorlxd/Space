#pragma once
#include "stdafx.h"

static std::map<std::string,void*> s_InitializationMap;		//初始值表

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
	auto i = find(s_InitializationMap.begin(), s_InitializationMap.end(), typeid(*(*c)).name());
	if (i != s_InitializationMap.end())
	{
		memcpy(*c, (*i).second, sizeof(T));
	}
	else
	{
		s_InitializationMap.insert(make_pair(typeid(T).name(), new T()));
		memcpy(*c, s_InitializationMap[typeid(T).name()], sizeof(T));
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

void CleanMemoryBlock(const MemoryBlock& mb)
{
	memset(mb.m_Address, NULL, mb.m_Size);
}

class MemoryManager		//内存管理器（基于栈，且是唯一的）
{
protected:
	size_t m_Top;
	void* m_Memory;
	std::vector<MemoryBlock> m_MemoryBlocks;
	std::vector<MemoryBlock> m_FreeMemoryBlocks;
public:
	static const size_t m_MemorySize = 0xffff;
	MemoryManager()
	{
		m_Memory = malloc(m_MemorySize);
		m_Top = 0;
		InitInitializationMap();
	}

	~MemoryManager()
	{
		free(m_Memory);
		m_Memory = NULL;
		ReleaseInitializationMap();
	}

	template<typename T>
	bool ReuseMemory(T** dest)
	{
		if (m_FreeMemoryBlocks.size() == 0)
			return false;
		else
		{
			for (vector<MemoryBlock>::iterator i = m_FreeMemoryBlocks.begin(); i != m_FreeMemoryBlocks.end(); i += 1)
			{
				if ((*i).m_Size >= sizeof(T))
				{
					m_MemoryBlocks.push_back(MemoryBlock((*i).m_Address, sizeof(T)));
					*dest = (T*)((*i).m_Address);
					CleanMemoryBlock(m_MemoryBlocks[m_MemoryBlocks.size() - 1]);
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
			for (vector<MemoryBlock>::iterator i = m_FreeMemoryBlocks.begin(); i != m_FreeMemoryBlocks.end(); i += 1)
			{
				if ((*i).m_Size >= c.second * sizeof(T))
				{
					m_MemoryBlocks.push_back(MemoryBlock((*i).m_Address, c.second * sizeof(T)));
					*c.first = (T*)((*i).m_Address);
					CleanMemoryBlock(m_MemoryBlocks[m_MemoryBlocks.size() - 1]);
					GetInitialization(dest);
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
			m_MemoryBlocks.push_back(MemoryBlock(m_Memory + m_Top, sizeof(T)));
			*dest = (T*)(m_Memory + m_Top);
			CleanMemoryBlock(m_MemoryBlocks[m_MemoryBlocks.size() - 1]);
			GetInitialization(dest);
			m_Top += sizeof(T);
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
			m_MemoryBlocks.push_back(MemoryBlock(m_Memory + m_Top, c.second * sizeof(T)));
			*c.first = (T*)(m_Memory + m_Top);
			CleanMemoryBlock(m_MemoryBlocks[m_MemoryBlocks.size() - 1]);
			GetInitialization(dest);
			m_Top += c.second * sizeof(T);
		}
	}

	template<typename T>
	bool ReleaseObject(T** dest)
	{
		for (vector<MemoryBlock>::iterator i = m_MemoryBlocks.begin(); i != m_MemoryBlocks.end(); i += 1)
		{
			if ((*i).m_Address == *dest)
			{
				m_FreeMemoryBlocks.push_back(*i);
				m_MemoryBlocks.erase(i);
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
	Pointer(MemoryManager& m) :m_MemoryManager(m),m_pContent(NULL){}
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
		m_MemoryManager.NewObject(make_pair(&m_pContent, size));
	}
	bool operator = (const Pointer&) = delete;
	T& operator * ()
	{
		return *m_pContent;
	}
};

template<typename T>
class UnitPointer :public Pointer<T>	//指向单个对象的指针
{
	UnitPointer(MemoryManager& m) :Pointer(m)
	{
		InitUnit();
	}
	~UnitPointer()
	{
		~Pointer();
	}
};

template<typename T>
class ArrayPointer :public Pointer<T>	//指向多个对象形成的数组的指针
{
	ArrayPointer(MemoryManager& m,size_t size) :Pointer(m)
	{
		InitArray(size);
	}
	~ArrayPointer()
	{
		~Pointer();
	}
};