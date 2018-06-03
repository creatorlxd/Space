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
#include <DirectXMath.h>

using namespace DirectX;

namespace SpaceGameEngine
{
	struct Matrix3D :public XMFLOAT3X3
	{
		Matrix3D();
		Matrix3D(float __11, float __12, float __13,
			float __21, float __22, float __23,
			float __31, float __32, float __33);
		Matrix3D(const XMFLOAT3X3& c);
		Matrix3D(const Matrix3D& m);
		Matrix3D(CXMMATRIX m);

		bool operator = (const XMFLOAT3X3& c);
		bool operator = (const Matrix3D& m);
		bool operator = (CXMMATRIX m);

		operator XMMATRIX();
	};
}