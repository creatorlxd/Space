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
#include "Game/Component/Include/Component.h"
#include "Physics/Transform/Include/Transform.h"

namespace SpaceGameEngine
{
	//�������������������ã�ʹ��ʱ�������Run����
	class CameraComponent :public Component
	{
	public:
		REGISTER_COMPONENT(CameraComponent)

		CameraComponent();
		~CameraComponent();

		void Start();
		void Run(float DeltaTime);
		void Copy(Component* pc);

		XMFLOAT4X4 ComputeViewMatrix();
		void GoForward(float dis);									//��ǰ��
		void GoUp(float dis);										//������
		void GoRight(float dis);									//������
		void RotationLookDirection(XMFLOAT3 rotate);				//��ת�ӽǣ�����x,y�ᣩ

		void SetAsMainCamera();
		static CameraComponent* GetMainCamera();
		
		void InitTransform();										//��ʼ���任��Ϣ
		TransformComponent* GetTransform();

		float GetAngle();
		void SetAngle(float f);
		float GetNearZ();
		void SetNearZ(float f);
		float GetFarZ();
		void SetFarZ(float f);
	private:
		XMFLOAT4 m_LookDirection;
		XMFLOAT4 m_RightDirection;
		XMFLOAT4 m_UpDirection;
		XMFLOAT4 m_Position;

		float m_Angle;
		float m_NearZ;
		float m_FarZ;

		TransformComponent* m_pTransform;
		void UpdatePosition();

		static CameraComponent* sm_pThis;
	};
}