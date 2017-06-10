#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"

class Object			//�����������
{
public:
	Object();
	~Object();
	Component* GetComponent(const std::string& name);		//��ȡ�����ָ��
	bool AddComponent(Component* pc);						//����������������
	bool DeleteComponent(const std::string& name);			//ɾ���������ȥ������

	void Start();											//��ʼʱ����
	void InitFromFile(std::vector<std::pair<std::string, std::string> > filenames);	//���ļ���ʼ��
	void InitFromFile(const std::string& filename);										//ͨ���ʲ��ļ��б�����ʼ��
	void Run(float DeltaTime);								//ÿ֡����ʱ�Ĳ���
	void Release();											//�ֶ��ͷ�

	bool SetRootComponent(const std::string& name);			//���ø����
	Component* GetRootComponent();							//��ȡ�����

	bool IfRun();						//�Ƿ�ÿ֡����
	bool IfUse();						//�Ƿ�ʹ��
	void ChangeIfRun(bool b);			//����ÿ֡�Ƿ�����
	void ChangeIfUse(bool b);			//�����Ƿ�ʹ��
protected:
	std::map<std::string, Component*> m_Components;			//�����...
	Component* m_pRootComponent;							//�����
	
	bool m_IfUse;											//�Ƿ�ʹ��
	bool m_IfRun;											//�Ƿ�ÿ֡����
};

void RunComponentOnTree(Component* node,float DeltaTime);	//�������������(DFS)