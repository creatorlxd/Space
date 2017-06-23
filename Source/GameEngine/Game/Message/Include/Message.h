#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"

struct Message					//消息
{
	std::string m_ReceiverName;		//接受器的名称
	int m_Content;					//消息的内容		
	Message();
	Message(int c);
	Message(const std::string& name,int c):
		m_ReceiverName(name),m_Content(c)
	{}
};

class Receiver						//接收器
{
public:
	void ReceiveMessage(const Message& message);//接受消息
	void ReceiveMessage(int message);//接受消息
	Message TakeOutMessage();					//取出消息
private:
	std::queue<int> m_MessageQueue;
};

class MessageManager				//消息管理器
{
public:
	MessageManager();
	~MessageManager();
	void Release();

	void SetAsMainManager();
	static MessageManager* GetMainManager();

	void PushMessage(const Message& message);
	void Run();

	template<typename T>
	struct NewReceiver
	{
		Receiver* operator () (const std::string& name)
		{
			if (sm_pThis == nullptr)
			{
				ThrowError(L"需要先定义一个消息管理器");
				return nullptr;
			}
			if (m_Receivers.find(name) != m_Receivers.end())
			{
				ThrowError(L"已存在该接收器");
				return nullptr;
			}
			auto pointer = new Receiver();
			sm_pThis->m_Receivers.insert(make_pair(name, pointer));
			return pointer;
		}
	};
	bool DeleteReceiver(const std::string& name);
	bool DeleteReceiver(Receiver* pr);
	bool AddReceiver(const std::string& name, Receiver* pr);
private:
	static MessageManager* sm_pThis;
	std::map<std::string, Receiver*> m_Receivers;
	std::queue<Message> m_GlobalMessageQueue;
};

class Sender						//发送器
{
public:
	void Send(const Message& message);
	void Send(const std::string& name, int c);
};
