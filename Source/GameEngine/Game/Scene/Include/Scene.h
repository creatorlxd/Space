#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"

class Scene					//����
{
public:
	Scene();
	~Scene();

	void SetAsMainScene();			//��Ϊ������
	static Scene* GetMainScene();	//��ȡ������
	void Start();					//��ʼ
	void Run(float DeltaTime);		//ÿ֡������
	void Release();					//�ͷ�

	bool AddObjectInformation(const std::string& name, Object* po);
	bool DeleteObjectInformation(const std::string& name);
	bool DeleteObjectInformation(Object* po);
	Object* FindObject(const std::string& name);
public:
	ObjectManager m_ObjectManager;	//���������
private:
	static Scene* sm_pThis;
	std::map<std::string, Object*> m_ObjectInformation;	//������Ϣ
};