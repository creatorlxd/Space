/*
Copyright 2018 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "stdafx.h"
#include "../Include/Plane.h"

SpaceGameEngine::Plane::Plane(XMFLOAT3 dir, float d)
{
	m_Direction = dir;
	m_Distance = d;
}

SpaceGameEngine::Plane::Plane(XMFLOAT4 c)
{
	m_Direction = XMFLOAT3(c.x, c.y, c.z);
	m_Distance = c.z;
}

SpaceGameEngine::Plane::Plane()
{

}

bool SpaceGameEngine::IfBehindPlane(const Plane & plane, const XMFLOAT3 & position)
{
	XMVECTOR vbuff1 = XMLoadFloat3(&plane.m_Direction);
	XMVECTOR vbuff2 = XMLoadFloat3(&position);
	vbuff1 = XMVector3Dot(vbuff1, vbuff2);
	float dt = XMVectorGetX(vbuff1);
	//if (dt + plane.m_Distance < 0)
	if(FloatLess(dt+plane.m_Distance,0.00f))
		return true;
	else
		return false;
}

SpaceGameEngine::Plane SpaceGameEngine::NormalizePlace(const Plane & plane)
{
	Plane re;
	XMVECTOR vbuff1 = XMLoadFloat3(&plane.m_Direction);
	XMVECTOR len = XMVector3Length(vbuff1);
	XMVectorSetW(vbuff1,plane.m_Distance);
	vbuff1 = XMVectorDivide(vbuff1, len);
	XMStoreFloat3(&re.m_Direction, vbuff1);
	re.m_Distance = XMVectorGetW(vbuff1);
	return re;
}
