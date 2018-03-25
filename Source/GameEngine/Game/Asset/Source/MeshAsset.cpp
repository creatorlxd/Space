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
#include "../Include/MeshAsset.h"

SpaceGameEngine::MeshForModelFileAsset::MeshForModelFileAsset()
{
	m_TypeName = "MeshForModelFileAsset";
}

void SpaceGameEngine::MeshForModelFileAsset::InitFromFile(const String & filename)
{
	m_FileName = filename;

	int v_s, i_s;
	File file(filename, FileMode::Read);

	file >> v_s >> i_s;

	m_Vertices.clear();
	m_Indices.clear();

	DefaultVertex vbuff;
	unsigned int ibuff;

	for (int i = 0; i < v_s; i++)
	{
		file >> vbuff.m_Position.x >> vbuff.m_Position.y >> vbuff.m_Position.z;
		file >> vbuff.m_Normal.x >> vbuff.m_Normal.y >> vbuff.m_Normal.z;
		file >> vbuff.m_TextureCoord.x >> vbuff.m_TextureCoord.y;
		m_Vertices.push_back(vbuff);
	}

	for (int i = 0; i < i_s; i++)
	{
		file >> ibuff;
		m_Indices.push_back(ibuff);
	}

	file.Close();
}
