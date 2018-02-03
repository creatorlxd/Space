/*
Copyright 2018 creatorlxd

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
#include "Game/Object/Include/ObjectManager.h"
#include "Game/Message/Include/Message.h"
#include "Graphics/Camera/Include/Camera.h"
#include "Common/Utility/Include/Window.h"
#include "Game/Object/Include/ObjectFactory.h"
#include "SceneData.h"
#include "Graphics/GlobalOctree/Include/GlobalOctree.h"
#include "Graphics/Light/Include/LightManager.h"

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
		GlobalOctree m_GlobalOctree;		//ȫ�ְ˲���
		LightManager m_LightManager;		//��Դ������
	private:
		static Scene* sm_pThis;
		Map<std::string, Object*> m_ObjectInformation;	//������Ϣ
	};
}