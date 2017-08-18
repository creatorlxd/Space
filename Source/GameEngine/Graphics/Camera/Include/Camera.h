#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"

namespace SpaceGameEngine
{
	//�������������������ã�ʹ��ʱ�������Run����
	class CameraComponent :public Component
	{
	public:
		CameraComponent();
		~CameraComponent();

		void InitFromFile(const std::string& filename, int mode = 0);
		void Release();
		void Run(float DeltaTime);

		void SetPosition(XMFLOAT3 pos);
		void SetLookDirection(XMFLOAT3 dir);
		XMFLOAT3 GetPosition();
		XMFLOAT3 GetLookDirection();
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

		static CameraComponent* sm_pThis;
	public:
		static ComponentManager::NewComponent<CameraComponent> NewComponent;
	};
}