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
#include "Vector4D.h"

namespace SpaceGameEngine
{
	struct Plane
	{
		Vector3D m_Direction;
		float m_Distance;

		Plane();
		Plane(Vector3D dir, float d);
		Plane(Vector4D c);
		/*
		参数依次为平面上的顺时针分布的三个点
		结果未被单位化
		*/
		Plane(Vector3D v1, Vector3D v2, Vector3D v3);
	};

	bool IfBehindPlane(const Plane& plane, const Vector3D& position);

	bool IfBeFrontOfPlane(const Plane& plane, const Vector3D& position);

	Plane NormalizePlane(const Plane& plane);
}