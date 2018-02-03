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
#include "Math/Frustum/Include/Frustum.h"
#include "Math/BoundingBox/Include/BoundingBox.h"

namespace SpaceGameEngine
{
	struct Triangle
	{
		XMFLOAT3 m_Positions[3];
		Triangle();
		Triangle(XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3 v3);
	};

	bool operator == (const Triangle& t1, const Triangle& t2);

	int IfIntersect(const Frustum& frustum, const Triangle& triangle);
	bool IfInclude(const AxisAlignedBoundingBox& aabb, const Triangle& triangle);
	bool IfIntersect(const AxisAlignedBoundingBox& aabb, const Triangle& triangle);
}