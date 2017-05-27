#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"

class Scene					//场景
{
public:
	Scene();
	~Scene();

	void SetAsMainScene();			//设为主场景
	void Start();					//开始
	void Run(float DeltaTime);		//每帧的运行
	void Release();					//释放
public:
	ObjectManager m_ObjectManager;	//对象管理器
};