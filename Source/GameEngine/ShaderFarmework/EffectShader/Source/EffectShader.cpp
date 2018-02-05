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
#include "../Include/EffectShader.h" 

using namespace SpaceGameEngine;

SpaceGameEngine::EffectShader::EffectShader()
{
	m_pContent = nullptr;
	m_pTechnique = nullptr;
}

SpaceGameEngine::EffectShader::~EffectShader()
{
	SafeRelease(m_pContent);
}

void SpaceGameEngine::EffectShader::Clear()
{
	SafeRelease(m_pContent);
	m_pTechnique = nullptr;
}

void SpaceGameEngine::EffectShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename, D3D_SHADER_MACRO * macros)
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
	ID3DBlob* ErrorMessage=nullptr;
	D3DX11CompileEffectFromFile(filename, macros, D3D_COMPILE_STANDARD_FILE_INCLUDE, shaderFlags, NULL, pDevice, &m_pContent, &ErrorMessage);
	SafeRelease(ErrorMessage);
}

void SpaceGameEngine::EffectShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename)
{
	InitFromFile(pDevice, filename, NULL);
}

void SpaceGameEngine::EffectShader::SetTechnique(const std::string & filename)
{
	m_pTechnique=m_pContent->GetTechniqueByName(filename.c_str());
}

/*
void SpaceGameEngine::EffectShader::operator=(const EffectShader & shader)
{
	Release();
	m_pContent = shader.m_pContent;
	m_pTechnique = shader.m_pTechnique;
}
*/

SpaceGameEngine::DefaultEffectShader::DefaultEffectShader()
{
	EffectShader();
	m_pWorldViewProjMatrix = nullptr;
	m_pDeltaTime = nullptr;
	m_pMaterial = nullptr;
	m_pLights = nullptr;
	m_pInverseTransposeMatrix = nullptr;
	m_pWorldMatrix = nullptr;
}

SpaceGameEngine::DefaultEffectShader::~DefaultEffectShader()
{
	
}

void SpaceGameEngine::DefaultEffectShader::Clear()
{
	EffectShader::Clear();
	m_pDeltaTime = nullptr;
	m_pWorldViewProjMatrix = nullptr;
	m_pCameraPosition = nullptr;
	m_pMaterial = nullptr;
	m_pLights = nullptr;
	m_pInverseTransposeMatrix = nullptr;
	m_pWorldMatrix = nullptr;
}

void SpaceGameEngine::DefaultEffectShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename)
{
	DefaultEffectShader::InitFromFile(pDevice, filename, NULL);
}

void SpaceGameEngine::DefaultEffectShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename, D3D_SHADER_MACRO * macros)
{
	EffectShader::InitFromFile(pDevice, filename, macros);

	//Intialization Variable
	m_pDeltaTime = m_pContent->GetVariableByName("g_DeltaTime")->AsVector();
	m_pWorldViewProjMatrix = m_pContent->GetVariableByName("g_WorldViewProjMatrix")->AsMatrix();
	m_pCameraPosition = m_pContent->GetVariableByName("g_CameraPosition")->AsVector();
	m_pMaterial = m_pContent->GetVariableByName("g_Material");
	m_pLights = m_pContent->GetVariableByName("g_Lights");
	m_pInverseTransposeMatrix = m_pContent->GetVariableByName("g_InverseTransposeMatrix")->AsMatrix();
	m_pWorldMatrix = m_pContent->GetVariableByName("g_WorldMatrix")->AsMatrix();
	m_pTextureTransformMatrix = m_pContent->GetVariableByName("g_TextureTransformMatrix")->AsMatrix();
	m_pTexture = m_pContent->GetVariableByName("g_Texture")->AsShaderResource();
}
