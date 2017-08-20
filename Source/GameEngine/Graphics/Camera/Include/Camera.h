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
	private:
		XMFLOAT3 m_LookDirection;
		XMFLOAT3 m_RightDirection;
		XMFLOAT3 m_UpDirection;
		XMFLOAT3 m_Position;

		TransformComponent* m_pTransform;
		void InitTransform();
		void UpdatePosition();

		static CameraComponent* sm_pThis;
	public:
		static ComponentManager::NewComponent<CameraComponent> NewComponent;
	};
}