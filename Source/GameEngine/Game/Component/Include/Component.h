/*
Copyright 2017 creatorlxd

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
#include "Space.h"
#include "Common/MemoryManager/Include/AllocatorForSTL.hpp"
#include "Common/Utility/Include/File.h"
#include "ComponentInformationManager.h"
#include "../../Asset/Include/Asset.h"

namespace SpaceGameEngine
{
	class Object;

	class Component							//组件：用于继承的基类
	{
	public:
		Component();
		virtual ~Component();
		std::string GetTypeName();			//获取类型名
		Component* GetFatherComponent();	//获取父组件
		void SetFatherComponent(Component* pc);//设置父组件
		void AddChildComponent(Component* pc);	//添加子组件
		bool DeleteChildComponent(Component* pc);	//删除子组件
		Component* FindChildComponent(const std::string& name);	//在所有子组件中寻找类型为name的组件(BFS)
		Component* FindFatherComponent(const std::string& name);//在所有父组件中寻找类型为name的组件
		Vector<Component*>& GetChildrenComponent();	//获得子组件数组的引用
		virtual void InitFromFile(const std::string& filename, int mode = 0);
		virtual void Start();			//在开始时执行
		virtual void Run(float DeltaTime);//每帧运行时的操作
		virtual void EveryFrameCleanUp();
		virtual void Attach(Component* pc);	//成为...组件的依附
		virtual void Release();				//释放
		bool IfRun();						//是否每帧运行
		bool IfUse();						//是否使用
		void ChangeIfRun(bool b);			//更改每帧是否运行
		void ChangeIfUse(bool b);			//更改是否使用
		void SetFatherObject(Object* po);			//设置所属的Object对象
		Object* GetFatherObject();				//获取所属的Object对象
		void SetMode(int m);				//获得组件内部具体模式
		int GetMode();						//设置组件内部具体模式
		template<typename T>
		const T* ReadAssetFromFile(const std::string& filename);
		const Asset* GetAsset();
	protected:
		std::string m_TypeName;				//组件的类型名
		int m_Mode;							//组件内部具体模式
		bool m_IfRun;						//是否每帧运行
		bool m_IfUse;						//是否使用
		Vector<Component*> m_Children;	//子组件
		Component* m_pFather;				//父组件
		Object* m_pFatherObject;					//所属的Object对象
		const Asset* m_pAsset;				//Asset
	};

	template<typename T>
	T* CloneComponent(Component* pc)
	{
		T* re = T::NewComponent();
		
		auto pa = pc->GetAsset();
		if (pa)
			re->InitFromFile(pa->m_FileName,pc->GetMode());
		re->SetMode(pc->GetMode());

		return re;
	}

	template<typename T>
	inline const T * Component::ReadAssetFromFile(const std::string & filename)
	{
		auto re = GetAssetByFileName<T>(filename);
		m_pAsset = (const Asset*)re;
		return re;
	}
}