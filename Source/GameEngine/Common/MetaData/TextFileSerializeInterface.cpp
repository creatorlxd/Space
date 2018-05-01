﻿/*
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
#include "TextFileSerializeInterface.h"

SpaceGameEngine::TextFileSerializeInterface::TextFileSerializeInterface(const String& filename, IOFlag ioflag)
	:SerializeInterface(ioflag)
{
	m_File.Open(filename, (ioflag == IOFlag::Input ? FileMode::Read : FileMode::Write));
}

SpaceGameEngine::TextFileSerializeInterface::~TextFileSerializeInterface()
{
	m_File.Close();
}

SpaceGameEngine::String SpaceGameEngine::TextFileSerializeInterface::Read()
{
	String re = "";
	if (m_File.IfFileReadOver() == false)
		m_File.GetLine(re);
	return re;
}

void SpaceGameEngine::TextFileSerializeInterface::Write(const String & str)
{
	m_File << str << PrintMode::EndLine;
}
