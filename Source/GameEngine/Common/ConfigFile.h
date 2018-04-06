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
#include "File.h"
#include "GlobalVariable.h"
#include "StringConverter.h"
#include "Error.h"

namespace SpaceGameEngine
{
	enum class ConfigFileValueType :unsigned char
	{
		Int,
		Float,
		Double,
		Char,
		String
	};

	struct ConfigFileValue
	{
		ConfigFileValueType m_Type;
		String m_Content;

		int AsInt();
		float AsFloat();
		double AsDouble();
		char AsChar();
		String AsString();

		void Set(int i);
		void Set(float f);
		void Set(double d);
		void Set(char c);
		void Set(const String& str);
	};

	class ConfigTable
	{
	public:
		friend class ConfigFile;

		ConfigFileValue& GetConfigValue(const String& name);
		bool IfHaveConfigValue(const String& name);
	private:
		Map<String, ConfigFileValue> m_Content;
	};

	class ConfigFile
	{
	public:
		ConfigFile();
		ConfigFile(const String& filename);

		ConfigTable & GetConfigTable(const String& name);
		bool IfHaveConfigTable(const String& name);

		/*
		接受由getline获取的一组字符串进行解析
		*/
		void Parse(const Vector<String>& strs);
		void InitFromFile(const String& filename);
		/*
		保存配置表到某个文件，但不保留注释
		*/
		void SaveToFile(const String& filename);
	public:
		friend struct StdAllocatorInterface;
		friend struct MemoryManagerAllocatorInterface;
	private:
		Map<String, ConfigTable> m_Content;
	};

	ConfigFile& GetDefaultConfigFile();
}