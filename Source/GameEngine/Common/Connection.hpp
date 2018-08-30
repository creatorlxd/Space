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
	private:
		void Clear()
		{
			if (m_pContent)
				m_pContent->Data<T>::DeleteConnection(m_Connection);
			m_pContent = nullptr;
		}

		void Reset(T* ptr)
		{
			if (ptr == m_pContent)
				return;
			if (ptr)
			{
				Clear();
				m_pContent = ptr;
				ptr->Data<T>::AddConnection(m_Connection);
			}
			else
				Clear();
		}
	public:
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
				ptr->Data<T>::AddConnection(m_Connection);
			}
		}
		ConnectionCore(ConnectionCore& other) = delete;
		ConnectionCore(ConnectionCore&& other) = delete;
		ConnectionCore& operator =(ConnectionCore& other) = delete;
		ConnectionCore& operator =(ConnectionCore&& other) = delete;
		virtual ~ConnectionCore()
		{
			if (m_pContent)
				m_pContent->Data<T>::DeleteConnection(m_Connection);
		}
		ConnectionCore& operator = (T* ptr)
		{
			if (ptr != m_pContent)
				Reset(ptr);
			return *this;
		}
		T& operator *()
		{
			return *m_pContent;
		}
		T* operator ->()
		{
			return m_pContent;
		}
		T* Get()
		{
			return m_pContent;
		}
	public:
		template<typename>
		class OnNotifyAction;		//do not use

		template<typename R, typename... Arg>
		class OnNotifyAction<R(Arg...)>
		{
		public:
			using FuncType = R(Arg...);

			OnNotifyAction()
			{
				m_Action = [](Arg... arg)->R {return R(); };	//default
			}
			template<typename... Arg>
			void operator () (Arg&&... arg)
			{
				m_Action(std::forward<Arg>(arg)...);
			}
			OnNotifyAction & operator = (const std::function<FuncType>& func)
			{
				m_Action = func;
				return *this;
			}
		private:
			std::function<FuncType> m_Action;
		};
	private:
		T * m_pContent;
		Connection<T>& m_Connection;
	};

	template<typename T>
	class Connection :public ConnectionCore<T>
	{
	public:
		Connection() :ConnectionCore<T>(*this)
		{}
		Connection(T* ptr) :ConnectionCore<T>(*this, ptr)
		{}
		Connection& operator = (T* ptr)
		{
			ConnectionCore<T>::operator = (ptr);
			return *this;
		}
		Connection(Connection& other) = delete;
		Connection(Connection&& other) = delete;
		Connection& operator =(Connection& other) = delete;
		Connection& operator =(Connection&& other) = delete;
	};

#define CONNECTION_BEGIN(type) \
template<> \
class SpaceGameEngine::Connection<type>:public SpaceGameEngine::ConnectionCore<type> \
{ \
public: \
Connection<type>():ConnectionCore<type>(*this){} \
Connection<type>(type* ptr):ConnectionCore<type>(*this,ptr){} \
Connection<type>(Connection<type>& other) = delete;\
Connection<type>(Connection<type>&& other) = delete;\
Connection<type>& operator =(Connection<type>& other) = delete;\
Connection<type>& operator =(Connection<type>&& other) = delete;\
Connection<type>& operator = (type* ptr) \
{ \
ConnectionCore<type>::operator = (ptr); \
return *this; \
}
#define CONNECTION_END }

}
