#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"

class Scene					//����
{
public:
	Scene();
	~Scene();

	void SetAsMainScene();			//��Ϊ������
	void Start();					//��ʼ
	void Run(float DeltaTime);		//ÿ֡������
	void Release();					//�ͷ�
public:
	ObjectManager m_ObjectManager;	//���������
};