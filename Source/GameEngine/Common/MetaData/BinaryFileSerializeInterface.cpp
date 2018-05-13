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
#include "BinaryFileSerializeInterface.h"

SpaceGameEngine::BinaryFileSerializeInterface::BinaryFileSerializeInterface(const String & filename, IOFlag ioflag)
	:SerializeInterface(ioflag)
{
	m_File.Open(filename, (ioflag == IOFlag::Input ? FileMode::Read : FileMode::Write) | FileMode::Binary);
}

SpaceGameEngine::BinaryFileSerializeInterface::~BinaryFileSerializeInterface()
{
	m_File.Close();
}

SpaceGameEngine::String SpaceGameEngine::BinaryFileSerializeInterface::Read()
{
	uint64_t size;
	m_File.Read(&size, sizeof(size));
	String re(size, ' ');
	m_File.Read(re.data(), size * sizeof(char));
	return re;
}

void SpaceGameEngine::BinaryFileSerializeInterface::Write(const String & str)
{
	uint64_t size = str.size();
	m_File.Write(&size, sizeof(size));
	m_File.Write(str.c_str(), size * sizeof(char));
}
