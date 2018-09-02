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
#pragma once
#include "Math/Common/Vector3D.h"
#include "Math/Common/Matrix4D.h"
#include "Math/Common/ConstantValue.hpp"
#include "Common/MemoryManager/AllocatorForSTL.hpp"

namespace SpaceGameEngine
{
	/*
	3D AABB 包围盒
	*/
	struct AxisAlignedBoundingBox
	{
		AxisAlignedBoundingBox() = default;
		AxisAlignedBoundingBox(const Vector3D& minl, const Vector3D& maxl);

		Vector3D m_MinPosition;
		Vector3D m_MaxPosition;
	};

	using AABB = AxisAlignedBoundingBox;

	bool operator == (const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2);

	bool operator != (const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2);

	/*
	点是否在AABB中(包括边框)
	*/
	bool IfInclude(const AxisAlignedBoundingBox& aabb, const Vector3D& position);	

	bool IfIntersect(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2);	

	bool IfInclude(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2);	//是否包含

	AxisAlignedBoundingBox GetAxisAlignedBoundingBox(const Vector<Vector3D>& points);

	AxisAlignedBoundingBox GetAxisAlignedBoundingBox(const Vector<AxisAlignedBoundingBox>& aabbs);

	AxisAlignedBoundingBox TransformAxisAlignedBoundingBox(const AxisAlignedBoundingBox& aabb, const Matrix4D& mat);
}