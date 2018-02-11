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
#include "../Include/Texture.h"

SpaceGameEngine::TextureForShader::TextureForShader()
{
	m_pContent = nullptr;
}

SpaceGameEngine::TextureForShader::TextureForShader(const TextureForShader & texture)
{
	if (texture.m_pContent)
	{
		if (m_pContent)
		{
			ID3D11Resource* dst = nullptr;
			ID3D11Resource* src = nullptr;
			m_pContent->GetResource(&dst);
			texture.m_pContent->GetResource(&src);
			SpaceEngineWindow->GetD3DDeviceContext()->CopyResource(dst, src);
		}
		else
		{
			D3D11_TEXTURE2D_DESC desc;
			ID3D11Resource* src = nullptr;
			ID3D11Resource* dst = nullptr;
			texture.m_pContent->GetResource(&src);
			auto ptex = dynamic_cast<ID3D11Texture2D*>(src);
			ptex->GetDesc(&desc);
			SpaceEngineWindow->GetD3DDevice()->CreateTexture2D(&desc, NULL, (ID3D11Texture2D**)&m_pContent);
			m_pContent->GetResource(&dst);
			SpaceEngineWindow->GetD3DDeviceContext()->CopyResource(dst, src);
		}
	}
}

SpaceGameEngine::TextureForShader::~TextureForShader()
{
	if (m_pContent)
		SafeRelease(m_pContent);
}

void SpaceGameEngine::TextureForShader::Release()
{
	if (m_pContent)
		SafeRelease(m_pContent);
}

SpaceGameEngine::TextureForShader& SpaceGameEngine::TextureForShader::operator=(const TextureForShader & texture)
{
	if (texture.m_pContent)
	{
		if (m_pContent)
		{
			ID3D11Resource* dst = nullptr;
			ID3D11Resource* src = nullptr;
			m_pContent->GetResource(&dst);
			texture.m_pContent->GetResource(&src);
			SpaceEngineWindow->GetD3DDeviceContext()->CopyResource(dst, src);
		}
		else
		{
			D3D11_TEXTURE2D_DESC desc;
			ID3D11Resource* src = nullptr;
			ID3D11Resource* dst = nullptr;
			texture.m_pContent->GetResource(&src);
			ID3D11Texture2D* ptex;
			HR(src->QueryInterface <ID3D11Texture2D>(&ptex));
			ptex->GetDesc(&desc);
			SpaceEngineWindow->GetD3DDevice()->CreateTexture2D(&desc, NULL, (ID3D11Texture2D**)&m_pContent);
			m_pContent->GetResource(&dst);
			SpaceEngineWindow->GetD3DDeviceContext()->CopyResource(dst, src);
		}
	}
	return *this;
}
