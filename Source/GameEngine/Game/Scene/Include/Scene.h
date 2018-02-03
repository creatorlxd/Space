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
	class Scene					//场景
	{
	public:
		Scene();
		~Scene();

		void SetAsMainScene();			//设为主场景
		static Scene* GetMainScene();	//获取主场景
		void Start();					//开始
		void Run(float DeltaTime);		//每帧的运行
		void Release();					//释放

		bool AddObjectInformation(const std::string& name, Object* po);
		bool DeleteObjectInformation(const std::string& name);
		bool DeleteObjectInformation(Object* po);
		Object* FindObject(const std::string& name);
		std::string FindObjectName(Object* po);
	public:
		ObjectManager m_ObjectManager;	//对象管理器
		ComponentManager m_ComponentManager;	//组件管理器
		MessageManager m_MessageManager;	//消息管理器
		GlobalOctree m_GlobalOctree;		//全局八叉树
		LightManager m_LightManager;		//光源管理器
	private:
		static Scene* sm_pThis;
		Map<std::string, Object*> m_ObjectInformation;	//对象信息
	};
}