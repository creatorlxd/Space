#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"
#include "Window.h"
#include "Game/Scene/Include/SceneData.h"
namespace SpaceGameEngine
{
	//TODO:��TransformComponent�趨���ģʽ������������Ⱦģʽ���������ģʽ����������ģʽ����ģʽ������������ͬ��Run(...)
	class TransformComponent :public Component				//����Ļ���������Ϣ
	{
	public:
		static ComponentManager::NewComponent<TransformComponent> NewComponent;		//�������

		static const int ForRenderingMode = 1 << 0;
		static const int InformationMode = 1 << 1;
		static const int FatherTransformMode = 1 << 2;

		TransformComponent();
		~TransformComponent();

		void InitFromFile(const std::string& filename, int mode = 0);
		void Run(float DeltaTime);

		void SetPosition(const XMFLOAT3& position);
		void SetRotation(const XMFLOAT3& rotation);
		void SetScale(const XMFLOAT3& scale);

		XMFLOAT3 GetPosition();
		XMFLOAT3 GetRotation();
		XMFLOAT3 GetScale();
	private:
		XMFLOAT3 m_Position;								//λ������
		XMFLOAT3 m_Rotation;								//��ת�Ļ���
		XMFLOAT3 m_Scale;									//���ŵı���
	};
}