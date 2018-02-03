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
#include "Space.h"
using namespace SpaceGameEngine;

unsigned int SpaceGameEngine::HashString(const std::string & str)
{
	std::hash<std::string> sh;
	return static_cast<unsigned int>(sh(str));
}

void SpaceGameEngine::SetDefaultInputLayout(ID3D11Device* device, ID3DBlob* ShaderByteCode,ID3D11InputLayout** inputlayout)
{
	static D3D11_INPUT_ELEMENT_DESC indesc[]=
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	device->CreateInputLayout(indesc, 3, ShaderByteCode->GetBufferPointer(), ShaderByteCode->GetBufferSize(), inputlayout);
}

void SpaceGameEngine::SetDefaultInputLayout(ID3D11Device * device, const void * shadercode, SIZE_T size, ID3D11InputLayout ** inputlayout)
{
	static D3D11_INPUT_ELEMENT_DESC indesc[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};
	device->CreateInputLayout(indesc, 3, shadercode, size, inputlayout);

}

void SpaceGameEngine::SetDefaultResterizerState(ID3D11Device * device, ID3D11RasterizerState ** rasterizerstate)
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;
	desc.DepthClipEnable = true;
	HR(device->CreateRasterizerState(&desc, rasterizerstate));
}

void SpaceGameEngine::CompileShaderFromFile(LPCWSTR filename,const std::string& includefilename, const std::string & entryname, const std::string & target, D3D_SHADER_MACRO* macros,ID3DBlob ** ShaderByteCode)
{
	ID3DBlob* errormsg;
	LPCSTR sourcefile = includefilename.empty() == true ? NULL : includefilename.c_str();
	ID3DInclude* include = includefilename.empty() == true ? NULL : ((ID3DInclude*)(UINT_PTR)1);
	D3DCompileFromFile(filename, macros, include, entryname.c_str(), target.c_str(), 0, 0, ShaderByteCode, &errormsg);
}

XMFLOAT4X4 SpaceGameEngine::GetProjectionMatrix(float angle,float aspectratio,float nearz,float farz)
{
	static float option_buff[4] = { 0,0,0,0 };
	static XMFLOAT4X4 re;
	if (option_buff[0] != angle || option_buff[1] != aspectratio || option_buff[2] != nearz || option_buff[3] != farz)
	{
		option_buff[0] = angle;
		option_buff[1] = aspectratio;
		option_buff[2] = nearz;
		option_buff[3] = farz;
		XMMATRIX mbuff;
		mbuff = XMMatrixPerspectiveFovLH(angle, aspectratio, nearz, farz);
		XMStoreFloat4x4(&re, mbuff);
	}
	return re;
}
