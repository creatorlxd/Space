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
#include "Data.hpp"

namespace SpaceGameEngine
{
	template<typename T>
	class ConnectionCore
	{
	public:
		friend class Data<T>;

		void Clear()
		{
			if (m_pContent)
				m_pContent->DeleteConnection(m_Connection);
			m_pContent = nullptr;
		}

		void Reset(T* ptr)
		{
			if (ptr)
			{
				Clear();
				m_pContent = ptr;
				ptr->AddConnection(m_Connection);
			}
			else
				Clear();
		}

		ConnectionCore() = delete;
		ConnectionCore(Connection<T>& connect) :m_Connection(connect)
		{
			m_pContent = nullptr;
		}
		ConnectionCore(Connection<T>& connect, T* ptr) :m_Connection(connect)
		{
			m_pContent = ptr;
			if (ptr)
			{
				ptr->AddConnection(m_Connection);
			}
		}
		virtual ~ConnectionCore()
		{
			if (m_pContent)
				m_pContent->DeleteConnection(m_Connection);
		}
		ConnectionCore& operator = (T* ptr)
		{
			Reset(ptr);
		}
		T& operator *()
		{
			return *m_pContent;
		}
		T* operator ->()
		{
			return m_pContent;
		}
		void Notify()
		{
			while (!m_NotifyActionQueue.empty())
			{
				m_NotifyActionQueue.front()();
				m_NotifyActionQueue.pop();
			}
		}
	public:
		template<typename FuncType = void()>
		class OnNotifyAction
		{
		public:
			OnNotifyAction() = delete;
			OnNotifyAction(ConnectionCore<T>& connect) :m_Connection(connect)
			{
				m_Action = [&]() {};
			}
			template<typename... Arg>
			void operator () (Arg&&... arg)
			{
				m_Connection.m_NotifyActionQueue.push(std::bind(m_Action, std::forward<Arg>(arg)...));
			}
			OnNotifyAction & operator = (const std::function<FuncType>& func)
			{
				m_Action = func;
				return *this;
			}
		private:
			std::function<FuncType> m_Action;
			ConnectionCore<T>& m_Connection;
		};
	private:
		T * m_pContent;
		Connection<T>& m_Connection;
		Queue < std::function<void()>> m_NotifyActionQueue;
	};

	template<typename T>
	class Connection :public ConnectionCore<T>
	{
	public:
		Connection() :ConnectionCore(*this)
		{}
		Connection(T* ptr) :ConnectionCore(*this, ptr)
		{}
	};

/*
Connection<T>的构造函数
用来初始化自定义的OnNotifyAction
example:
CONNECTION_CONSTRUCTOR(test_type,OnNotifyTest(*this));
*/
#define CONNECTION_CONSTRUCTOR(type,...) \
Connection<type>():ConnectionCore<type>(*this),__VA_ARGS__{}\
Connection<type>(type* ptr):ConnectionCore<type>(*this,ptr),__VA_ARGS__{}
}