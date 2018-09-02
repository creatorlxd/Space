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
#include "AxisAlignedBoundingBox.h"

SpaceGameEngine::AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vector3D & minl, const Vector3D & maxl)
{
	m_MinPosition = minl;
	m_MaxPosition = maxl;
}

bool SpaceGameEngine::operator == (const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2)
{
	return (aabb1.m_MinPosition == aabb2.m_MinPosition) && (aabb1.m_MaxPosition == aabb2.m_MaxPosition);
}

bool SpaceGameEngine::operator!=(const AxisAlignedBoundingBox & aabb1, const AxisAlignedBoundingBox & aabb2)
{
	return !(aabb1 == aabb2);
}

bool SpaceGameEngine::IfInclude(const AxisAlignedBoundingBox & aabb, const Vector3D & position)
{
	if (FloatMore(aabb.m_MinPosition.x, position.x) || FloatLess(aabb.m_MaxPosition.x, position.x))
		return false;
	if (FloatMore(aabb.m_MinPosition.y, position.y) || FloatLess(aabb.m_MaxPosition.y, position.y))
		return false;
	if (FloatMore(aabb.m_MinPosition.z, position.z) || FloatLess(aabb.m_MaxPosition.z, position.z))
		return false;
	return true;
}

bool SpaceGameEngine::IfIntersect(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2)
{
	if (FloatMore(aabb1.m_MinPosition.x, aabb2.m_MaxPosition.x) || FloatLess(aabb1.m_MaxPosition.x, aabb2.m_MinPosition.x))
		return false;
	if (FloatMore(aabb1.m_MinPosition.y, aabb2.m_MaxPosition.y) || FloatLess(aabb1.m_MaxPosition.y, aabb2.m_MinPosition.y))
		return false;
	if (FloatMore(aabb1.m_MinPosition.z, aabb2.m_MaxPosition.z) || FloatLess(aabb1.m_MaxPosition.z, aabb2.m_MinPosition.z))
		return false;
	return true;
}

bool SpaceGameEngine::IfInclude(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2)
{
	if (FloatLessOrEqual(aabb1.m_MinPosition.x, aabb2.m_MinPosition.x) && FloatMoreOrEqual(aabb1.m_MaxPosition.x, aabb2.m_MaxPosition.x) &&
		FloatLessOrEqual(aabb1.m_MinPosition.y, aabb2.m_MinPosition.y) && FloatMoreOrEqual(aabb1.m_MaxPosition.y, aabb2.m_MaxPosition.y) &&
		FloatLessOrEqual(aabb1.m_MinPosition.z, aabb2.m_MinPosition.z) && FloatMoreOrEqual(aabb1.m_MaxPosition.z, aabb2.m_MaxPosition.z))
		return true;
	else
		return false;
}

SpaceGameEngine::AxisAlignedBoundingBox SpaceGameEngine::GetAxisAlignedBoundingBox(const Vector<Vector3D>& points)
{
	Vector3D minl((float)MaxValue::g_MaxIntValue, (float)MaxValue::g_MaxIntValue, (float)MaxValue::g_MaxIntValue), maxl(-(float)MaxValue::g_MaxIntValue, -(float)MaxValue::g_MaxIntValue, -(float)MaxValue::g_MaxIntValue);
	for (auto& i : points)
	{
		minl.x = FloatMin(minl.x, i.x);
		minl.y = FloatMin(minl.y, i.y);
		minl.z = FloatMin(minl.z, i.z);
		maxl.x = FloatMax(maxl.x, i.x);
		maxl.y = FloatMax(maxl.y, i.y);
		maxl.z = FloatMax(maxl.z, i.z);
	}
	return AxisAlignedBoundingBox(minl, maxl);
}

SpaceGameEngine::AxisAlignedBoundingBox SpaceGameEngine::GetAxisAlignedBoundingBox(const Vector<AxisAlignedBoundingBox>& aabbs)
{
	Vector3D minl((float)MaxValue::g_MaxIntValue, (float)MaxValue::g_MaxIntValue, (float)MaxValue::g_MaxIntValue), maxl(-(float)MaxValue::g_MaxIntValue, -(float)MaxValue::g_MaxIntValue, -(float)MaxValue::g_MaxIntValue);
	for (auto i : aabbs)
	{
		minl.x = FloatMin(minl.x, i.m_MinPosition.x);
		minl.y = FloatMin(minl.y, i.m_MinPosition.y);
		minl.z = FloatMin(minl.z, i.m_MinPosition.z);
		maxl.x = FloatMax(maxl.x, i.m_MaxPosition.x);
		maxl.y = FloatMax(maxl.y, i.m_MaxPosition.y);
		maxl.z = FloatMax(maxl.z, i.m_MaxPosition.z);
	}
	return AxisAlignedBoundingBox(minl, maxl);
}

SpaceGameEngine::AxisAlignedBoundingBox SpaceGameEngine::TransformAxisAlignedBoundingBox(const AxisAlignedBoundingBox & aabb, const Matrix4D & mat)
{
	Vector<Vector3D> points;
	points.resize(8);
	points[0] = Vector3D(aabb.m_MinPosition.x, aabb.m_MaxPosition.y, aabb.m_MinPosition.z);
	points[1] = Vector3D(aabb.m_MaxPosition.x, aabb.m_MaxPosition.y, aabb.m_MinPosition.z);
	points[2] = Vector3D(aabb.m_MaxPosition.x, aabb.m_MinPosition.y, aabb.m_MinPosition.z);
	points[3] = Vector3D(aabb.m_MinPosition);
	points[4] = Vector3D(aabb.m_MinPosition.x, aabb.m_MaxPosition.y, aabb.m_MaxPosition.z);
	points[5] = Vector3D(aabb.m_MaxPosition);
	points[6] = Vector3D(aabb.m_MaxPosition.x, aabb.m_MinPosition.y, aabb.m_MaxPosition.z);
	points[7] = Vector3D(aabb.m_MinPosition.x, aabb.m_MinPosition.y, aabb.m_MaxPosition.z);

	for (auto& i : points)
	{
		i = XMVector3TransformCoord(i, mat);
	}
	
	return GetAxisAlignedBoundingBox(points);
}
