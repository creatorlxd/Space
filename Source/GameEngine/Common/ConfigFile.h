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
	/*!
	@brief 配置文件键值的类型
	*/
	enum class ConfigFileValueType :unsigned char
	{
		Int,
		Float,
		Double,
		Char,
		String,
		Bool
	};

	/*!
	@brief 配置文件中的值
	@note 实际上是使用String来储存和转换
	*/
	struct ConfigFileValue
	{
		/*!
		@brief 值的类型
		@see ConfigFileValueType
		*/
		ConfigFileValueType m_Type;
		/*!
		@brief 值的内容
		*/
		String m_Content;

		/*!
		@brief 以`int`类型得到值的内容
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Int`
		@see m_Type
		@see ConfigFileValueType
		*/
		int AsInt();
		/*!
		@brief 以`float`类型得到值的内容
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Float`
		@see m_Type
		@see ConfigFileValueType
		*/
		float AsFloat();
		/*!
		@brief 以`double`类型得到值的内容
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Double`
		@see m_Type
		@see ConfigFileValueType
		*/
		double AsDouble();
		/*!
		@brief 以`char`类型得到值的内容
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Char`
		@see m_Type
		@see ConfigFileValueType
		*/
		char AsChar();
		/*!
		@brief 以`SpaceGameEngine::String`类型得到值的内容
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::String`
		@see m_Type
		@see ConfigFileValueType
		*/
		String AsString();
		/*!
		@brief 以`bool`类型得到值的内容
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Bool`
		@see m_Type
		@see ConfigFileValueType
		*/
		bool AsBool();

		/*!
		@brief 设置值为一个`int`值
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Int`
		@see m_Type
		@see ConfigFileValueType
		*/
		void Set(int i);
		/*!
		@brief 设置值为一个`float`值
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Float`
		@see m_Type
		@see ConfigFileValueType
		*/
		void Set(float f);
		/*!
		@brief 设置值为一个`double`值
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Double`
		@see m_Type
		@see ConfigFileValueType
		*/
		void Set(double d);
		/*!
		@brief 设置值为一个`char`值
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Char`
		@see m_Type
		@see ConfigFileValueType
		*/
		void Set(char c);
		/*!
		@brief 设置值为一个`SpaceGameEngine::String`值
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::String`
		@see m_Type
		@see ConfigFileValueType
		*/
		void Set(const String& str);
		/*!
		@brief 设置值为一个`bool`值
		@attention 值的类型`m_Type`应该是`ConfigFileValueType::Bool`
		@see m_Type
		@see ConfigFileValueType
		*/
		void Set(bool b);
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
	private:
		Map<String, ConfigTable> m_Content;
	};

	ConfigFile& GetDefaultConfigFile();
}