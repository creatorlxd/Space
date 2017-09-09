#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"
namespace SpaceGameEngine
{
	struct Message					//��Ϣ
	{
		std::string m_ReceiverName;		//������������
		int m_Content;					//��Ϣ������		
		Message();
		Message(int c);
		Message(const std::string& name, int c) :
			m_ReceiverName(name), m_Content(c)
		{}
	};

	class Receiver						//������
	{
	public:
		void ReceiveMessage(const Message& message);//������Ϣ
		void ReceiveMessage(int message);			//������Ϣ
		int TakeOutMessage();					//ȡ����Ϣ
		bool IfEmpty();								//�Ƿ�Ϊ��
		int Size();									//��ȡ���еĴ�С
		void Clear();								//��ն���
		bool IfHaveMessage(int c);					//�Ƿ���ĳ����Ϣ
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
				Receiver* pointer = MemoryManager::New<T>();
				sm_pThis->m_Receivers.insert(make_pair(name, pointer));
				return pointer;
			}
		};
		NewReceiver<Receiver> NewBaseReceiver;
		bool DeleteReceiver(const std::string& name);
		bool DeleteReceiver(Receiver* pr);
		bool AddReceiver(const std::string& name, Receiver* pr);
		Receiver* FindReceiver(const std::string& name);
		std::string FindReceiverName(Receiver* pr);
		void SetMaxSize(int i);
	private:
		static MessageManager* sm_pThis;
		std::map<std::string, Receiver*> m_Receivers;
		std::queue<Message> m_GlobalMessageQueue;
		int m_MaxSize;
	};

	class Sender						//������
	{
	public:
		Sender();
		Sender(const std::string& name);
		~Sender();

		void ProduceMessage(const Message& message);			//������������Ϣ
		void ProduceMessage(const std::string& name, int c);	//������������Ϣ
		void ProduceMessage(MessageManager& manager, const Message& message);	//������������Ϣ
		void ProduceMessages(const std::vector<std::string>& names, int c);		//����ͬһ��Ϣ���������
		void ProduceMessages(MessageManager& manager, const std::vector<std::string>& names, int c);	//����ͬһ��Ϣ���������
		void FastProduceMessage(Receiver& r, const Message& message);			//���ٷ�����Ϣ�����������������У������Ƽ�ʹ��

		void DebugLog(const Message& message);

		void SetName(const std::string& name);
		std::string GetName();
	private:
		std::string m_Name;
	};
}