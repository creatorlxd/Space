#pragma once
#include "stdafx.h"
#include "Object.h"

class ObjectManager			//Object���������
{
public:
	ObjectManager();
	~ObjectManager();

	static ObjectManager* GetMainManager();		//��ȡ��Ҫ�Ĺ�����
	void SetAsMainManager();					//����Ϊ��������
	static Object* NewObject();					//����һ��Object
	bool DeleteObject(Object* po);				//ɾ��һ��Object

	void Start();								//ִ�п�ʼ����
	void Run(float DeltaTime);					//ִ��ÿ֡�Ĳ���
	void Release();								//�ͷ�
private:
	static ObjectManager* sm_pThis;
	std::vector<Object*> m_Content;
};