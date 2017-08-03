#pragma once
#include "stdafx.h"
namespace SpaceGameEngine
{
#ifndef SPACE
#define SPACE

#ifdef _UNICODE
#define tcin wcin
#define tfstream wfstream
#else
#define tcin cin
#define tfstream fstream
#endif

#define STRING(str) #str

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILEW__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

	using tstring = std::conditional<std::is_same<TCHAR, char>::value, std::string, std::wstring>::type;

	template <typename _T> void SafeRelease(_T& p) { if (p) { p->Release(); p = nullptr; } }

	//-----------------------------------【FVF顶点格式】---------------------------------------------

	struct DefaultVertex //顶点结构体
	{
		XMFLOAT3 m_Position;	//三维坐标
		XMFLOAT3 m_Normal;//顶点法向量坐标
		XMFLOAT2 m_TextureCoord;		//纹理坐标
	};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)	//FVF灵活顶点格式

	namespace Colors
	{
		XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
		XMGLOBALCONST XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
	}

	//----------------------------------------------------------------------------------------------
	tstring StringToTString(const std::string& str);				//string转wstring,目前只支持英文

	std::string TStringToString(const tstring& tstr);				//wstring转string,目前只支持英文

	float GetDeltaTime();																	//获取时间间隔

	//TODO:报错后的处理
	void ThrowError(const tstring& errormessege);										//报错

	std::vector<std::pair<std::string, std::string> > ReadAssetListFromFile(const std::string& filename);	//从文件中读取资产文件列表

	//----------------------------------------------------------------------------------------------
	void SetDefaultInputLayout(ID3D11Device* device,ID3DBlob* ShaderByteCode, ID3D11InputLayout** inputlayout);										//设置默认的顶点输入格式（需要shader)
	void CompileShaderFromFile(LPCWSTR filename, const std::string& includefilename, const std::string& entryname, const std::string& target, D3D_SHADER_MACRO* macros, ID3DBlob** ShaderByteCode);	//从文件中读取并编译Shader
#endif

}