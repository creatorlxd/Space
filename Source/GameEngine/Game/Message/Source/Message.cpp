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
#include "stdafx.h"
#include "../Include/Message.h" 
using namespace SpaceGameEngine;

MessageManager* SpaceGameEngine::MessageManager::sm_pThis = nullptr;

SpaceGameEngine::Message::Message()
{
	m_ReceiverName = "Global";
	m_Content = 0;
}

SpaceGameEngine::Message::Message(unsigned int c)
{
	m_ReceiverName = "Global";
	m_Content = c;
}

SpaceGameEngine::Receiver::~Receiver()
{
	
}

void SpaceGameEngine::Receiver::ReceiveMessage(const Message & message)
{
	m_MessageQueue.push(message.m_Content);
}

void SpaceGameEngine::Receiver::ReceiveMessage(unsigned int message)
{
	m_MessageQueue.push(message);
}

unsigned int SpaceGameEngine::Receiver::TakeOutMessage()
{
	auto re = m_MessageQueue.front();
	m_MessageQueue.pop();
	return re;
}

bool SpaceGameEngine::Receiver::IfEmpty()
{
	return m_MessageQueue.empty();
}

size_t SpaceGameEngine::Receiver::Size()
{
	return m_MessageQueue.size();
}

void SpaceGameEngine::Receiver::Clear()
{
	m_MessageQueue = Queue<unsigned int>();
}

bool SpaceGameEngine::Receiver::IfHaveMessage(unsigned int c)
{
	bool re = false;
	for (size_t i = 1; i <= m_MessageQueue.size(); i++)
	{
		unsigned int buff = TakeOutMessage();
		if (buff == c)
		{
			re = true;
		}
		m_MessageQueue.push(buff);
	}
	return re;
}

SpaceGameEngine::MessageManager::MessageManager()
{
	sm_pThis = this;
	m_MaxSize = 256;
}

SpaceGameEngine::MessageManager::~MessageManager()
{
	if (sm_pThis == this)
	{
		sm_pThis = nullptr;
	}
	for (auto i : m_Receivers)
	{
		MemoryManager::Delete(i.second);
	}
}

void SpaceGameEngine::MessageManager::SetAsMainManager()
{
	sm_pThis = this;
}

MessageManager * SpaceGameEngine::MessageManager::GetMainManager()
{
	return sm_pThis;
}

void SpaceGameEngine::MessageManager::PushMessage(const Message & message)
{
	m_GlobalMessageQueue.push(message);
}

void SpaceGameEngine::MessageManager::Run()
{
	int cot = 1;
	while (!m_GlobalMessageQueue.empty()&&cot<=m_MaxSize)
	{
		auto m = m_GlobalMessageQueue.front();
		m_GlobalMessageQueue.pop();

		if (m.m_ReceiverName == "Global")
		{
			for (auto i : m_Receivers)
			{
				i.second->ReceiveMessage(m);
				cot += 1;
			}
		}
		else
		{
			cot += 1;
			auto rer = m_Receivers.find(m.m_ReceiverName);
			if (rer != m_Receivers.end())
			{
				(*rer).second->ReceiveMessage(m);
			}
			else
			{
				continue;
			}
		}
	}
}

bool SpaceGameEngine::MessageManager::DeleteReceiver(const std::string & name)
{
	auto i = m_Receivers.find(name);
	if (i != m_Receivers.end())
	{
		MemoryManager::Delete(i->second);
		m_Receivers.erase(i);
		return true;
	}
	else
	{
		ThrowError(L"没有该接收器");
		return false;
	}
}

bool SpaceGameEngine::MessageManager::DeleteReceiver(Receiver * pr)
{
	auto re = m_Receivers.end();
	for (auto i = m_Receivers.begin(); i != m_Receivers.end(); i++)
	{
		if ((*i).second == pr)
		{
			re = i;
			break;
		}
	}
	if (re == m_Receivers.end())
	{
		ThrowError(L"没有该接收器");
		return false;
	}
	else
	{
		m_Receivers.erase(re);
		return true;
	}
}

bool SpaceGameEngine::MessageManager::AddReceiver(const std::string & name, Receiver * pr)
{
	if (m_Receivers.find(name) != m_Receivers.end())
	{
		ThrowError(L"已存在该接收器");
		return false;
	}
	else
	{
		m_Receivers.insert(make_pair(name, pr));
		return true;
	}
}

Receiver * SpaceGameEngine::MessageManager::FindReceiver(const std::string & name)
{
	auto iter = m_Receivers.find(name);
	if (iter == m_Receivers.end())
	{
		return nullptr;
	}
	return (*iter).second;
}

std::string SpaceGameEngine::MessageManager::FindReceiverName(Receiver * pr)
{
	for (auto i = m_Receivers.begin(); i != m_Receivers.end(); i++)
	{
		if (i->second == pr)
		{
			return i->first;
		}
	}
	return std::string();
}

void SpaceGameEngine::MessageManager::SetMaxSize(int i)
{
	m_MaxSize = i;
}

SpaceGameEngine::Sender::Sender()
{
	m_Name = "Unkown";
}

SpaceGameEngine::Sender::Sender(const std::string & name)
{
	m_Name = name;
}

SpaceGameEngine::Sender::~Sender()
{

}

void SpaceGameEngine::Sender::ProduceMessage(const Message & message)
{
	if (!MessageManager::GetMainManager())
	{
		ThrowError(L"需要先定义一个消息管理器");
		return;
	}
	DebugLog(message);
	MessageManager::GetMainManager()->PushMessage(message);
}

void SpaceGameEngine::Sender::ProduceMessage(const std::string & name, unsigned int c)
{
	if (!MessageManager::GetMainManager())
	{
		ThrowError(L"需要先定义一个消息管理器");
		return;
	}
	DebugLog(Message(name, c));
	MessageManager::GetMainManager()->PushMessage(Message(name, c));
}

void SpaceGameEngine::Sender::ProduceMessage(MessageManager & manager, const Message & message)
{
	DebugLog(message);
	manager.PushMessage(message);
}

void SpaceGameEngine::Sender::ProduceMessages(const std::vector<std::string>& names, unsigned int c)
{
	if (!MessageManager::GetMainManager())
	{
		ThrowError(L"需要先定义一个消息管理器");
		return;
	}
	for (auto i : names)
	{
		DebugLog(Message(i, c));
		MessageManager::GetMainManager()->PushMessage(Message(i, c));
	}
}

void SpaceGameEngine::Sender::ProduceMessages(MessageManager & manager, const std::vector<std::string>& names, unsigned int c)
{
	for (auto i : names)
	{
		DebugLog(Message(i, c));
		manager.PushMessage(Message(i, c));
	}
}

void SpaceGameEngine::Sender::FastProduceMessage(Receiver & r, const Message & message)
{
	DebugLog(message);
	r.ReceiveMessage(message.m_Content);
}

void SpaceGameEngine::Sender::DebugLog(const Message & message)
{
#if defined(DEBUG) | defined(_DEBUG)
	//TODO:调用日志系统
#endif
}

void SpaceGameEngine::Sender::SetName(const std::string & name)
{
	m_Name = name;
}

std::string SpaceGameEngine::Sender::GetName()
{
	return m_Name;
}
