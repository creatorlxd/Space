#pragma once 
#include "stdafx.h"
#include "Space.h"
namespace SpaceGameEngine
{
	class PixelShader			//像素着色器
	{
	public:
		PixelShader();
		~PixelShader();
		void Release();
		void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename, const std::string& includefilename, const std::string& entryname, D3D_SHADER_MACRO* macros);
		void InitFromFile(ID3D11Device* pDevice, LPCWSTR filename);			//简化版:includefilename = "",entryname = "main"
		void SetAsMainShader(ID3D11DeviceContext* pDeviceContext);							//设置为当前使用的shader
		ID3DBlob* GetBuffer();

		template<typename T>
		void SetConstantBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, int index, T& content);

		bool operator = (const PixelShader& ps);
	private:
		ID3D11PixelShader* m_pContent;
		ID3DBlob* m_pBuffer;
		ID3D11ShaderReflection* m_pReflection;
	};
	template<typename T>
	inline void PixelShader::SetConstantBuffer(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, int index, T & content)
	{
		ID3D11Buffer* buffer = nullptr;

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

		HR(pDevice->CreateBuffer(&cbDesc, &InitData, &buffer));

		pDeviceContext->PSSetConstantBuffers(index, 1, &buffer);

		SafeRelease(&buffer);
	}
}