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
	m_TimeChange = 0;
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
	}
	else
	{
		TimeBuffer = timeGetTime()*0.001f;
		m_TimeChange = TimeBuffer - m_TimeNow;
		m_TimeNow = timeGetTime()*0.001f;
	}
}

void PhysicsComponent::SetXYZ(float x, float y, float z)
{
	m_Position = D3DXVECTOR3(x, y, z);
}

void PhysicsComponent::InitPhysicsFromFile(const std::string & filename)
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
	m_a = m_F / m_m;
	m_v = m_v + m_a*m_TimeChange;
	m_Position = m_Position + m_v*m_TimeChange;
	m_F = { 0.00f,0.00f,0.00f };
}

void PhysicsComponent::RunRoundingEngine()
{
}
