#pragma once 
#include "stdafx.h"

namespace SpaceGameEngine
{
	struct AxisAlignedBoundingBox		//AABB包围盒
	{
		XMFLOAT3 m_MinPosition;
		XMFLOAT3 m_MaxPosition;
	};

	typedef AxisAlignedBoundingBox AABB;

	bool IfIntersect(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2);	//是否相交

	bool IfIntersect(const AxisAlignedBoundingBox& aabb, const XMFLOAT3& position);				//是否相交
}