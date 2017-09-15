#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"
#include "Physics/Transform/Include/Transform.h"

namespace SpaceGameEngine
{
	//相机组件：不会主动调用，使用时需调用其Run方法
	class CameraComponent :public Component
	{
	public:
		CameraComponent();
		~CameraComponent();

		void Release();
		void Start();
		void Run(float DeltaTime);
	
		XMFLOAT4X4 ComputeViewMatrix();
		void GoForward(float dis);									//向前走
		void GoUp(float dis);										//向上走
		void GoRight(float dis);									//向右走
		void RotationLookDirection(XMFLOAT3 rotate);				//旋转视角（仅限x,y轴）

		void SetAsMainCamera();
		static CameraComponent* GetMainCamera();
		
		void InitTransform();										//初始化变换信息

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