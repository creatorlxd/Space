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

#include <DirectXMath.h>

#include "Def.h"
#include "../MemoryManager/Include/AllocatorForSTL.hpp"
#include "../Utility/Include/StringConverter.h"
#include "../Utility/Include/InputDevice.h"
#include "../Utility/Include/TimeTool.h"
#include "DDSTextureLoader/DDSTextureLoader.h"

using namespace DirectX;

namespace SpaceGameEngine
{
	//-----------------------------------【FVF顶点格式】---------------------------------------------

	struct DefaultVertex //顶点结构体
	{
		XMFLOAT3 m_Position;	//三维坐标
		XMFLOAT3 m_Normal;//顶点法向量坐标
		XMFLOAT2 m_TextureCoord;		//纹理坐标
	};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)	//FVF灵活顶点格式

	namespace Colors
	{
		XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
		XMGLOBALCONST XMVECTORF32 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
		XMGLOBALCONST XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
	}

	//----------------------------------------------------------------------------------------------

	unsigned int HashString(const std::string& str);

	//----------------------------------------------------------------------------------------------
	void SetDefaultInputLayout(ID3D11Device* device,ID3DBlob* ShaderByteCode, ID3D11InputLayout** inputlayout);				//设置默认的顶点输入格式（需要shader)
	void SetDefaultInputLayout(ID3D11Device* device, const void* shadercode, SIZE_T size, ID3D11InputLayout** inputlayout);
	void SetDefaultResterizerState(ID3D11Device* device, ID3D11RasterizerState** rasterizerstate);				//设置默认的RS状态
	void CompileShaderFromFile(LPCWSTR filename, const std::string& includefilename, const std::string& entryname, const std::string& target, D3D_SHADER_MACRO* macros, ID3DBlob** ShaderByteCode);	//从文件中读取并编译Shader

	XMFLOAT4X4 GetProjectionMatrix(float angle=XM_PIDIV4, float aspectratio=1, float nearz=1.0f, float farz=1000.0f);

}