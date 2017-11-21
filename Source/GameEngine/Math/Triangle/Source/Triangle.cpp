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
#include "../Include/Triangle.h"

SpaceGameEngine::Triangle::Triangle()
{

}

SpaceGameEngine::Triangle::Triangle(XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3 v3)
{
	m_Positions[0] = v1;
	m_Positions[1] = v2;
	m_Positions[2] = v3;
}

bool SpaceGameEngine::operator==(const Triangle & t1, const Triangle & t2)
{
	return (memcmp(t1.m_Positions, t2.m_Positions, 3 * sizeof(XMFLOAT3)) == 0);
}

int SpaceGameEngine::IfIntersect(const Frustum & frustum, const Triangle & triangle)
{
	Plane planes[6] = { frustum.m_NearPlane,frustum.m_FarPlane,
		frustum.m_LeftPlane,frustum.m_RightPlane,
		frustum.m_TopPlane,frustum.m_BottomPlane };
	bool flag[3];
	memset(flag, true, sizeof(flag));
	for (int i = 0; i < 6; i++)
	{
		int fa_cot = 0;
		for (int j = 0; j < 3; j++)
			if (IfBehindPlane(planes[i], triangle.m_Positions[j]))
			{
				flag[j] = false;
				fa_cot += 1;
			}
		if (fa_cot == 3)
			return -1;
	}
	int re = 0;
	for (int i = 0; i < 3; i++)
	{
		if (flag[i])
			re += 1;
	}
	return re;
}

bool SpaceGameEngine::IfInclude(const AxisAlignedBoundingBox & aabb, const Triangle & triangle)
{
	for (int i = 0; i < 3; i++)
	{
		if (IfInclude(aabb, triangle.m_Positions[i]) == false)
			return false;
	}
	return true;
}
