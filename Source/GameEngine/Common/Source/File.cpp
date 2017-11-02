#include "stdafx.h"
#include "../Include/File.h"

SpaceGameEngine::File::File()
{
	m_pFile = nullptr;
	m_FileMode = FileMode::None;
}

SpaceGameEngine::File::~File()
{
	if (m_FileMode != FileMode::None)
		Close();
}

SpaceGameEngine::File::File(const std::string & filename, unsigned char mode)
{
	m_pFile = nullptr;
	m_FileMode = FileMode::None;

	Open(filename, mode);
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

	CheckAndCreateDirectory(filename);
	if (fopen_s(&m_pFile, filename.c_str(), opt.c_str()) != 0)
		ThrowError(L"can not open file:" + StringToTString(filename));

	if ((mode&FileMode::Append) != 0)
	{
		fseek(m_pFile, 0, SEEK_END);
	}
}

void SpaceGameEngine::File::Close()
{
	if (m_FileMode == FileMode::None)
		ThrowError(L"can not Close a File without Open or has been closed");

	fclose(m_pFile);
	m_FileMode = FileMode::None;
	m_FileName.clear();
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetBeginPosition()
{
	FilePosition buff, re;
	fgetpos(m_pFile, &buff);
	fseek(m_pFile, 0, SEEK_SET);
	fgetpos(m_pFile, &re);
	fsetpos(m_pFile, &buff);
	return re;
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetEndPosition()
{
	FilePosition buff, re;
	fgetpos(m_pFile, &buff);
	fseek(m_pFile, 0L, SEEK_END);
	fgetpos(m_pFile, &re);
	fsetpos(m_pFile, &buff);
	return re;
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetCurrentPosition()
{
	FilePosition re;
	fgetpos(m_pFile, &re);
	return re;
}

void SpaceGameEngine::File::SetFilePosition(FilePosition pos)
{
	fsetpos(m_pFile, &pos);
}

void SpaceGameEngine::File::Read(void * adr, size_t size)
{
	fread_s(adr, size, size, 1, m_pFile);
}

void SpaceGameEngine::File::Wirte(const void * adr, size_t size)
{
	fwrite(adr, size, 1, m_pFile);
}
SpaceGameEngine::File & SpaceGameEngine::File::operator>>(wchar_t * cwstr)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		std::wstring wstr;
		*this >> wstr;
		memcpy(cwstr, wstr.c_str(), sizeof(wchar_t)*wstr.size());
	}
	return *this;
}
SpaceGameEngine::File & SpaceGameEngine::File::operator>>(std::wstring & wstr)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		wstr.clear();
		wchar_t c = L' ';
		while (c == L' ' || c == L'\r' || c == L'\n')
		{
			c = fgetwc(m_pFile);
		}
		while (c != L' '&&c != EOF&&c != L'\r'&&c != L'\n')
		{
			wstr += c;
			c = fgetwc(m_pFile);
		}
	}
	return *this;
}
SpaceGameEngine::File & SpaceGameEngine::File::operator>>(wchar_t & wc)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, " \r\n\t%C", &wc, (unsigned int)sizeof(wchar_t));
	return *this;
}
SpaceGameEngine::File & SpaceGameEngine::File::operator>>(char * cstr)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		std::string str;
		*this >> str;
		memcpy(cstr, str.c_str(), sizeof(char)*str.size());
	}
	return *this;
}

SpaceGameEngine::File& SpaceGameEngine::File::operator>>(std::string & str)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		str.clear();
		char c = ' ';
		while (c == ' ' || c == '\r' || c == '\n')
		{
			c = fgetc(m_pFile);
		}
		while (c != ' '&&c != EOF&&c != '\r'&&c != '\n')
		{
			str += c;
			c = fgetc(m_pFile);
		}
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(int & i)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%d", &i);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned int & ui)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%ud", &ui);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(short & s)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%hd", &s);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned short & us)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%hud", &us);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long & l)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%ld", &l);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned long & ul)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%uld", &ul);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long long & ll)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%I64d", &ll);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned long long & ull)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%I64ud", &ull);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(char & c)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, " \r\n\t%c", &c, (unsigned int)sizeof(char));
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned char & uc)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%hhu", &uc);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(float & f)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%f", &f);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(double & d)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%lf", &d);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long double & ld)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFile, "%Lf", &ld);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const wchar_t * wcstr)
{
	if ((m_FileMode&FileMode::Write) != 0)
	{
		fprintf_s(m_pFile, "%S", wcstr);
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const std::wstring & wstr)
{
	if ((m_FileMode&FileMode::Write) != 0)
	{
		fprintf_s(m_pFile, "%S", wstr.c_str());
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const wchar_t & wc)
{
	if ((m_FileMode&FileMode::Write) != 0)
	{
		fprintf_s(m_pFile, "%C", wc);
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const SpaceGameEngine::PrintMode & pm)
{
	if ((m_FileMode&FileMode::Write) != 0)
	{
		switch (pm)
		{
		case PrintMode::EndLine:
		{
			fscanf_s(m_pFile, "\n");
			fflush(m_pFile);
		}
		default:
			break;
		}
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const char * cstr)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%s", cstr);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const std::string & str)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%s", str.c_str());
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const int & i)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%d", i);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned int & ui)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%ud", ui);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const short & s)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%hd", s);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned short & us)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%hud", us);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long & l)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%ld", l);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned long & ul)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%lud", ul);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long long & ll)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%I64d", ll);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned long long & ull)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%I64ud", ull);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const char & c)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%c", c);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned char & uc)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%hhu", uc);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const float & f)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%f", f);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const double & d)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%lf", d);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long double & ld)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%Lf", ld);
	return *this;
}

SpaceGameEngine::Vector<std::string> SpaceGameEngine::GetDirectoryName(const std::string & filepath)
{
	if (filepath.empty())
		return Vector<std::string>();

	Vector<std::string> re;
	std::string buffer;
	int index = 0;

	char c = ' ';
	while (c == ' ')
		c = filepath[index++];
	while (index<=filepath.length())
	{
		if (c != '/')
		{
			buffer += c;
		}
		else
		{
			re.push_back(buffer);
			buffer.clear();
		}
		c = filepath[(index++)%filepath.length()];
	}
	return re;
}

void SpaceGameEngine::CheckAndCreateDirectory(const std::string & str)
{
	auto folder = GetDirectoryName(str);
	std::string buffer;
	for (int i = 0; i<folder.size(); i++)
	{
		if (folder[i] == "." || folder[i] == "..")
		{
			buffer += folder[i] + "/";
		}
		else
		{
			buffer += folder[i] + "/";
			if (_access(buffer.c_str(), 0) == -1)
				_mkdir(buffer.c_str());
		}
	}
}
