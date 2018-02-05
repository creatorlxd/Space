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
	class ObjectManager			//Object���������
	{
	public:
		ObjectManager();
		~ObjectManager();

		static ObjectManager* GetMainManager();		//��ȡ��Ҫ�Ĺ�����
		void SetAsMainManager();					//����Ϊ��������
		static Object* NewObject();					//����һ��Object
		static void DestoryObject(Object* po);
		bool DeleteObject(Object* po);				//ɾ��һ��Object

		void Start();								//ִ�п�ʼ����
		void Run(float DeltaTime);					//ִ��ÿ֡�Ĳ���
		void Clear();								//�ͷ�
	private:
		static ObjectManager* sm_pThis;
		Vector<Object*> m_Content;
		Queue<unsigned int> m_FreeIndexList;
	};

	Object* CloneObject(Object* po);				//���ƶ���(�ڱ����ƶ������ڳ�������ʱ����ʹ��)
}