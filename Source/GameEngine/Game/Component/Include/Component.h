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

	class Component							//��������ڼ̳еĻ���
	{
	public:
		Component();
		virtual ~Component();
		std::string GetTypeName();			//��ȡ������
		Component* GetFatherComponent();	//��ȡ�����
		void SetFatherComponent(Component* pc);//���ø����
		void AddChildComponent(Component* pc);	//��������
		bool DeleteChildComponent(Component* pc);	//ɾ�������
		Component* FindChildComponent(const std::string& name);	//�������������Ѱ������Ϊname�����(BFS)
		Component* FindFatherComponent(const std::string& name);//�����и������Ѱ������Ϊname�����
		Vector<Component*>& GetChildrenComponent();	//�����������������
		virtual void InitFromFile(const std::string& filename, int mode = 0);
		virtual void Start();			//�ڿ�ʼʱִ��
		virtual void Run(float DeltaTime);//ÿ֡����ʱ�Ĳ���
		virtual void EveryFrameCleanUp();
		virtual void Attach(Component* pc);	//��Ϊ...���������
		virtual void Release();				//�ͷ�
		bool IfRun();						//�Ƿ�ÿ֡����
		bool IfUse();						//�Ƿ�ʹ��
		void ChangeIfRun(bool b);			//����ÿ֡�Ƿ�����
		void ChangeIfUse(bool b);			//�����Ƿ�ʹ��
		void SetFatherObject(Object* po);			//����������Object����
		Object* GetFatherObject();				//��ȡ������Object����
		void SetMode(int m);				//�������ڲ�����ģʽ
		int GetMode();						//��������ڲ�����ģʽ
		template<typename T>
		const T* ReadAssetFromFile(const std::string& filename);
		const Asset* GetAsset();
	protected:
		std::string m_TypeName;				//�����������
		int m_Mode;							//����ڲ�����ģʽ
		bool m_IfRun;						//�Ƿ�ÿ֡����
		bool m_IfUse;						//�Ƿ�ʹ��
		Vector<Component*> m_Children;	//�����
		Component* m_pFather;				//�����
		Object* m_pFatherObject;					//������Object����
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