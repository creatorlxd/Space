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
#include "../Include/LightAsset.h"

SpaceGameEngine::LightAsset::LightAsset()
{
	m_TypeName = "LightAsset";
}

void SpaceGameEngine::LightAsset::InitFromFile(const std::string & filename)
{
	m_FileName = filename;

	File file(filename, FileMode::Read);

	file >> m_Content.m_Ambient.x >> m_Content.m_Ambient.y >> m_Content.m_Ambient.z >> m_Content.m_Ambient.w;
	file >> m_Content.m_Diffuse.x >> m_Content.m_Diffuse.y >> m_Content.m_Diffuse.z >> m_Content.m_Diffuse.w;
	file >> m_Content.m_Specular.x >> m_Content.m_Specular.y >> m_Content.m_Specular.z >> m_Content.m_Specular.w;
	file >> m_Content.m_Position.x >> m_Content.m_Position.y >> m_Content.m_Position.z;
	file >> m_Content.m_Range;
	file >> m_Content.m_Direction.x >> m_Content.m_Direction.y >> m_Content.m_Direction.z;
	file >> m_Content.m_SpotLightOption;
	file >> m_Content.m_LightOption.x >> m_Content.m_LightOption.y >> m_Content.m_LightOption.z;
	file >> (uint32_t&)m_Content.m_Type;

	file.Close();
}
