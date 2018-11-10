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
	@brief 配置文件中的值的类型
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

	/*!
	@brief 配置文件中的配置表
	*/
	class ConfigTable
	{
	public:
		friend class ConfigFile;

		/*!
		@brief 获取配置表中的值
		@param name 值的键名
		*/
		ConfigFileValue& GetConfigValue(const String& name);
		/*!
		@brief 查看配置表中是否有某个键值对
		@param name 值的键名
		*/
		bool IfHaveConfigValue(const String& name);
		/*!
		@brief 查找配置表中的值
		@param name 值的键名
		@return 有该键值对则返回指向其的指针，否则返回空指针nullptr
		*/
		ConfigFileValue* QueryConfigValue(const String& name);
	private:
		/*!
		@brief 配置表的内容
		*/
		Map<String, ConfigFileValue> m_Content;
	};

	/*!
	@brief 配置文件
	*/
	class ConfigFile
	{
	public:
		/*!
		@brief 配置文件的默认构造
		*/
		ConfigFile();
		/*!
		@brief 构造的同时读取一个配置文件的配置
		@param filename 要读取的配置文件名
		*/
		ConfigFile(const String& filename);

		/*!
		@brief 获取一个配置表
		@param name 配置表名
		*/
		ConfigTable & GetConfigTable(const String& name);
		/*!
		@brief 查看配置文件中是否有某个配置表
		@param name 配置表名
		*/
		bool IfHaveConfigTable(const String& name);
		/*!
		@brief 查找一个配置表
		@param name 配置表名
		@return 有该配置表则返回指向其的指针，否则返回空指针nullptr
		*/
		ConfigTable* QueryConfigTable(const String& name);

		/*!
		@brief 接受由`getline`获取的一组字符串进行解析
		@param strs 一行行字符串
		*/
		void Parse(const Vector<String>& strs);
		/*!
		@brief 从配置文件中读取配置
		@param filename 要读取的配置文件名
		*/
		void InitFromFile(const String& filename);
		/*!
		@brief 保存配置文件内容到某个文件，但不保留注释
		@param filename 要保存的文件名
		*/
		void SaveToFile(const String& filename);
	private:
		/*!
		@brief 配置文件的内容
		*/
		Map<String, ConfigTable> m_Content;
	};

	/*!
	@brief 获取游戏引擎默认的配置文件"./SystemConfig.configfile"
	*/
	ConfigFile& GetDefaultConfigFile();
}