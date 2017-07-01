#include "stdafx.h"
#include "../Include/Transform.h" 

REGISTERCOMPONENTCLASS(TransformComponent);

TransformComponent::TransformComponent()
{
	m_TypeName = "TransformComponent";
	m_Position = { 0,0,0 };
	m_Rotation = { 0,0,0 };
	m_Scale = { 1,1,1 };
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::InitFromFile(const std::string & filename, int mode)
{
	std::fstream file(filename, std::ios::in);

	file >> m_Position.x >> m_Position.y >> m_Position.z;
	file >> m_Rotation.x >> m_Rotation.y >> m_Rotation.z;
	file >> m_Scale.x >> m_Scale.y >> m_Scale.z;

	file.close();
}

void TransformComponent::Run(float DeltaTime)
{

}

void TransformComponent::SetPosition(const XMFLOAT3 & position)
{
	m_Position = position;
}

void TransformComponent::SetRotation(const XMFLOAT3 & rotation)
{
	m_Rotation = rotation;
}

void TransformComponent::SetScale(const XMFLOAT3 & scale)
{
	m_Scale = scale;
}

XMFLOAT3 TransformComponent::GetPosition()
{
	return m_Position;
}

XMFLOAT3 TransformComponent::GetRotation()
{
	return m_Rotation;
}

XMFLOAT3 TransformComponent::GetScale()
{
	return m_Scale;
}
