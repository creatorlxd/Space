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
#include "Vector3D.h"
#include "Math/BoundingBox/AxisAlignedBoundingBox.h"
#include "Frustum.h"

namespace SpaceGameEngine
{
	struct Triangle
	{
		Triangle() = default;
		Vector3D m_Positions[3];
		Triangle(Vector3D v1, Vector3D v2, Vector3D v3);
	};

	bool operator == (const Triangle& t1, const Triangle& t2);

	int IfIntersect(const Frustum& frustum, const Triangle& triangle);
	
	bool IfInclude(const AxisAlignedBoundingBox& aabb, const Triangle& triangle);
	
	bool IfIntersect(const AxisAlignedBoundingBox& aabb, const Triangle& triangle);
}