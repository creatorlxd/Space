#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"
#include "Game/Message/Include/Message.h"
#include "Graphics/Camera/Include/Camera.h"
#include "Window.h"
#include "Game/Object/Include/ObjectFactory.h"
#include "SceneData.h"
namespace SpaceGameEngine
{
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
		std::string FindObjectName(Object* po);
	public:
		ObjectManager m_ObjectManager;	//���������
		ComponentManager m_ComponentManager;	//���������
		MessageManager m_MessageManager;	//��Ϣ������
	private:
		static Scene* sm_pThis;
		std::map<std::string, Object*> m_ObjectInformation;	//������Ϣ
	};
}