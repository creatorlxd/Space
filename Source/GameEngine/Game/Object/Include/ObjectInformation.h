#pragma once
#include "stdafx.h"
#include "Game/Scene/Include/Scene.h"

class InformationComponent :public Component			//Object信息组件
{
public:
	InformationComponent();
	~InformationComponent();

	void Run();

	void SetObjectInformation(Object* po);
private:
	Object* m_pObject;
};