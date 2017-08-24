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
	private:
		static Scene* sm_pThis;
		std::map<std::string, Object*> m_ObjectInformation;	//对象信息
	};
}