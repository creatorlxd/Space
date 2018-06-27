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
#include "MemoryManager/AllocatorForSTL.hpp"
#include "Error.h"
#include <mutex>

namespace SpaceGameEngine
{
	template<typename T>
	class ConnectionCore;

	template<typename T>
	class Connection;

	template<typename T>
	class Data
	{
	public:
		friend class ConnectionCore<T>;

		virtual ~Data()
		{
			std::lock_guard<std::mutex> locker(m_Mutex);
			for (auto i : m_Connection)
				i->m_pContent = nullptr;
		}
	private:
		void AddConnection(Connection<T>& connect)
		{
			std::lock_guard<std::mutex> locker(m_Mutex);
			m_Connection.insert(m_Connection.end(), &connect);
		}
		void DeleteConnection(Connection<T>& connect)
		{
			std::lock_guard<std::mutex> locker(m_Mutex);
			auto iter = std::find(m_Connection.begin(), m_Connection.end(), &connect);
			if (iter != m_Connection.end())
				m_Connection.erase(iter);
			else
				THROW_ERROR("do not have this connection");
		}
	protected:
		List<Connection<T>*> m_Connection;
		std::mutex m_Mutex;
	};

#define DATA_NOTIFY(scope,method,...)\
scope::m_Mutex.lock();\
for(auto i:scope::m_Connection)\
{\
	i->method##(__VA_ARGS__);\
}\
scope::m_Mutex.unlock();
}