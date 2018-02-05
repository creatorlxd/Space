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
#include "Object.h"

namespace SpaceGameEngine
{
	class ObjectManager			//Object对象管理器
	{
	public:
		ObjectManager();
		~ObjectManager();

		static ObjectManager* GetMainManager();		//获取主要的管理器
		void SetAsMainManager();					//设置为主管理器
		static Object* NewObject();					//创建一个Object
		static void DestoryObject(Object* po);
		bool DeleteObject(Object* po);				//删除一个Object

		void Start();								//执行开始操作
		void Run(float DeltaTime);					//执行每帧的操作
		void Clear();								//释放
	private:
		static ObjectManager* sm_pThis;
		Vector<Object*> m_Content;
		Queue<unsigned int> m_FreeIndexList;
	};

	Object* CloneObject(Object* po);				//复制对象(在被复制对象所在场景运行时不能使用)
}