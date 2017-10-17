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
		void Wirte(const void* adr, size_t size);

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
	private:
		FILE* m_pFILE;
		std::string m_FileName;
		unsigned int m_FileMode;
	};
}