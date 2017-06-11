#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"

class TransformComponent:public Component				//物体的基本物理信息
{
public:
	static ComponentManager::NewComponent<TransformComponent> NewComponent;		//创建组件

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
	XMFLOAT3 m_Position;								//位置坐标
	XMFLOAT3 m_Rotation;								//旋转的弧度
	XMFLOAT3 m_Scale;									//缩放的比例
};