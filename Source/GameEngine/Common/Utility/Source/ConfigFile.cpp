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
#include "../Include/ConfigFile.h"

int SpaceGameEngine::ConfigFileValue::AsInt()
{
	if (m_Type == ConfigFileValueType::Int)
	{
		return std::stoi(m_Content);
	}
	else
	{
		ThrowError("this value's type is not int");
		return 0;
	}
}

float SpaceGameEngine::ConfigFileValue::AsFloat()
{
	if (m_Type == ConfigFileValueType::Float)
	{
		return std::stof(m_Content);
	}
	else
	{
		ThrowError("this value's type is not float");
		return 0.00f;
	}
}

double SpaceGameEngine::ConfigFileValue::AsDouble()
{
	if (m_Type == ConfigFileValueType::Double)
	{
		return std::stod(m_Content);
	}
	else
	{
		ThrowError("this value's type is not double");
		return 0.00;
	}
}

char SpaceGameEngine::ConfigFileValue::AsChar()
{
	if (m_Type == ConfigFileValueType::Char)
	{
		return m_Content[0];
	}
	else
	{
		ThrowError("this value's type is not char");
		return ' ';
	}
}

std::string SpaceGameEngine::ConfigFileValue::AsString()
{
	if (m_Type == ConfigFileValueType::String)
	{
		return m_Content;
	}
	else
	{
		ThrowError("this value's type is not string");
		return "";
	}
}

void SpaceGameEngine::ConfigFileValue::Set(int i)
{
	if (m_Type == ConfigFileValueType::Int)
	{
		m_Content = std::to_string(i);
	}
	else
	{
		ThrowError("this value's type is not int");
	}
}

void SpaceGameEngine::ConfigFileValue::Set(float f)
{
	if (m_Type == ConfigFileValueType::Float)
	{
		m_Content = std::to_string(f);
	}
	else
	{
		ThrowError("this value's type is not float");
	}
}

void SpaceGameEngine::ConfigFileValue::Set(double d)
{
	if (m_Type == ConfigFileValueType::Double)
	{
		m_Content = std::to_string(d);
	}
	else
	{
		ThrowError("this value's type is not double");
	}
}

void SpaceGameEngine::ConfigFileValue::Set(char c)
{
	if (m_Type == ConfigFileValueType::Char)
	{
		m_Content = c;
	}
	else
	{
		ThrowError("this value's type is not char");
	}
}

void SpaceGameEngine::ConfigFileValue::Set(const std::string & str)
{
	if (m_Type == ConfigFileValueType::String)
	{
		m_Content = str;
	}
	else
	{
		ThrowError("this value's type is not string");
	}
}

SpaceGameEngine::ConfigFileValue & SpaceGameEngine::ConfigTable::GetConfigValue(const std::string& name)
{
	auto iter = m_Content.find(name);
	if (iter != m_Content.end())
	{
		return iter->second;
	}
	else
	{
		ThrowError("can not find this config value");
		return ConfigFileValue();
	}
}

SpaceGameEngine::ConfigFile::ConfigFile()
{

}

SpaceGameEngine::ConfigFile::ConfigFile(const std::string & filename)
{
	InitFromFile(filename);
}

SpaceGameEngine::ConfigTable & SpaceGameEngine::ConfigFile::GetConfigTable(const std::string & name)
{
	auto iter = m_Content.find(name);
	if (iter != m_Content.end())
	{
		return iter->second;
	}
	else
	{
		ThrowError("can not find this config table");
		return ConfigTable();
	}
}

