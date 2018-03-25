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
#pragma once 
#include "Space.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3d11shader.h>

using namespace DirectX;

namespace SpaceGameEngine
{
	class VertexShader			//顶点着色器
	{
	public:
		VertexShader();
		~VertexShader();
		void Clear();
		void InitFromFile(ID3D11Device* pDevice,LPCWSTR filename, const String& includefilename, const String& entryname, D3D_SHADER_MACRO* macros);
		void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename);			//简化版:includefilename = "",entryname = "main"
		void SetAsMainShader(ID3D11DeviceContext* pDeviceContext);							//设置为当前使用的shader
		ID3DBlob* GetBuffer();

		template<typename T>
		void SetConstantBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext,int index, T& content);

		VertexShader(const VertexShader&) = delete;
		bool operator = (const VertexShader& vs) = delete;
	public:
		struct SceneData
		{
			XMFLOAT4X4 m_ViewMatrix, m_ProjectionMatrix;
			XMFLOAT4 m_DeltaTime;
		};
		struct ObjectData
		{
			XMFLOAT4X4 m_WorldMatrix;
		};
		static const int SceneDataIndex = 0;
		static const int ObjectDataIndex = 1;
		SceneData m_SceneData;
		ObjectData m_ObjectData;
	private:
		ID3D11VertexShader* m_pContent;
		ID3DBlob* m_pBuffer;
		ID3D11ShaderReflection* m_pReflection;
	};
	template<typename T>
	inline void VertexShader::SetConstantBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, int index, T & content)
	{
		//TODO:有可能会爆
		ID3D11Buffer* buffer=nullptr;

		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = sizeof(T);
		cbDesc.Usage = D3D11_USAGE_DYNAMIC;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = &content;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		HR(pDevice->CreateBuffer(&cbDesc, &InitData,&buffer));

		pDeviceContext->VSSetConstantBuffers(index, 1, &buffer);

		SafeRelease(buffer);
	}
}