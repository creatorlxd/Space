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
		std::string m_Content;

		int AsInt();
		float AsFloat();
		double AsDouble();
		char AsChar();
		std::string AsString();

		void Set(int i);
		void Set(float f);
		void Set(double d);
		void Set(char c);
		void Set(const std::string& str);
	};

	class ConfigTable
	{
	public:
		friend class ConfigFile;

		ConfigFileValue& GetConfigValue(const std::string& name);
	private:
		Map<std::string, ConfigFileValue> m_Content;
	};

	class ConfigFile
	{
	public:
		ConfigFile();
		ConfigFile(const std::string& filename);

		ConfigTable & GetConfigTable(const std::string& name);

		/*
		接受由getline获取的一组字符串进行解析
		*/
		void Parse(const Vector<std::string>& strs);
		void InitFromFile(const std::string& filename);
		/*
		保存配置表到某个文件，但不保留注释
		*/
		void SaveToFile(const std::string& filename);
	public:
		friend struct StdAllocatorInterface;
		friend struct MemoryManagerAllocatorInterface;
	private:
		Map<std::string, ConfigTable> m_Content;
	};

	ConfigFile& GetDefaultConfigFile();
}