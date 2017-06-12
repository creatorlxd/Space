#pragma once
#include "stdafx.h"
#include "Game/Scene/Include/Scene.h"

class InformationComponent :public Component			//Object��Ϣ���
{
public:
	static ComponentManager::NewComponent<InformationComponent> NewComponent;

	InformationComponent();
	~InformationComponent();

	void Run(float DeltaTime);

	void SetObjectInformation(Object* po);
private:
	Object* m_pObject;
};

bool RegisterObject(const std::string& name, Object* po);	//ע��Object

#define REGISTEROBJECT(o) RegisterObject(#o,o);