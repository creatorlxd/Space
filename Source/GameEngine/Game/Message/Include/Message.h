#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"

struct Message					//��Ϣ
{
	std::string m_ReceiverName;		//������������
	int m_Content;					//��Ϣ������		
	Message();
	Message(int c);
	Message(const std::string& name,int c):
		m_ReceiverName(name),m_Content(c)
	{}
};

class Receiver						//������
{
public:
	void ReceiveMessage(const Message& message);//������Ϣ
	void ReceiveMessage(int message);//������Ϣ
	Message TakeOutMessage();					//ȡ����Ϣ
private:
	std::queue<int> m_MessageQueue;
};

class MessageManager				//��Ϣ������
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
				ThrowError(L"��Ҫ�ȶ���һ����Ϣ������");
				return nullptr;
			}
			if (m_Receivers.find(name) != m_Receivers.end())
			{
				ThrowError(L"�Ѵ��ڸý�����");
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

class Sender						//������
{
public:
	void Send(const Message& message);
	void Send(const std::string& name, int c);
};
