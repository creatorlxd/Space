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
#include <mutex>
#include "MemoryManager/AllocatorForSTL.hpp"
#include "Error.h"

namespace SpaceGameEngine
{
	template<typename T>
	class Observer;

	/*!
	@brief 用于响应被观察者所发出的消息的函数
	@param 函数的参数类型
	*/
	template<typename... T>
	class RespondFunction :public std::function<void(T...)>
	{
	public:
		RespondFunction()
			:std::function<void(T...)>([]()->void {})
		{}
		RespondFunction& operator = (const std::function<void(T...)>& func)
		{
			std::function<void(T...)>::operator = (func);
			return *this;
		}
	};

	/*!
	@brief 观察者模式中的被观察对象
	@warning 子类T必须继承于Subject<T>
	*/
	template<typename T>
	class Subject
	{
	public:
		friend class Observer<T>;
		Subject()
		{

		}
		~Subject()
		{
			std::lock_guard<std::mutex> locker(m_Mutex);
			for (auto i : m_Content)
			{
				i->m_RespondSubjectRelease();
				i->m_pSubject = nullptr;
			}
		}
	private:
		void AddObserver(Observer<T>& ob)
		{
			std::lock_guard<std::mutex> locker(m_Mutex);
			m_Content.push_back(&ob);
		}
		void DeleteObserver(Observer<T>& ob)
		{
			std::lock_guard<std::mutex> locker(m_Mutex);
			auto iter = std::find(m_Content.begin(), m_Content.end(), &ob);
			if (iter == m_Content.end())
			{
				THROW_ERROR("can not delete this observer");
				return;
			}
			m_Content.erase(iter);
		}
	protected:
		Vector<Observer<T>*> m_Content;
		std::mutex m_Mutex;
	};

/*!
@brief 向观察者发出用于触发的消息（即触发观察者的相应的响应函数）
@attention 只能在观察者子类中调用
@prama 当前的观察者子类的类型
@prama 被触发的消息（即Observer中的对应的响应函数）
@prama 被触发的消息的参数（即Observer中的对应的响应函数的参数）
@note 实际上就是直接调用观察者的响应函数。
*/
#define SUBJECT_NOTIFY(type,func,...)\
SpaceGameEngine::Subject<type>::m_Mutex.lock();\
for(auto i:SpaceGameEngine::Subject<type>::m_Content)\
{\
i->##func(##__VA_ARGS__##);\
}\
SpaceGameEngine::Subject<type>::m_Mutex.unlock();

	/*！
	@brief 观察者模式中的观察者对象
	*/
	template<typename T>
	class Observer
	{
	public:
		friend class Subject<T>;
		Observer()
		{
			m_pSubject = nullptr;
		}
		/*!
		@brief 清空观察者的观察对象
		*/
		void Clear()
		{
			if (m_pSubject)
			{
				m_pSubject->DeleteObserver(*this);
				m_pSubject = nullptr;
			}
		}
		/*!
		@brief 重设观察者的观察对象
		@param 指向被观察者的指针（可为nullptr）
		*/
		void Reset(Subject<T>* ptr)
		{
			if (ptr&&ptr != m_pSubject)
			{
				Clear();
				m_pSubject = ptr;
				m_pSubject->AddObserver(*this);
			}
			else if (ptr == nullptr)
				Clear();
		}
		Observer(Subject<T>* ptr)
		{
			m_pSubject = ptr;
			if (m_pSubject)
				m_pSubject->AddObserver(*this);
		}
		~Observer()
		{
			Clear();
		}
	public:
		/*!
		@brief 响应被观察者的释放
		@attention 该响应是在被观察者已被销毁后触发的
		*/
		RespondFunction<> m_RespondSubjectRelease;
	private:
		Subject<T>* m_pSubject;
	};
/*!
@brief 观察者可响应的消息列表的定义的开始
@param 被观察者的类型
@note 实际上就是对Observer的特例化
@attention 需与OBSERVER_RESPOND_LIST_END配合使用
@see OBSERVER_RESPOND_LIST_END
*/
#define OBSERVER_RESPOND_LIST_BEGIN(type)\
namespace SpaceGameEngine{\
template<>\
class Observer<type>\
{\
public:\
	friend class Subject<type>;\
	Observer<type>()\
	{\
		m_pSubject = nullptr;\
	}\
	void Clear()\
	{\
		if (m_pSubject)\
		{\
			m_pSubject->DeleteObserver(*this);\
			m_pSubject = nullptr;\
		}\
	}\
	void Reset(Subject<type>* ptr)\
	{\
		if (ptr&&ptr != m_pSubject)\
		{\
			Clear();\
			m_pSubject = ptr;\
			m_pSubject->AddObserver(*this);\
		}\
		else if (ptr == nullptr)\
			Clear();\
	}\
	Observer<type>(Subject<type>* ptr)\
	{\
		m_pSubject = ptr;\
		if (m_pSubject)\
			m_pSubject->AddObserver(*this);\
	}\
	~Observer<type>()\
	{\
		Clear();\
	}\
public:\
	RespondFunction<> m_RespondSubjectRelease;\
private:\
	Subject<type>* m_pSubject;\
public:

/*!
@brief 观察者可响应的消息列表的定义的结束
@attention 需与OBSERVER_RESPOND_LIST_BEGIN配合使用
@see OBSERVER_RESPOND_LIST_BEGIN
*/
#define OBSERVER_RESPOND_LIST_END \
};}

}