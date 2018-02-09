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
#include "stdafx.h"
#include "Game/Object/Include/Object.h"

namespace SpaceGameEngine
{
	struct Message					//��Ϣ
	{
		std::string m_ReceiverName;		//������������
		unsigned int m_Content;					//��Ϣ������		
		Message();
		Message(unsigned int c);
		Message(const std::string& name, unsigned int c) :
			m_ReceiverName(name), m_Content(c)
		{}
	};

	class Receiver						//������
	{
	public:
		virtual ~Receiver();

		void ReceiveMessage(const Message& message);//������Ϣ
		void ReceiveMessage(unsigned int message);			//������Ϣ
		unsigned int TakeOutMessage();					//ȡ����Ϣ
		bool IfEmpty();								//�Ƿ�Ϊ��
		size_t Size();									//��ȡ���еĴ�С
		void Clear();								//��ն���
		bool IfHaveMessage(unsigned int c);					//�Ƿ���ĳ����Ϣ
	private:
		Queue<unsigned int> m_MessageQueue;
	};

	class MessageManager				//��Ϣ������
	{
	public:
		MessageManager();
		~MessageManager();

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
		Map<std::string, Receiver*> m_Receivers;
		Queue<Message> m_GlobalMessageQueue;
		int m_MaxSize;
	};

	class Sender						//������
	{
	public:
		Sender();
		Sender(const std::string& name);
		~Sender();

		void ProduceMessage(const Message& message);			//������������Ϣ
		void ProduceMessage(const std::string& name, unsigned int c);	//������������Ϣ
		void ProduceMessage(MessageManager& manager, const Message& message);	//������������Ϣ
		void ProduceMessages(const std::vector<std::string>& names, unsigned int c);		//����ͬһ��Ϣ���������
		void ProduceMessages(MessageManager& manager, const std::vector<std::string>& names, unsigned int c);	//����ͬһ��Ϣ���������
		void FastProduceMessage(Receiver& r, const Message& message);			//���ٷ�����Ϣ�����������������У������Ƽ�ʹ��

		void DebugLog(const Message& message);

		void SetName(const std::string& name);
		std::string GetName();
	private:
		std::string m_Name;
	};
}