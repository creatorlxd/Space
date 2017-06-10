#pragma once
#include "stdafx.h"
#include "Space.h"

class Component							//��������ڼ̳еĻ���
{
public:
	Component();
	~Component();
	std::string GetTypeName();			//��ȡ������
	Component* GetFatherComponent();	//��ȡ�����
	void SetFatherComponent(Component* pc);//���ø����
	void AddChildComponent(Component* pc);	//���������
	bool DeleteChildComponent(Component* pc);	//ɾ�������
	Component* FindChildComponent(const std::string& name);	//�������������Ѱ������Ϊname�����(BFS)
	std::vector<Component*>& GetChildrenComponent();	//�����������������
	virtual void InitFromFile(const std::string& filename, int mode=0);
	virtual void Start();			//�ڿ�ʼʱִ��
	virtual void Run(float DeltaTime);//ÿ֡����ʱ�Ĳ���
	virtual void Attach(Component* pc);	//��Ϊ...���������
	virtual void Release();				//�ͷ�
	bool IfRun();						//�Ƿ�ÿ֡����
	bool IfUse();						//�Ƿ�ʹ��
	void ChangeIfRun(bool b);			//����ÿ֡�Ƿ�����
	void ChangeIfUse(bool b);			//�����Ƿ�ʹ��
protected:
	std::string m_TypeName;				//�����������
	bool m_IfRun;						//�Ƿ�ÿ֡����
	bool m_IfUse;						//�Ƿ�ʹ��
	std::vector<Component*> m_Children;	//�����
	Component* m_pFather;				//�����
};