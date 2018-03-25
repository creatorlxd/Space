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
	SafeRelease(m_pContent);
	SafeRelease(m_pBuffer);
	SafeRelease(m_pReflection);
}

void SpaceGameEngine::VertexShader::Clear()
{
	SafeRelease(m_pContent);
	SafeRelease(m_pBuffer);
	SafeRelease(m_pReflection);
	m_pContent = nullptr;
	m_pBuffer = nullptr;
	m_pReflection = nullptr;
}

void SpaceGameEngine::VertexShader::InitFromFile(ID3D11Device* pDevice, LPCWSTR filename, const String& includefilename, const String& entryname, D3D_SHADER_MACRO* macros)
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

/*
bool SpaceGameEngine::VertexShader::operator=(const VertexShader & vs)
{
	Release();
	m_pBuffer = vs.m_pBuffer;
	m_pContent = vs.m_pContent;
	m_pReflection = vs.m_pReflection;
	return true;
}
*/