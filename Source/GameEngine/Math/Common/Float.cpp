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
#include "stdafx.h"
#include "Float.h"

bool SpaceGameEngine::FloatEqual(float f1, float f2)
{
	return std::fabs(f1 - f2) < FloatEpsilon ? true : false;
}

bool SpaceGameEngine::FloatLess(float f1, float f2)
{
	return FloatEqual(f1, f2) ? false : f1 < f2;
}

bool SpaceGameEngine::FloatMore(float f1, float f2)
{
	return FloatEqual(f1, f2) ? false : f1 > f2;
}

bool SpaceGameEngine::FloatLessOrEqual(float f1, float f2)
{
	return FloatEqual(f1, f2) ? true : f1 <= f2;
}

bool SpaceGameEngine::FloatMoreOrEqual(float f1, float f2)
{
	return FloatEqual(f1, f2) ? true : f1 >= f2;
}

float SpaceGameEngine::FloatMin(float f1, float f2)
{
	return FloatLess(f1, f2) ? f1 : f2;
}

float SpaceGameEngine::FloatMax(float f1, float f2)
{
	return FloatMore(f1, f2) ? f1 : f2;
}
