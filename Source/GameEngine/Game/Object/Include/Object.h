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
#include "Game/Component/Include/ComponentManager.h"

namespace SpaceGameEngine
{
	class RenderObject;

	Vector<std::pair<std::string, std::pair<std::string, int>>> ReadAssetListFromFile(const std::string& filename);	//从文件中读取资产文件列表

	class Object			//基本物体对象
	{
	public:
		Object();
		~Object();
		Component* GetComponent(const std::string& name);		//获取组件的指针
		template<typename T>
		T* GetComponent();
		bool AddComponent(Component* pc);						//添加组件，并不连接
		bool DeleteComponent(const std::string& name);			//删除组件，并去除连接

		void Start();											//开始时运行
		void InitFromFile(const Vector<std::pair<std::string, std::pair<std::string, int>>>& filenames);	//从文件初始化
		void InitFromFile(const std::string& filename);										//通过资产文件列表来初始化
		void Run(float DeltaTime);								//每帧运行时的操作
		void EveryFrameCleanUp();
		void Release();											//手动释放

		bool SetRootComponent(const std::string& name);			//设置根组件
		Component* GetRootComponent();							//获取根组件

		bool IfRun();						//是否每帧运行
		bool IfUse();						//是否使用
		void ChangeIfRun(bool b);			//更改每帧是否运行
		void ChangeIfUse(bool b);			//更改是否使用
		
		bool IfRender();					//是否渲染
		void ChangeIfRender(bool b);		//更改是否渲染

		void ProduceMessage(Component* from, unsigned int message);
		Component* GetComponentByMessage(unsigned int message);

		Vector<Object*>& GetChildren();
		void AddChildObject(Object* po);
		void DeleteChildObject(Object* po);
		bool IfChild();

		friend void ConnectObject(Object* father, Object* child);
		friend void DisconObject(Object* child);

		void SetRenderObject(RenderObject* pro);
		RenderObject* GetRenderObject();

	private:
		
		void Attach(Object* po);
		void Discon();						//断开

	protected:
		Map<std::string, Component*> m_Components;			//组件们...
		Component* m_pRootComponent;							//根组件
		Map<unsigned int, Component*> m_Message;
		Object* m_pFather;									//父对象
		Vector<Object*> m_Children;							//子对象
		RenderObject* m_pRenderObject;						//渲染对象

		bool m_IfUse;											//是否使用
		bool m_IfRun;											//是否每帧运行
		bool m_IfRender;										//是否渲染
		bool m_IfChild;											//是否是子对象
	};

	void RunComponentOnTree(Component* node, float DeltaTime);	//在树上运行组件(DFS)

	template<typename T>
	inline T * Object::GetComponent()
	{
		return dynamic_cast<T*>(GetComponent(T::NewComponent.m_Name));
	}
	
}