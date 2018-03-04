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
#include "Game/Message/Include/Message.h"
#include "Graphics/Camera/Include/Camera.h"
#include "Common/Utility/Include/Window.h"
#include "Game/Object/Include/ObjectConnection.h"
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

		/*
		��������
		ע�⣺�������Scene���й����д����ģ�Ӧ�ֶ�������Start����
		*/
		Object* NewObject(const std::string name, ObjectMode mode = ObjectMode::Common);
		Object* GetObjectByName(const std::string name);
		bool DeleteObject(Object* po);
		bool DeleteObject(const std::string name);

	public:
		GlobalOctree m_GlobalOctree;		//ȫ�ְ˲���
		LightManager m_LightManager;		//��Դ������
		RenderSystem m_RenderSystem;
		MessageManager m_MessageManager;	//��Ϣ������
	private:
		static Scene* sm_pThis;
		HashMap<std::string, Object*> m_Content;//����Object
		bool m_IfInit;
	};

	/*
	����Object����
	ע�⣺dst����ָ��յ��´�����Object���������ߵ�mode������ͬ
	*/
	void CopyObject(Object* dst, Object* src);
}