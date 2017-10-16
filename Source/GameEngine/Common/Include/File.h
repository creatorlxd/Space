#pragma once
#include "stdafx.h"
#include "Space.h"

namespace SpaceGameEngine
{
	typedef fpos_t FilePosition;

	enum FileMode : unsigned char
	{
		None = 0,
		Read = 1,
		Write = 2,
		Append = 4,
		Binary = 8
	};

	enum PrintMode
	{
		EndLine = 1
	};

	class File
	{
	public:
		File();
		~File();

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