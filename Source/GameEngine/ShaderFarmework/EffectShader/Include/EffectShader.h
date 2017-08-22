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
	private:
		ID3DX11Effect* m_pContent;
	};
}