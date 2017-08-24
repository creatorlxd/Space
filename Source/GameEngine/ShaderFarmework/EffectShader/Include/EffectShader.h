#pragma once 
#include "stdafx.h"
#include "Space.h"

namespace SpaceGameEngine
{
	class EffectShader
	{
	public:
		EffectShader();
		~EffectShader();
		void Release();
		void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename, const std::string& includefilename, D3D_SHADER_MACRO* macros);
		void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename);

		void SetTechnique(const std::string& filename);

		void operator = (const EffectShader& shader);
	private:
		ID3DX11Effect* m_pContent;
	public:
		ID3DX11EffectTechnique* m_pTechnique;
		ID3DX11EffectMatrixVariable* m_pWorldViewProjMatrix;
		ID3DX11EffectVectorVariable* m_pDeltaTime;

		//Buffer
		XMFLOAT4X4 m_ViewMatrix;
		XMFLOAT4X4 m_ProjectionMatrix;
	};
}