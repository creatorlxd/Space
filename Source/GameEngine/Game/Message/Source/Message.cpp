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

void Sender::Send(const Message & message)
{
	MessageManager::GetMainManager()->PushMessage(message);
}

void Sender::Send(const std::string & name, int c)
{
	MessageManager::GetMainManager()->PushMessage(Message(name, c));
}
