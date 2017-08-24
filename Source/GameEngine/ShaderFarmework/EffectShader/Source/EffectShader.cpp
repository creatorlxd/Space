#include "stdafx.h"
#include "../Include/EffectShader.h" 

using namespace SpaceGameEngine;

SpaceGameEngine::EffectShader::EffectShader()
{
	m_pContent = nullptr;
	m_pTechnique = nullptr;
	m_pWorldViewProjMatrix = nullptr;
	m_pDeltaTime = nullptr;
}

SpaceGameEngine::EffectShader::~EffectShader()
{
	Release();
}

void SpaceGameEngine::EffectShader::Release()
{
	SafeRelease(m_pContent);
	m_pTechnique = nullptr;
	m_pDeltaTime = nullptr;
	m_pWorldViewProjMatrix = nullptr;
}

void SpaceGameEngine::EffectShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename, const std::string & includefilename, D3D_SHADER_MACRO * macros)
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
	ID3DBlob* ErrorMessage=nullptr;
	D3DX11CompileEffectFromFile(filename, macros, D3D_COMPILE_STANDARD_FILE_INCLUDE, shaderFlags, NULL, pDevice, &m_pContent, &ErrorMessage);
	SafeRelease(ErrorMessage);

	m_pDeltaTime = m_pContent->GetVariableByName("DeltaTime")->AsVector();
	m_pWorldViewProjMatrix = m_pContent->GetVariableByName("WorldViewProjMatrix")->AsMatrix();
}

void SpaceGameEngine::EffectShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename)
{
	InitFromFile(pDevice, filename, "", NULL);
}

void SpaceGameEngine::EffectShader::SetTechnique(const std::string & filename)
{
	m_pTechnique=m_pContent->GetTechniqueByName(filename.c_str());
}

void SpaceGameEngine::EffectShader::operator=(const EffectShader & shader)
{
	Release();
	m_pContent = shader.m_pContent;
	m_pTechnique = shader.m_pTechnique;
	m_pDeltaTime = shader.m_pDeltaTime;
	m_pWorldViewProjMatrix = shader.m_pWorldViewProjMatrix;
}
