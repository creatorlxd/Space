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
#include "Math/Common/Include/MathDefinition.h"
#include "Math/Common/Include/XMathExtension.h"

namespace SpaceGameEngine
{
	struct Plane
	{
		XMFLOAT3 m_Direction;
		float m_Distance;
		
		Plane(XMFLOAT3 dir, float d);
		Plane(XMFLOAT4 c);
		Plane();
	};

	bool IfBehindPlane(const Plane& plane, const XMFLOAT3& position);

	Plane NormalizePlane(const Plane& plane);
}