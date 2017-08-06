#include "stdafx.h"
#include "../Include/PixelShader.h" 

using namespace SpaceGameEngine;

SpaceGameEngine::PixelShader::PixelShader()
{
	m_pContent = nullptr;
	m_pBuffer = nullptr;
	m_pReflection = nullptr;
}

SpaceGameEngine::PixelShader::~PixelShader()
{
	Release();
}

void SpaceGameEngine::PixelShader::Release()
{
	SafeRelease(m_pContent);
	SafeRelease(m_pBuffer);
	SafeRelease(m_pReflection);
}

void SpaceGameEngine::PixelShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename, const std::string & includefilename, const std::string & entryname, D3D_SHADER_MACRO * macros)
{
	if (pDevice == nullptr)
	{
		ThrowError(L"指针不能为空");
		return;
	}
	CompileShaderFromFile(filename, includefilename, entryname, "ps_5_0", macros, &m_pBuffer);
	pDevice->CreatePixelShader(m_pBuffer->GetBufferPointer(), m_pBuffer->GetBufferSize(), NULL, &m_pContent);
	D3DReflect(m_pBuffer->GetBufferPointer(), m_pBuffer->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&m_pReflection);
}

void SpaceGameEngine::PixelShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename)
{
	if (pDevice == nullptr)
	{
		ThrowError(L"指针不能为空");
		return;
	}
	InitFromFile(pDevice, filename, "", "main", NULL);
}

void SpaceGameEngine::PixelShader::SetAsMainShader(ID3D11DeviceContext * pDeviceContext)
{
	if (pDeviceContext == nullptr)
	{
		ThrowError(L"指针不能为空");
		return;
	}
	pDeviceContext->PSSetShader(m_pContent, NULL, 0);
}

ID3DBlob * SpaceGameEngine::PixelShader::GetBuffer()
{
	return m_pBuffer;
}

bool SpaceGameEngine::PixelShader::operator=(const PixelShader & vs)
{
	Release();
	m_pBuffer = vs.m_pBuffer;
	m_pContent = vs.m_pContent;
	return true;
}
