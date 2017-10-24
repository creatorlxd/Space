#pragma once 
#include "stdafx.h"

namespace SpaceGameEngine
{
	struct AxisAlignedBoundingBox		//AABB°üÎ§ºÐ
	{
		XMFLOAT3 m_MinPosition;
		XMFLOAT3 m_MaxPosition;
	};

	typedef AxisAlignedBoundingBox AABB;

	bool IfIntersect(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2);
}