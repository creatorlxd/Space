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
#pragma once 
#include "stdafx.h"
#include "AllocatorForSTL.hpp"
#include "Math/Common/Include/MathDefinition.h"
#include "Math/Common/Include/XMathExtension.h"

namespace SpaceGameEngine
{
	struct AxisAlignedBoundingBox		//AABB��Χ��
	{
		XMFLOAT3 m_MinPosition;
		XMFLOAT3 m_MaxPosition;
		AxisAlignedBoundingBox();
		AxisAlignedBoundingBox(const XMFLOAT3& minl, const XMFLOAT3& maxl);
	};

	typedef AxisAlignedBoundingBox AABB;

	bool IfIntersect(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2);	//�Ƿ��ཻ

	bool IfIntersect(const AxisAlignedBoundingBox& aabb, const XMFLOAT3& position);				//�Ƿ��ཻ

	AxisAlignedBoundingBox GetAxisAlignedBoundingBox(const Vector<XMFLOAT3>& points);
}