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
	struct Matrix4D :public XMFLOAT4X4
	{
		Matrix4D();
		Matrix4D(float __11, float __12, float __13, float __14,
			float __21, float __22, float __23, float __24,
			float __31, float __32, float __33, float __34,
			float __41, float __42, float __43, float __44);
		Matrix4D(const XMFLOAT4X4& c);
		Matrix4D(const Matrix4D& m);
		Matrix4D(CXMMATRIX m);

		bool operator = (const XMFLOAT4X4& c);
		bool operator = (const Matrix4D& m);
		bool operator = (CXMMATRIX m);

		operator XMMATRIX() const;
	};
}