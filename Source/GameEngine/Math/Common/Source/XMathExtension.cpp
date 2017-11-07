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
#include "stdafx.h"
#include "../Include/XMathExtension.h"

bool SpaceGameEngine::operator < (const XMFLOAT3& v1, const XMFLOAT3& v2)
{
	return (v1.x<v2.x&&v1.y<v2.y&&v1.z<v2.z);
}

bool SpaceGameEngine::operator > (const XMFLOAT3 & v1, const XMFLOAT3 & v2)
{
	return (v1.x>v2.x&&v1.y>v2.y&&v1.z>v2.z);
}