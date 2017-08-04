#include "stdafx.h"
#include "../Include/VertexShader.h" 
using namespace SpaceGameEngine;

SpaceGameEngine::VertexShader::VertexShader()
{
	m_pContent = nullptr;
	m_pBuffer = nullptr;
	m_pReflection = nullptr;
}

SpaceGameEngine::VertexShader::~VertexShader()
{
	Release();
}

void SpaceGameEngine::VertexShader::Release()
{
	SafeRelease(m_pContent);
	SafeRelease(m_pBuffer);
	SafeRelease(m_pReflection);
}

void SpaceGameEngine::VertexShader::InitFromFile(ID3D11Device* pDevice, LPCWSTR filename, const std::string& includefilename, const std::string& entryname, D3D_SHADER_MACRO* macros)
{
	if (pDevice == nullptr)
	{
		ThrowError(L"指针不能为空");
		return;
	}
	CompileShaderFromFile(filename, includefilename, entryname, "vs_5_0", macros, &m_pBuffer);
	pDevice->CreateVertexShader(m_pBuffer->GetBufferPointer(), m_pBuffer->GetBufferSize(), NULL, &m_pContent);
	D3DReflect(m_pBuffer->GetBufferPointer(), m_pBuffer->GetBufferSize(), IID_ID3D11ShaderReflection,(void**)&m_pReflection);
}

void SpaceGameEngine::VertexShader::InitFromFile(ID3D11Device* pDevice, LPCWSTR filename)
{
	if (pDevice == nullptr)
	{
		ThrowError(L"指针不能为空");
		return;
	}
	InitFromFile(pDevice,filename,"", "main", NULL);
}

void SpaceGameEngine::VertexShader::SetAsMainShader(ID3D11DeviceContext* pDeviceContext)
{
	if (pDeviceContext == nullptr)
	{
		ThrowError(L"指针不能为空");
		return;
	}
	pDeviceContext->VSSetShader(m_pContent, NULL, 0);
}

ID3DBlob * SpaceGameEngine::VertexShader::GetBuffer()
{
	return m_pBuffer;
}

bool SpaceGameEngine::VertexShader::operator=(const VertexShader & vs)
{
	Release();
	m_pBuffer = vs.m_pBuffer;
	m_pContent = vs.m_pContent;
	return true;
}
