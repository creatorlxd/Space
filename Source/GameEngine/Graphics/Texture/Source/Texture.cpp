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

			D3D11_MAPPED_SUBRESOURCE mappeddata;
			HR(SpaceEngineWindow->GetD3DDeviceContext()->Map(dst, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappeddata));
			SpaceEngineWindow->GetD3DDeviceContext()->Unmap(dst, 0);
		}
		else
		{
			D3D11_TEXTURE2D_DESC texdesc;
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			ID3D11Resource* src = nullptr;
			ID3D11Resource* dst = nullptr;
			ID3D11Texture2D* ptex = nullptr;
			ID3D11Texture2D* texbuff = nullptr;
			texture.m_pContent->GetResource(&src);
			texture.m_pContent->GetDesc(&desc);
			HR(src->QueryInterface <ID3D11Texture2D>(&ptex));
			ptex->GetDesc(&texdesc);
			SpaceEngineWindow->GetD3DDevice()->CreateTexture2D(&texdesc, NULL, (ID3D11Texture2D**)&texbuff);
			SpaceEngineWindow->GetD3DDevice()->CreateShaderResourceView(texbuff, &desc, &m_pContent);
			m_pContent->GetResource(&dst);
			SpaceEngineWindow->GetD3DDeviceContext()->CopyResource(dst, src);

			D3D11_MAPPED_SUBRESOURCE mappeddata;
			HR(SpaceEngineWindow->GetD3DDeviceContext()->Map(dst, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappeddata));
			SpaceEngineWindow->GetD3DDeviceContext()->Unmap(dst, 0);
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

			D3D11_MAPPED_SUBRESOURCE mappeddata;
			HR(SpaceEngineWindow->GetD3DDeviceContext()->Map(dst, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappeddata));
			SpaceEngineWindow->GetD3DDeviceContext()->Unmap(dst, 0);
		}
		else
		{
			D3D11_TEXTURE2D_DESC texdesc;
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			ID3D11Resource* src = nullptr;
			ID3D11Resource* dst = nullptr;
			ID3D11Texture2D* ptex = nullptr;
			ID3D11Texture2D* texbuff = nullptr;
			texture.m_pContent->GetResource(&src);
			texture.m_pContent->GetDesc(&desc);
			HR(src->QueryInterface <ID3D11Texture2D>(&ptex));
			ptex->GetDesc(&texdesc);
			SpaceEngineWindow->GetD3DDevice()->CreateTexture2D(&texdesc, NULL, (ID3D11Texture2D**)&texbuff);
			SpaceEngineWindow->GetD3DDevice()->CreateShaderResourceView(texbuff, &desc, &m_pContent);
			m_pContent->GetResource(&dst);
			SpaceEngineWindow->GetD3DDeviceContext()->CopyResource(dst, src);
		
			D3D11_MAPPED_SUBRESOURCE mappeddata;
			HR(SpaceEngineWindow->GetD3DDeviceContext()->Map(dst, 0, D3D11_MAP_WRITE_NO_OVERWRITE,0,&mappeddata));
			SpaceEngineWindow->GetD3DDeviceContext()->Unmap(dst, 0);
		}
	}
	return *this;
}
