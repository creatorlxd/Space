/*
Copyright 2017 creatorlxd

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
#include "../Include/BoundingBox.h" 

SpaceGameEngine::AxisAlignedBoundingBox::AxisAlignedBoundingBox()
{
	m_MinPosition = XMFLOAT3(0, 0, 0);
	m_MaxPosition = XMFLOAT3(0, 0, 0);
}

SpaceGameEngine::AxisAlignedBoundingBox::AxisAlignedBoundingBox(const XMFLOAT3 & minl, const XMFLOAT3 & maxl)
{
	m_MinPosition = minl;
	m_MaxPosition = maxl;
}

bool SpaceGameEngine::IfIntersect(const AxisAlignedBoundingBox & aabb1, const AxisAlignedBoundingBox & aabb2)
{
	if (aabb1.m_MinPosition.x >= aabb2.m_MaxPosition.x || aabb1.m_MaxPosition.x <= aabb2.m_MinPosition.x)
		return false;
	if (aabb1.m_MinPosition.y >= aabb2.m_MaxPosition.y || aabb1.m_MaxPosition.y <= aabb2.m_MinPosition.y)
		return false;
	if (aabb1.m_MinPosition.z >= aabb2.m_MaxPosition.z || aabb1.m_MaxPosition.z <= aabb2.m_MinPosition.z)
		return false;
	return true;
}

bool SpaceGameEngine::IfInclude(const AxisAlignedBoundingBox & aabb, const XMFLOAT3 & position)
{
	if (aabb.m_MinPosition.x > position.x || aabb.m_MaxPosition.x < position.x)
		return false;
	if (aabb.m_MinPosition.y > position.y || aabb.m_MaxPosition.y < position.y)
		return false;
	if (aabb.m_MinPosition.z > position.z || aabb.m_MaxPosition.z < position.z)
		return false;
	return true;
}

bool SpaceGameEngine::IfInclude(const AxisAlignedBoundingBox & aabb1, const AxisAlignedBoundingBox & aabb2)
{
	if ((aabb1.m_MinPosition.x <= aabb2.m_MinPosition.x&&aabb1.m_MaxPosition.x >= aabb2.m_MaxPosition.x) &&
		(aabb1.m_MinPosition.y <= aabb2.m_MinPosition.y&&aabb1.m_MaxPosition.y >= aabb2.m_MaxPosition.y) &&
		(aabb1.m_MinPosition.z <= aabb2.m_MinPosition.z&&aabb1.m_MaxPosition.z >= aabb2.m_MaxPosition.z))
		return true;
	else
		return false;
}

SpaceGameEngine::AxisAlignedBoundingBox SpaceGameEngine::GetAxisAlignedBoundingBox(const Vector<XMFLOAT3>& points)
{
	XMFLOAT3 minl((float)MaxIntValue,(float)MaxIntValue,(float)MaxIntValue), maxl(0.0f,0.0f,0.0f);
	for (auto& i : points)
	{
		minl.x = min(minl.x, i.x);
		minl.y = min(minl.y, i.y);
		minl.z = min(minl.z, i.z);
		maxl.x = max(maxl.x, i.x);
		maxl.y = max(maxl.y, i.y);
		maxl.z = max(maxl.z, i.z);
	}
	return AxisAlignedBoundingBox(minl, maxl);
}

int SpaceGameEngine::IfIntersectWithFrustum(const AxisAlignedBoundingBox & aabb)
{
	XMFLOAT3 point[8];
	point[0] = XMFLOAT3(aabb.m_MinPosition.x, aabb.m_MaxPosition.y, aabb.m_MinPosition.z);
	point[1] = XMFLOAT3(aabb.m_MaxPosition.x, aabb.m_MaxPosition.y, aabb.m_MinPosition.z);
	point[2] = XMFLOAT3(aabb.m_MaxPosition.x, aabb.m_MinPosition.y, aabb.m_MinPosition.z);
	point[3] = XMFLOAT3(aabb.m_MinPosition);
	point[4] = XMFLOAT3(aabb.m_MinPosition.x, aabb.m_MaxPosition.y, aabb.m_MaxPosition.z);
	point[5] = XMFLOAT3(aabb.m_MaxPosition);
	point[6] = XMFLOAT3(aabb.m_MaxPosition.x, aabb.m_MinPosition.y, aabb.m_MaxPosition.z);
	point[7] = XMFLOAT3(aabb.m_MinPosition.x, aabb.m_MinPosition.y, aabb.m_MaxPosition.z);
	
	int re=0;
	for (int i = 0; i < 8; i++)
	{
		if (IfIntersectWithFrustum(point[i]))
			re += 1;
	}
	return re;
}