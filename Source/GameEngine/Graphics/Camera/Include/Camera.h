#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"

namespace SpaceGameEngine
{
	//相机组件：不会主动调用，使用时需调用其Run方法
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
		void GoForward(float dis);									//向前走
		void GoUp(float dis);										//向上走
		void GoRight(float dis);									//向右走
		void RotationLookDirection(XMFLOAT3 rotate);				//旋转视角（仅限x,y轴）

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