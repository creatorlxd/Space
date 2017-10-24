#include "stdafx.h"
#include "../Include/BoundingBox.h" 

bool SpaceGameEngine::IfIntersect(const AxisAlignedBoundingBox & aabb1, const AxisAlignedBoundingBox & aabb2)
{
	if (aabb1.m_MinPosition.x > aabb2.m_MaxPosition.x || aabb1.m_MaxPosition.x < aabb2.m_MinPosition.x)
		return false;
	if (aabb1.m_MinPosition.y > aabb2.m_MaxPosition.y || aabb1.m_MaxPosition.y < aabb2.m_MinPosition.y)
		return false;
	if (aabb1.m_MinPosition.z > aabb2.m_MaxPosition.z || aabb1.m_MaxPosition.z < aabb2.m_MinPosition.z)
		return false;
	return true;
}
