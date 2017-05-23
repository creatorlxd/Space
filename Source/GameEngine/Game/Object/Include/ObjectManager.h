#pragma once
#include "stdafx.h"
#include "Object.h"

class ObjectManager			//Object对象管理器
{
public:
	ObjectManager();
	~ObjectManager();

	ObjectManager* const GetMainManager();		//获取主要的管理器

	static Object* NewObject();					//创建一个Object
	bool DeleteObject(Object* po);				//删除一个Object

	void Start();								//执行开始操作
	void Run(float DeltaTime);					//执行每帧的操作
private:
	static ObjectManager* sm_pThis;
	std::vector<Object*> m_Content;
};