#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"

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
public:
	ObjectManager m_ObjectManager;	//对象管理器
private:
	static Scene* sm_pThis;
	std::map<std::string, Object*> m_ObjectInformation;	//对象信息
};