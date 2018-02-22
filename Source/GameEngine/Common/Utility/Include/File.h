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
#include "stdafx.h"
#include "Space.h"

namespace SpaceGameEngine
{
	typedef fpos_t FilePosition;

	namespace FileMode
	{
		const unsigned char None = 0;
		const unsigned char Read = 1;
		const unsigned char Write = 2;
		const unsigned char Append = 4;
		const unsigned char Binary = 8;
	}

	enum class PrintMode:unsigned char
	{
		EndLine = 1
	};

	Vector<std::string> GetDirectoryName(const std::string& filepath);

	void CheckAndCreateDirectory(const std::string& str);					//如果没找到文件所在的目录，则创建目录

	class File
	{
	public:
		File();
		~File();
		File(const std::string& filename, unsigned char mode);

		void Open(const std::string& filename, unsigned char mode);
		void Close();
		FilePosition GetBeginPosition();
		FilePosition GetEndPosition();
		FilePosition GetCurrentPosition();
		void SetFilePosition(FilePosition pos);

		void Read(void* adr, size_t size);
		void Write(const void* adr, size_t size);

		bool IfFileReadOver();				//文件是否读取完了

		File& operator >> (wchar_t* cwstr);
		File& operator >> (std::wstring& wstr);
		File& operator >> (wchar_t& wc);
		File& operator >> (char* cstr);
		File& operator >> (std::string& str);
		File& operator >> (int& i);
		File& operator >> (unsigned int& ui);
		File& operator >> (short& s);
		File& operator >> (unsigned short& us);
		File& operator >> (long& l);
		File& operator >> (unsigned long& ul);
		File& operator >> (long long& ll);
		File& operator >> (unsigned long long& ull);
		File& operator >> (char& c);
		File& operator >> (unsigned char& uc);
		File& operator >> (float& f);
		File& operator >> (double& d);
		File& operator >> (long double& ld);

		File& operator << (const wchar_t* wcstr);
		File& operator << (const std::wstring& wstr);
		File& operator << (const wchar_t& wc);
		File& operator << (const PrintMode& pm);
		File& operator << (const char* cstr);
		File& operator << (const std::string& str);
		File& operator << (const int& i);
		File& operator << (const unsigned int& ui);
		File& operator << (const short& s);
		File& operator << (const unsigned short& us);
		File& operator << (const long& l);
		File& operator << (const unsigned long& ul);
		File& operator << (const long long& ll);
		File& operator << (const unsigned long long& ull);
		File& operator << (const char& c);
		File& operator << (const unsigned char& uc);
		File& operator << (const float& f);
		File& operator << (const double& d);
		File& operator << (const long double& ld);

		bool GetLine(std::string& str);
	private:
		FILE* m_pFile;
		std::string m_FileName;
		unsigned int m_FileMode;
		bool m_IfFileReadOver;
	};
}