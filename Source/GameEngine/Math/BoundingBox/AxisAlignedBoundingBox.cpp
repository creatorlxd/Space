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

bool SpaceGameEngine::IfIntersect(const AxisAlignedBoundingBox & aabb, const Vector3D & position)
{
	if (FloatMore(aabb.m_MinPosition.x, position.x) || FloatLess(aabb.m_MaxPosition.x, position.x))
		return false;
	if (FloatMore(aabb.m_MinPosition.y, position.y) || FloatLess(aabb.m_MaxPosition.y, position.y))
		return false;
	if (FloatMore(aabb.m_MinPosition.z, position.z) || FloatLess(aabb.m_MaxPosition.z, position.z))
		return false;
	return true;
}
