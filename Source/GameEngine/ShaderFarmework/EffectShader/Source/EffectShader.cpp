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
	SafeRelease(m_pTechnique);
	SafeRelease(m_pWorldViewProjMatrix);
	SafeRelease(m_pDeltaTime);
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

}

void SpaceGameEngine::EffectShader::InitFromFile(ID3D11Device * pDevice, LPCWSTR filename)
{
	InitFromFile(pDevice, filename, NULL, NULL);
}

void SpaceGameEngine::EffectShader::SetTechnique(const std::string & filename)
{
	m_pContent->GetTechniqueByName(filename.c_str());
}
