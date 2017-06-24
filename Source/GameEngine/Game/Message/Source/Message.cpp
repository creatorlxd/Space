#include "stdafx.h"
#include "../Include/Message.h" 

MessageManager* MessageManager::sm_pThis = nullptr;

Message::Message()
{
	m_ReceiverName = "Global";
	m_Content = 0;
}

Message::Message(int c)
{
	m_ReceiverName = "Global";
	m_Content = c;
}

void Receiver::ReceiveMessage(const Message & message)
{
	m_MessageQueue.push(message.m_Content);
}

void Receiver::ReceiveMessage(int message)
{
	m_MessageQueue.push(message);
}

Message Receiver::TakeOutMessage()
{
	auto re = m_MessageQueue.front();
	m_MessageQueue.pop();
	return re;
}

MessageManager::MessageManager()
{
	sm_pThis = this;
}

MessageManager::~MessageManager()
{
	Release();
}

void MessageManager::Release()
{
	if (sm_pThis == this)
	{
		sm_pThis = nullptr;
	}
	for (auto i : m_Receivers)
	{
		delete i.second;
	}
}

void MessageManager::SetAsMainManager()
{
	sm_pThis = this;
}

MessageManager * MessageManager::GetMainManager()
{
	return sm_pThis;
}

void MessageManager::PushMessage(const Message & message)
{
	m_GlobalMessageQueue.push(message);
}

void MessageManager::Run()
{
	while (!m_GlobalMessageQueue.empty())
	{
		auto m = m_GlobalMessageQueue.front();
		m_GlobalMessageQueue.pop();

		if (m.m_ReceiverName == "Global")
		{
			for (auto i : m_Receivers)
			{
				i.second->ReceiveMessage(m);
			}
		}
		else
		{
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

bool MessageManager::DeleteReceiver(const std::string & name)
{
	auto i = m_Receivers.find(name);
	if (i != m_Receivers.end())
	{
		m_Receivers.erase(i);
		return true;
	}
	else
	{
		ThrowError(L"没有该接收器");
		return false;
	}
}

bool MessageManager::DeleteReceiver(Receiver * pr)
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

bool MessageManager::AddReceiver(const std::string & name, Receiver * pr)
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

Receiver * MessageManager::FindReceiver(const std::string & name)
{
	auto iter = m_Receivers.find(name);
	if (iter == m_Receivers.end())
	{
		return nullptr;
	}
	return (*iter).second;
}

std::string MessageManager::FindReceiverName(Receiver * pr)
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

void Sender::ProduceMessage(const Message & message)
{
	if (!MessageManager::GetMainManager())
	{
		ThrowError(L"需要先定义一个消息管理器");
		return;
	}
	MessageManager::GetMainManager()->PushMessage(message);
}

void Sender::ProduceMessage(const std::string & name, int c)
{
	if (!MessageManager::GetMainManager())
	{
		ThrowError(L"需要先定义一个消息管理器");
		return;
	}
	MessageManager::GetMainManager()->PushMessage(Message(name, c));
}

void Sender::ProduceMessage(MessageManager & manager, const Message & message)
{
	manager.PushMessage(message);
}

void Sender::ProduceMessages(const std::vector<std::string>& names, int c)
{
	if (!MessageManager::GetMainManager())
	{
		ThrowError(L"需要先定义一个消息管理器");
		return;
	}
	for (auto i : names)
	{
		MessageManager::GetMainManager()->PushMessage(Message(i, c));
	}
}

void Sender::ProduceMessages(MessageManager & manager, const std::vector<std::string>& names, int c)
{
	for (auto i : names)
	{
		manager.PushMessage(Message(i, c));
	}
}
