#pragma once
#include "stdafx.h"
#include "Space.h"
#include "AllocatorForSTL.hpp"
#include "File.h"
namespace SpaceGameEngine
{
	class Object;

	class Component							//��������ڼ̳еĻ���
	{
	public:
		Component();
		~Component();
		std::string GetTypeName();			//��ȡ������
		Component* GetFatherComponent();	//��ȡ�����
		void SetFatherComponent(Component* pc);//���ø����
		void AddChildComponent(Component* pc);	//��������
		bool DeleteChildComponent(Component* pc);	//ɾ�������
		Component* FindChildComponent(const std::string& name);	//�������������Ѱ������Ϊname�����(BFS)
		Component* FindFatherComponent(const std::string& name);//�����и������Ѱ������Ϊname�����
		Vector<Component*>& GetChildrenComponent();	//�����������������
		virtual void InitFromFile(const std::string& filename, int mode = 0);
		virtual void Start();			//�ڿ�ʼʱִ��
		virtual void Run(float DeltaTime);//ÿ֡����ʱ�Ĳ���
		virtual void Attach(Component* pc);	//��Ϊ...���������
		virtual void Release();				//�ͷ�
		bool IfRun();						//�Ƿ�ÿ֡����
		bool IfUse();						//�Ƿ�ʹ��
		void ChangeIfRun(bool b);			//����ÿ֡�Ƿ�����
		void ChangeIfUse(bool b);			//�����Ƿ�ʹ��
		void SetFatherObject(Object* po);			//����������Object����
		Object* GetFatherObject();				//��ȡ������Object����
		void SetMode(int m);				//�������ڲ�����ģʽ
		int GetMode();						//��������ڲ�����ģʽ
	protected:
		std::string m_TypeName;				//�����������
		int m_Mode;							//����ڲ�����ģʽ
		bool m_IfRun;						//�Ƿ�ÿ֡����
		bool m_IfUse;						//�Ƿ�ʹ��
		Vector<Component*> m_Children;	//�����
		Component* m_pFather;				//�����
		Object* m_pFatherObject;					//������Object����
	};
}