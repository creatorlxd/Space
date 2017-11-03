/*
Copyright 2017 creatorlxd

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
#include "Game/Component/Include/ComponentManager.h"
namespace SpaceGameEngine
{
	class Object			//�����������
	{
	public:
		Object();
		~Object();
		Component* GetComponent(const std::string& name);		//��ȡ�����ָ��
		bool AddComponent(Component* pc);						//����������������
		bool DeleteComponent(const std::string& name);			//ɾ���������ȥ������

		void Start();											//��ʼʱ����
		void InitFromFile(Vector<std::pair<std::string, std::string> > filenames);	//���ļ���ʼ��
		void InitFromFile(const std::string& filename);										//ͨ���ʲ��ļ��б�����ʼ��
		void Run(float DeltaTime);								//ÿ֡����ʱ�Ĳ���
		void Release();											//�ֶ��ͷ�

		bool SetRootComponent(const std::string& name);			//���ø����
		Component* GetRootComponent();							//��ȡ�����

		bool IfRun();						//�Ƿ�ÿ֡����
		bool IfUse();						//�Ƿ�ʹ��
		void ChangeIfRun(bool b);			//����ÿ֡�Ƿ�����
		void ChangeIfUse(bool b);			//�����Ƿ�ʹ��
		
		bool IfRender();					//�Ƿ���Ⱦ
		void ChangeIfRender(bool b);		//�����Ƿ���Ⱦ

		void ProduceMessage(Component* from, unsigned int message);
		Component* GetComponentByMessage(unsigned int message);
	protected:
		Map<std::string, Component*> m_Components;			//�����...
		Component* m_pRootComponent;							//�����
		Map<unsigned int, Component*> m_Message;

		bool m_IfUse;											//�Ƿ�ʹ��
		bool m_IfRun;											//�Ƿ�ÿ֡����
		bool m_IfRender;										//�Ƿ���Ⱦ
	};

	void RunComponentOnTree(Component* node, float DeltaTime);	//�������������(DFS)
}