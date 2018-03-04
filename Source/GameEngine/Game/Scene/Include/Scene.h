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
	class Scene					//场景
	{
	public:
		Scene();
		~Scene();

		void SetAsMainScene();			//设为主场景
		static Scene* GetMainScene();	//获取主场景
		void Start();					//开始
		void Run(float DeltaTime);		//每帧的运行

		/*
		创建对象。
		注意：如果是在Scene运行过程中创建的，应手动调用其Start方法
		*/
		Object* NewObject(const std::string name, ObjectMode mode = ObjectMode::Common);
		Object* GetObjectByName(const std::string name);
		bool DeleteObject(Object* po);
		bool DeleteObject(const std::string name);

	public:
		GlobalOctree m_GlobalOctree;		//全局八叉树
		LightManager m_LightManager;		//光源管理器
		RenderSystem m_RenderSystem;
		MessageManager m_MessageManager;	//消息管理器
	private:
		static Scene* sm_pThis;
		HashMap<std::string, Object*> m_Content;//储存Object
		bool m_IfInit;
	};

	/*
	复制Object对象
	注意：dst必须指向空的新创建的Object对象，且两者的mode必须相同
	*/
	void CopyObject(Object* dst, Object* src);
}