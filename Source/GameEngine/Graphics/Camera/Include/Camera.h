#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"
#include "Physics/Transform/Include/Transform.h"

namespace SpaceGameEngine
{
	//�������������������ã�ʹ��ʱ�������Run����
	class CameraComponent :public Component
	{
	public:
		CameraComponent();
		~CameraComponent();

		void Release();
		void Start();
		void Run(float DeltaTime);
	
		XMFLOAT4X4 ComputeViewMatrix();
		void GoForward(float dis);									//��ǰ��
		void GoUp(float dis);										//������
		void GoRight(float dis);									//������
		void RotationLookDirection(XMFLOAT3 rotate);				//��ת�ӽǣ�����x,y�ᣩ

		void SetAsMainCamera();
		static CameraComponent* GetMainCamera();
		
		void InitTransform();										//��ʼ���任��Ϣ

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
	public:
		static ComponentManager::NewComponent<CameraComponent> NewComponent;
	};
}