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
#include "../Include/TransformAsset.h"

SpaceGameEngine::TransformAsset::TransformAsset()
{
	m_TypeName = "TransformAsset";
}

void SpaceGameEngine::TransformAsset::InitFromFile(const String & filename)
{
	m_FileName = filename;

	File file(filename, FileMode::Read);

	file >> m_Position.x >> m_Position.y >> m_Position.z;
	file >> m_Rotation.x >> m_Rotation.y >> m_Rotation.z;
	file >> m_Scale.x >> m_Scale.y >> m_Scale.z;

	file.Close();
}
