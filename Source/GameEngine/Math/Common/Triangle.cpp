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
#include "Triangle.h"

SpaceGameEngine::Triangle::Triangle(Vector3D v1, Vector3D v2, Vector3D v3)
{
	m_Positions[0] = v1;
	m_Positions[1] = v2;
	m_Positions[2] = v3;
}

bool SpaceGameEngine::operator==(const Triangle& t1, const Triangle& t2)
{
	if (t1.m_Positions[0] == t2.m_Positions[0] &&
		t1.m_Positions[1] == t2.m_Positions[1] &&
		t1.m_Positions[2] == t2.m_Positions[2])
		return true;
	else
		return false;
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

bool SpaceGameEngine::IfIntersect(const AxisAlignedBoundingBox & aabb, const Triangle & triangle)
{
	Vector3D point[8];
	point[0] = Vector3D(aabb.m_MinPosition.x, aabb.m_MaxPosition.y, aabb.m_MinPosition.z);
	point[1] = Vector3D(aabb.m_MaxPosition.x, aabb.m_MaxPosition.y, aabb.m_MinPosition.z);
	point[2] = Vector3D(aabb.m_MaxPosition.x, aabb.m_MinPosition.y, aabb.m_MinPosition.z);
	point[3] = Vector3D(aabb.m_MinPosition);
	point[4] = Vector3D(aabb.m_MinPosition.x, aabb.m_MaxPosition.y, aabb.m_MaxPosition.z);
	point[5] = Vector3D(aabb.m_MaxPosition);
	point[6] = Vector3D(aabb.m_MaxPosition.x, aabb.m_MinPosition.y, aabb.m_MaxPosition.z);
	point[7] = Vector3D(aabb.m_MinPosition.x, aabb.m_MinPosition.y, aabb.m_MaxPosition.z);
	Plane plane[6] = {
		NormalizePlane(Plane(point[0],point[1],point[2])),	//front
		NormalizePlane(Plane(point[5],point[4],point[7])),	//back
		NormalizePlane(Plane(point[4],point[5],point[1])),	//top
		NormalizePlane(Plane(point[3],point[2],point[6])),	//back
		NormalizePlane(Plane(point[4],point[0],point[3])),	//left
		NormalizePlane(Plane(point[1],point[5],point[6]))	//right
	};//面都对外
	for (int i = 0; i < 6; i++)
	{
		int fa_cot = 0;
		for (int j = 0; j < 3; j++)
		{
			if (IfBeFrontOfPlane(plane[i], triangle.m_Positions[j]))
				fa_cot += 1;
		}
		if (fa_cot == 3)
			return false;
	}
	return true;
}