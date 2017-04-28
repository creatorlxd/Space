#include "stdafx.h"
#include "Physics.h"

D3DVECTOR operator + (D3DVECTOR v1, D3DVECTOR v2)
{
	D3DVECTOR r;
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;
	return r;
}
D3DVECTOR operator * (D3DVECTOR v1, float f)
{
	D3DVECTOR r;
	r = v1;
	r.x *= f;
	r.y *= f;
	r.z *= f;
	return r;
}
D3DVECTOR operator / (D3DVECTOR v1, float f)
{
	D3DVECTOR r;
	r = v1;
	r.x /= f;
	r.y /= f;
	r.z /= f;
	return r;
}

PhysicsComponent::PhysicsComponent()
{
	m_TimeNow = 0;
	m_DeltaTime = 0;
	m_a = { 0,0,0 };
	m_F = { 0,0,0 };
	m_m = 0;
	m_rxa = 0;
	m_rxv = 0;
	m_rya = 0;
	m_ryv = 0;
	m_rza = 0;
	m_rzv = 0;
	m_I = { 0.00f, 0.00f, 0.00f };
	m_Position = { 0.00f,0.00f,0.00f };
	m_v = { 0.00f,0.00f,0.00f };
}

void PhysicsComponent::GetTime()
{
	float TimeBuffer = 0;
	if (m_TimeNow == 0)
	{
		m_TimeNow = timeGetTime()*0.001f;
		GetTime();
	}
	else
	{
		TimeBuffer = timeGetTime()*0.001f;
		m_DeltaTime = TimeBuffer - m_TimeNow;
		m_TimeNow = timeGetTime()*0.001f;
	}
}

void PhysicsComponent::SetXYZ(float x, float y, float z)
{
	m_Position = D3DXVECTOR3(x, y, z);
}

void PhysicsComponent::SetDeltaTime(float second)
{
	m_DeltaTime = second;
}

void PhysicsComponent::InitFromFile(const std::string & filename)
{
	std::fstream file(filename.c_str(), std::ios::in);

	file.close();
}

void PhysicsComponent::GetG()
{
	D3DVECTOR G;
	G.y = -1 * g*m_m;
	m_F = m_F + G;
}

void PhysicsComponent::RunMovingEngine()
{
	D3DVECTOR buff_v = m_v;
	m_a = m_F / m_m;
	m_v = m_v + m_a*m_DeltaTime;
	m_Position = m_Position + ((m_v + buff_v) / 2)*m_DeltaTime;
	m_F = { 0.00f,0.00f,0.00f };
}

void PhysicsComponent::RunRotationEngine()
{
}

bool PhysicsManager::AddPhysicsComponent(PhysicsComponent * physicscomponent)
{
	m_Content.push_back(physicscomponent);
	return true;
}

bool PhysicsManager::RemovePhysicsComponent(PhysicsComponent * physicscomponent)
{
	std::vector<PhysicsComponent*>::iterator result = m_Content.end();
	for (std::vector<PhysicsComponent*>::iterator i = m_Content.begin();i != m_Content.end();i += 1)
	{
		if (*i == physicscomponent)
		{
			result = i;
			break;
		}
	}
	if (result != m_Content.end())
	{
		m_Content.erase(result);
		return true;
	}
	else
		return false;
}

bool PhysicsManager::RunManager(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	for (size_t i = 0;i < m_Content.size();i++)
	{
		m_Content[i]->GetTime();
		m_Content[i]->RunMovingEngine();
		m_Content[i]->RunRotationEngine();
	}
	return true;
}

bool PhysicsManager::RunManager(LPDIRECT3DDEVICE9 g_pd3dDevice, float time)
{
	for (size_t i = 0;i < m_Content.size();i++)
	{
		m_Content[i]->SetDeltaTime(time);
		m_Content[i]->RunMovingEngine();
		m_Content[i]->RunRotationEngine();
	}
	return true;
}