void SpaceGameEngine::ConfigFile::Parse(const Vector<std::string>& strs)
{
	/*
	prase state:
	0 : table
	1 : key
	2 : value
	*/
	int state = 0;
	bool if_table_name = false;
	ConfigTable* ptable = nullptr;
	ConfigFileValue* pvalue = nullptr;
	ConfigFileValueType type_buffer = ConfigFileValueType::Int;
	std::string str_buffer;

	for (auto str : strs)
	{
		for (auto _char : str)
		{
			if (_char == '\n' || _char == '\r' || _char == '\r\n')
				continue;

			//comment
			if (_char == ';')
				break;

			//table name
			if (state <= 1)
			{
				if (_char == '[' && (!if_table_name))
				{
					if_table_name = true;
					continue;
				}
				if (_char == ']'&&if_table_name)
				{
					if (!str_buffer.empty())
					{
						state = 1;
						m_Content.insert(std::make_pair(str_buffer, ConfigTable()));
						ptable = &m_Content[str_buffer];
						if_table_name = false;
						str_buffer.clear();
						continue;
					}
					else
					{
						ThrowError("can not have null table name");
						return;
					}
				}
			}

			if (if_table_name)
			{
				str_buffer += _char;
				continue;
			}

			//key
			if (state == 1)
			{
				if (_char == '=')
				{
					if (str_buffer.empty())
					{
						ThrowError("config value need key name");
						return;
					}
					else
					{
						if (ptable)
						{
							ptable->m_Content.insert(std::make_pair(str_buffer, ConfigFileValue()));
							pvalue = &ptable->m_Content[str_buffer];
							state = 2;
							str_buffer.clear();
							continue;
						}
						else
						{
							ThrowError("can not find config table");
							return;
						}
					}
				}
				else
				{
					if (_char != ' ')
						str_buffer += _char;
					continue;
				}
			}

			//value
			if (state == 2)
			{
				//float
				if (_char == 'f'&& type_buffer == ConfigFileValueType::Double)
				{
					type_buffer = ConfigFileValueType::Float;
					break;
				}

				//double
				if (_char == '.'&& type_buffer == ConfigFileValueType::Int)
				{
					type_buffer = ConfigFileValueType::Double;
				}

				//char
				if (_char == '\''&& type_buffer == ConfigFileValueType::Int)
				{
					type_buffer = ConfigFileValueType::Char;
					continue;
				}
				if (_char == '\''&& type_buffer == ConfigFileValueType::Char)
				{
					if (str_buffer.size() > 1)
					{
						ThrowError("char type value can only have single char");
						return;
					}
					break;
				}

				//string
				if (_char == '\"' && type_buffer == ConfigFileValueType::Int)
				{
					type_buffer = ConfigFileValueType::String;
					continue;
				}
				if (_char == '\"' && type_buffer == ConfigFileValueType::String)
				{
					break;
				}

				if (type_buffer == ConfigFileValueType::Char || type_buffer == ConfigFileValueType::String)
					str_buffer += _char;
				else if (_char != ' ')
					str_buffer += _char;
			}
		}

		if (state == 2)
		{
			//string check
			if (str_buffer.empty() && type_buffer != ConfigFileValueType::String)
			{
				ThrowError("config value can not be null");
				return;
			}

			//number check
			if (type_buffer != ConfigFileValueType::Char&&type_buffer != ConfigFileValueType::String)
			{
				bool if_point = false;
				for (auto iter = str_buffer.begin(); iter != str_buffer.end(); iter += 1)
				{
					auto i = *iter;
					if (i == '.')
					{
						if (if_point || (type_buffer != ConfigFileValueType::Float && type_buffer != ConfigFileValueType::Double) || iter == str_buffer.end() - 1)
						{
							ThrowError("config value number error");
							return;
						}
						else
							if_point = true;
						continue;
					}
					if (i<'0' || i>'9')
					{
						ThrowError("config value number error");
						return;
					}
				}
			}

			//submit
			if (pvalue)
			{
				pvalue->m_Type = type_buffer;
				pvalue->m_Content = str_buffer;
				
				type_buffer = ConfigFileValueType::Int;
				str_buffer.clear();
				state = 1;
			}
			else
			{
				ThrowError("can not find config value");
				return;
			}
		}
	}
}

void SpaceGameEngine::ConfigFile::InitFromFile(const std::string & filename)
{
	Vector<std::string> buffer;
	File file(filename, FileMode::Read);
	std::string str_buff;

	while (file.GetLine(str_buff))
	{
		buffer.push_back(str_buff);
	}

	file.Close();

	Parse(buffer);
}

void SpaceGameEngine::ConfigFile::SaveToFile(const std::string & filename)
{
	File file(filename, FileMode::Write);

	for (auto table : m_Content)
	{
		file << "[" << table.first << "]" << PrintMode::EndLine;
		for (auto key : table.second.m_Content)
		{
			auto str = key.second.m_Content;
			if (key.second.m_Type == ConfigFileValueType::Char)
				str = "\'" + str + "\'";
			if (key.second.m_Type == ConfigFileValueType::String)
				str = "\"" + str + "\"";
			if (key.second.m_Type == ConfigFileValueType::Float && (*str.rbegin()) != 'f')
				str += 'f';
			file << key.first << "=" << str << PrintMode::EndLine;
		}

	}

	file.Close();
}

SpaceGameEngine::ConfigFile & SpaceGameEngine::GetDefaultConfigFile()
{
	static ConfigFile DefaultConfigFile("SystemConfig.configfile");
	return DefaultConfigFile;
}
