/*
Copyright 2017 creatorlxd

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
#pragma once 
#include "stdafx.h"
#include "Space.h"

namespace SpaceGameEngine
{
	class EffectShader
	{
	public:
		EffectShader();
		virtual ~EffectShader();
		virtual void Release();
		virtual void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename, D3D_SHADER_MACRO* macros);
		virtual void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename);

		void SetTechnique(const std::string& filename);

		EffectShader(const EffectShader&) = delete;
		void operator = (const EffectShader& shader) = delete;
	protected:
		ID3DX11Effect* m_pContent;
	public:
		ID3DX11EffectTechnique* m_pTechnique;
	};

	class DefaultEffectShader :public EffectShader
	{
	public:
		DefaultEffectShader();
		~DefaultEffectShader();
		void Release();
		void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename);
		void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename, D3D_SHADER_MACRO* macros);
	public:
		ID3DX11EffectMatrixVariable* m_pWorldViewProjMatrix;
		ID3DX11EffectVectorVariable* m_pDeltaTime;
		ID3DX11EffectVectorVariable* m_pCameraPosition;
		ID3DX11EffectVariable* m_pMaterial;
		ID3DX11EffectVariable* m_pLights;
		ID3DX11EffectMatrixVariable* m_pWorldMatrix;
		ID3DX11EffectMatrixVariable* m_pInverseTransposeMatrix;
		ID3DX11EffectMatrixVariable* m_pTextureTransformMatrix;
		ID3DX11EffectShaderResourceVariable* m_pTexture;
	};
}