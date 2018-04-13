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
			for (auto i : m_Connection)
				i->m_pContent = nullptr;
		}

		/*
		通知各个链接开始运行积攒的惰性OnNotifyAction
		*/
		void NotifyConnection()
		{
			for (auto& i : m_Connection)
			{
				i->Notify();
			}
		}
	private:
		void AddConnection(Connection<T>& connect)
		{
			m_Connection.push_back(&connect);
		}
		void DeleteConnection(Connection<T>& connect)
		{
			auto iter = std::find(m_Connection.begin(), m_Connection.end(), &connect);
			if (iter != m_Connection.end())
				m_Connection.erase(iter);
			else
				THROWERROR("do not have this connection");
		}
	protected:
		Vector<Connection<T>*> m_Connection;
	};

/*
这种notify是惰性的
可以避免多余的重复的notify
需要调用connection的Notify()或Data<T>的NotifyConnection来执行上次Notify()之后的积攒的惰性的OnNotifyAction
*/
#define DATA_NOTIFY(method,arg)\
for(auto& i:m_Connection)\
{\
	i->method##arg;\
}
/*
这种notify是及时的
*/
#define DATA_NOTIFY_AT_ONCE(method,arg)\
for(auto& i:m_Connection)\
{\
	i->method##arg;\
	i->Notify();\
}
}