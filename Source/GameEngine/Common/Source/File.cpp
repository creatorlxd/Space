#include "stdafx.h"
#include "../Include/File.h"

SpaceGameEngine::File::File()
{
	m_pFILE = nullptr;
	m_FileMode = FileMode::None;
}

SpaceGameEngine::File::~File()
{
	if (m_FileMode != FileMode::None)
		Close();
}

void SpaceGameEngine::File::Open(const std::string & filename, unsigned char mode)
{
	m_FileName = filename;
	m_FileMode = mode;
	std::string opt;
	if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) == 0)
	{
		opt = "r";
	}
	if ((mode&FileMode::Read) == 0 && (mode&FileMode::Write) != 0)
	{
		opt = "w";
	}
	if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) != 0)
	{
		opt = "r";
	}
	if ((mode&FileMode::Binary) != 0)
	{
		opt += "b";
	}
	if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) != 0)
	{
		opt += "+";
	}

	if (fopen_s(&m_pFILE, filename.c_str(), opt.c_str()) != 0)
		ThrowError(L"can not open file:" + StringToTString(filename));

	if ((mode&FileMode::Append) != 0)
	{
		fseek(m_pFILE, 0, SEEK_END);
	}
}

void SpaceGameEngine::File::Close()
{
	if (m_FileMode == FileMode::None)
		ThrowError(L"can not Close a File without Open or has been closed");

	fclose(m_pFILE);
	m_FileMode = FileMode::None;
	m_FileName.clear();
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetBeginPosition()
{
	FilePosition buff, re;
	fgetpos(m_pFILE, &buff);
	fseek(m_pFILE, 0, SEEK_SET);
	fgetpos(m_pFILE, &re);
	fsetpos(m_pFILE, &buff);
	return re;
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetEndPosition()
{
	FilePosition buff, re;
	fgetpos(m_pFILE, &buff);
	fseek(m_pFILE, 0L, SEEK_END);
	fgetpos(m_pFILE, &re);
	fsetpos(m_pFILE, &buff);
	return re;
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetCurrentPosition()
{
	FilePosition re;
	fgetpos(m_pFILE, &re);
	return re;
}

void SpaceGameEngine::File::SetFilePosition(FilePosition pos)
{
	fsetpos(m_pFILE, &pos);
}

void SpaceGameEngine::File::Read(void * adr, size_t size)
{
	fread_s(adr, size, size, 1, m_pFILE);
}

void SpaceGameEngine::File::Wirte(const void * adr, size_t size)
{
	fwrite(adr, size, 1, m_pFILE);
}
SpaceGameEngine::File & SpaceGameEngine::File::operator>>(char * cstr)
{
	std::string str;
	*this >> str;
	memcpy(cstr, str.c_str(), sizeof(char)*str.size());
	return *this;
}

SpaceGameEngine::File& SpaceGameEngine::File::operator>>(std::string & str)
{
	char c = ' ';
	while (c == ' ' || c == '\r' || c == '\n')
	{
		c = fgetc(m_pFILE);
	}
	while (c != ' '&&c != EOF&&c != '\r'&&c != '\n')
	{
		str += c;
		c = fgetc(m_pFILE);
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(int & i)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%d", &i);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned int & ui)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%ud", &ui);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(short & s)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%hd", &s);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned short & us)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%hud", &us);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long & l)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%ld", &l);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned long & ul)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%uld", &ul);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long long & ll)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%I64d", &ll);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned long long & ull)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%I64ud", &ull);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(char & c)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, " \r\n\t%c", &c, sizeof(char));
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned char & uc)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%hhu", &uc);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(float & f)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%f", &f);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(double & d)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%lf", &d);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long double & ld)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%Lf", &ld);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const SpaceGameEngine::PrintMode & pm)
{
	switch (pm)
	{
	case EndLine:
	{
		fscanf_s(m_pFILE, "\n");
		fflush(m_pFILE);
	}
	default:
		break;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const char * cstr)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%s", cstr);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const std::string & str)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%s", str.c_str());
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const int & i)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%d", i);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned int & ui)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%ud", ui);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const short & s)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%hd", s);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned short & us)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%hud", us);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long & l)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%ld", l);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned long & ul)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%lud", ul);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long long & ll)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%I64d", ll);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned long long & ull)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%I64ud", ull);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const char & c)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%c", c);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned char & uc)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%hhu", uc);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const float & f)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%f", f);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const double & d)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%lf", d);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long double & ld)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%Lf", ld);
	return *this;
}
