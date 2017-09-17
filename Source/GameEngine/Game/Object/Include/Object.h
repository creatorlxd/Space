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