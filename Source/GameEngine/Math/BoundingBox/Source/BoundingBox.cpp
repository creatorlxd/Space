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
	XMFLOAT3 minl((float)MaxIntValue,(float)MaxIntValue,(float)MaxIntValue), maxl(-(float)MaxIntValue, -(float)MaxIntValue, -(float)MaxIntValue);
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

SpaceGameEngine::AxisAlignedBoundingBox SpaceGameEngine::GetAxisAlignedBoundingBox(const Vector<AxisAlignedBoundingBox>& aabbs)
{
	XMFLOAT3 minl((float)MaxIntValue, (float)MaxIntValue, (float)MaxIntValue), maxl(-(float)MaxIntValue, -(float)MaxIntValue, -(float)MaxIntValue);
	for (auto i : aabbs)
	{
		minl.x = min(minl.x, i.m_MinPosition.x);
		minl.y = min(minl.y, i.m_MinPosition.y);
		minl.z = min(minl.z, i.m_MinPosition.z);
		maxl.x = max(maxl.x, i.m_MaxPosition.x);
		maxl.y = max(maxl.y, i.m_MaxPosition.y);
		maxl.z = max(maxl.z, i.m_MaxPosition.z);
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
	
	XMFLOAT3 point_after[8];
	bool if_front = true, if_behind = true;
	int flag_x = 0, flag_y = 0;
	int ans_x = 0, ans_y = 0;
	int point_cot = 0;
	int re = 0;
	for (int i = 0; i < 8; i++)
	{
		point_cot += 1;
		point_after[i] = TransformByViewProjectionMatrix(point[i]);
		if (point_after[i].z >= 0)
			if_front = false;
		if (point_after[i].z <= 1)
			if_behind = false;
		if (point_after[i].z > 1 || point_after[i].z < 0)
		{
			point_cot -= 1;
			continue;
		}
		if (point_after[i].x >= -1.0f&&point_after[i].x <= 1.0f&&
			point_after[i].y >= -1.0f&&point_after[i].y <= 1.0f&&
			point_after[i].z >= 0.0f&&point_after[i].z <= 1.0f)
		{
			re += 1;
			continue;
		}
		if (flag_x == 0 && point_cot == 1)
			flag_x = (point_after[i].x > 1 ? 1 : (point_after[i].x < -1 ? -1 : 0));
		if (flag_y == 0 && point_cot == 1)
			flag_y = (point_after[i].y > 1 ? 1 : (point_after[i].y < -1 ? -1 : 0));
		if (flag_x == (point_after[i].x > 1 ? 1 : (point_after[i].x < -1 ? -1 : 0)))
			ans_x += 1;
		if (flag_y == (point_after[i].y > 1 ? 1 : (point_after[i].y < -1 ? -1 : 0)))
			ans_y += 1;
	}
	if (re > 0)
		return re;
	if (if_front || if_behind)
		return -1;
	if ((ans_x == point_cot&&flag_x != 0) || (ans_y == point_cot&&flag_y != 0))
		return -1;
	static XMFLOAT2 point_left[8];
	int point_left_size = 0;
	AxisAlignedBoundingBox box(XMFLOAT3((float)MaxIntValue, (float)MaxIntValue, 0),XMFLOAT3(-(float)MaxIntValue, -(float)MaxIntValue, 0));
	for (int i = 0; i < 8; i++)
	{
		if (point_after[i].z >= 0 && point_after[i].z <= 1)
		{
			point_left[point_left_size++] = XMFLOAT2(point_after[i].x, point_after[i].y);
		}
		box.m_MinPosition.x = min(box.m_MinPosition.x, point_after[i].x);
		box.m_MinPosition.y = min(box.m_MinPosition.y, point_after[i].y);
		
		box.m_MaxPosition.x = max(box.m_MaxPosition.x, point_after[i].x);
		box.m_MaxPosition.y = max(box.m_MaxPosition.y, point_after[i].y);
	}
	if (IfInclude(box, AxisAlignedBoundingBox(XMFLOAT3(-1.0f, -1.0f, 0), XMFLOAT3(1.0f, 1.0f, 0))))
		return 0;
	/*
	use y=k*x+b to find the line bewteen two point if cross the rectangle
	*/
	float k, b;
	float y[2];
	for (int i = 0; i < point_left_size; i++)
	{
		for (int j = i + 1; j < point_left_size; j++)
		{
			if (min(point_left[i].x, point_left[j].x) <= 1 && max(point_left[i].x, point_left[j].x) >= -1 &&
				min(point_left[i].y, point_left[j].y) <= 1 && max(point_left[i].y, point_left[j].y) >= -1)
			{
				if (point_left[i].x == point_left[j].x)
					return 0;
				k = (point_left[i].y - point_left[j].y) / (point_left[i].x - point_left[j].x);
				b = ((point_left[i].x*point_left[j].y) - (point_left[j].x*point_left[i].y)) / (point_left[i].x - point_left[j].x);
				y[0] = k*-1.0f + b;
				y[1] = k + b;
				if ((y[0] >= -1 && y[0] <= 1) || (y[1] >= -1 && y[1] <= 1) ||
					(y[0] > 1 && y[1] < -1) || (y[0] < -1 && y[1]>1))
					return 0;
			}
		}
	}
	return -1;
}
