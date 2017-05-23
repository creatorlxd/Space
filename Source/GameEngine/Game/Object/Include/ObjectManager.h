#pragma once
#include "stdafx.h"
#include "Object.h"

class ObjectManager			//Object���������
{
public:
	ObjectManager();
	~ObjectManager();

	ObjectManager* const GetMainManager();		//��ȡ��Ҫ�Ĺ�����

	static Object* NewObject();					//����һ��Object
	bool DeleteObject(Object* po);				//ɾ��һ��Object

	void Start();								//ִ�п�ʼ����
	void Run(float DeltaTime);					//ִ��ÿ֡�Ĳ���
private:
	static ObjectManager* sm_pThis;
	std::vector<Object*> m_Content;
};