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
#include "../Include/RenderObject.h"

SpaceGameEngine::RenderObject::RenderObject() :m_ObjectOctree(&m_MeshForModelFileAsset.m_Vertices)
{
	m_pObject = nullptr;
	m_Mode = 0;
	m_IfRender = true;
	m_Type = RenderObjectType::Unkown;
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_pGlobalOctree = nullptr;
	m_pGlobalOctreeNode = nullptr;
	m_IfInit = false;
	m_IfHaveTransform = false;
	m_IfHaveMaterial = false;
	m_IfHaveTexture = false;
	m_IfHaveMesh = false;
}

SpaceGameEngine::RenderObject::~RenderObject()
{
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
	if (m_pObject)
	{
		m_pObject->SetRenderObject(nullptr);
	}
}

void SpaceGameEngine::RenderObject::Init()
{
	if (!m_IfInit)
	{
		if (m_Type == RenderObjectType::Model)
		{
			if (m_Shader.empty())
			{
				m_Shader.push_back(&SpaceEngineWindow->GetEffectShader());
			}

			if (m_Mode&ModelFileMode)
			{
				InitVertexBuffer();
				InitIndexBuffer();
				if ((m_Mode&RenderObject::WholeMode) == 0)
				{
					m_ObjectOctree.BuildTree(m_MeshForModelFileAsset.m_Indices);
				}
			}
		}
		m_IfInit = true;
	}
}

void SpaceGameEngine::RenderObject::Render()
{
	if (m_Type == RenderObjectType::Model)
	{
		if (m_Mode&ModelFileMode)
		{
			auto shaders = SpaceEngineWindow->GetDefaultEffectShader();

			//transform
			if (m_IfHaveTransform)
			{
				XMMATRIX mrebuff, mbuff;
				mbuff = XMMatrixScaling(m_TransformAsset.m_Scale.x, m_TransformAsset.m_Scale.y, m_TransformAsset.m_Scale.z);
				mrebuff = mbuff;
				mbuff = XMMatrixRotationX(m_TransformAsset.m_Rotation.x);
				mrebuff = XMMatrixMultiply(mrebuff, mbuff);
				mbuff = XMMatrixRotationY(m_TransformAsset.m_Rotation.y);
				mrebuff = XMMatrixMultiply(mrebuff, mbuff);
				mbuff = XMMatrixRotationZ(m_TransformAsset.m_Rotation.z);
				mrebuff = XMMatrixMultiply(mrebuff, mbuff);
				mbuff = XMMatrixTranslation(m_TransformAsset.m_Position.x, m_TransformAsset.m_Position.y, m_TransformAsset.m_Position.z);
				mrebuff = XMMatrixMultiply(mrebuff, mbuff);

				auto inversetransposemat = InverseTransposeMatrix(mrebuff);

				XMMATRIX result = mrebuff * XMLoadFloat4x4(&SceneData::m_ViewMatrix)*XMLoadFloat4x4(&SceneData::m_ProjectionMatrix);

				for (auto i : shaders)
				{
					i->m_pWorldViewProjMatrix->SetMatrix(reinterpret_cast<float*>(&result));
					i->m_pWorldMatrix->SetMatrix(reinterpret_cast<float*>(&mrebuff));
					i->m_pInverseTransposeMatrix->SetMatrix(reinterpret_cast<float*>(&inversetransposemat));
				}
			}

			//material
			if(m_IfHaveMaterial)
				for (auto i : shaders)
					i->m_pMaterial->SetRawValue(&m_MaterialAsset[0].m_Content, 0, sizeof(m_MaterialAsset[0].m_Content));
			
			//texture
			if (m_IfHaveTexture)
			{
				if (m_TextureAsset[0].first.m_Content.m_pContent)
				{
					for (auto i : shaders)
					{
						i->m_pTextureTransformMatrix->SetMatrix(reinterpret_cast<float*>(&m_TextureAsset[0].second));
						i->m_pTexture->SetResource(m_TextureAsset[0].first.m_Content.m_pContent);
					}
				}
			}

			//mesh
			if (m_IfHaveMesh)
			{
				if (m_pVertexBuffer&&m_pIndexBuffer)
				{
					if ((m_Mode&RenderObject::WholeMode) == 0)
					{
						auto indices_buffer = m_ObjectOctree.Run(m_TransformAsset.m_Position, m_TransformAsset.m_Rotation, m_TransformAsset.m_Scale);
						D3D11_MAPPED_SUBRESOURCE mappeddata;
						HR(SpaceEngineWindow->GetD3DDeviceContext()->Map(m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappeddata));
						unsigned int* pi = reinterpret_cast<unsigned int*>(mappeddata.pData);
						for (unsigned int i = 0; i < indices_buffer.size(); i++)
							pi[i] = indices_buffer[i];
						SpaceEngineWindow->GetD3DDeviceContext()->Unmap(m_pIndexBuffer, 0);
						unsigned int v_strides = sizeof(DefaultVertex);
						unsigned int v_offset = 0;
						SpaceEngineWindow->GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &v_strides, &v_offset);
						SpaceEngineWindow->GetD3DDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

						D3DX11_TECHNIQUE_DESC techDesc;
						m_Shader[0]->m_pTechnique->GetDesc(&techDesc);
						for (UINT p = 0; p < techDesc.Passes; ++p)
						{
							m_Shader[0]->m_pTechnique->GetPassByIndex(p)->Apply(0, SpaceEngineWindow->GetD3DDeviceContext());

							SpaceEngineWindow->GetD3DDeviceContext()->DrawIndexed(indices_buffer.size(), 0, 0);
						}
					}
					else
					{
						unsigned int v_strides = sizeof(DefaultVertex);
						unsigned int v_offset = 0;
						SpaceEngineWindow->GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &v_strides, &v_offset);
						SpaceEngineWindow->GetD3DDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

						D3DX11_TECHNIQUE_DESC techDesc;
						m_Shader[0]->m_pTechnique->GetDesc(&techDesc);
						for (UINT p = 0; p < techDesc.Passes; ++p)
						{
							m_Shader[0]->m_pTechnique->GetPassByIndex(p)->Apply(0, SpaceEngineWindow->GetD3DDeviceContext());

							SpaceEngineWindow->GetD3DDeviceContext()->DrawIndexed(m_MeshForModelFileAsset.m_Indices.size(), 0, 0);
						}
					}
				}
			}
		}
	}
}

void SpaceGameEngine::RenderObject::SetMesh(const MeshForModelFileAsset & mmfa)
{
	m_IfHaveMesh = true;
	m_MeshForModelFileAsset = mmfa;
	if (m_IfInit)
	{
		SafeRelease(m_pVertexBuffer);
		SafeRelease(m_pIndexBuffer);
		m_ObjectOctree.CleanUp();
		m_ObjectOctree.ResetVertexData(&m_MeshForModelFileAsset.m_Vertices);
		if (m_Type == RenderObjectType::Model)
		{
			if (m_Mode&ModelFileMode)
			{
				InitVertexBuffer();
				InitIndexBuffer();
				if ((m_Mode&RenderObject::WholeMode) == 0)
				{
					m_ObjectOctree.BuildTree(m_MeshForModelFileAsset.m_Indices);
				}
				if ((m_Mode&RenderObject::DynamicMode) == 0)
				{
					Vector<XMFLOAT3> points;
					for (const auto& i : m_MeshForModelFileAsset.m_Vertices)
					{
						points.push_back(i.m_Position);
					}
					m_BaseSpace = GetAxisAlignedBoundingBox(points);
					m_Space = TransformByWorldMatrix(m_TransformAsset.m_Position, m_TransformAsset.m_Rotation, m_TransformAsset.m_Scale, m_BaseSpace);
					m_pGlobalOctreeNode = m_pGlobalOctree->UpdateObject(GlobalOctreeData(m_pObject->GetRenderObject()->m_Space, m_pObject));
				}
			}
		}
	}
}

void SpaceGameEngine::RenderObject::InitVertexBuffer()
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.ByteWidth = sizeof(DefaultVertex)*m_MeshForModelFileAsset.m_Vertices.size();
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initdata;
	initdata.pSysMem = m_MeshForModelFileAsset.m_Vertices.data();

	HR(SpaceEngineWindow->GetD3DDevice()->CreateBuffer(&desc, &initdata, &m_pVertexBuffer));
}

void SpaceGameEngine::RenderObject::InitIndexBuffer()
{
	D3D11_BUFFER_DESC desc;
	if ((m_Mode&RenderObject::WholeMode) == 0)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(unsigned int)*m_MeshForModelFileAsset.m_Indices.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
	}
	else
	{
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = sizeof(unsigned int)*m_MeshForModelFileAsset.m_Indices.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
	}

	D3D11_SUBRESOURCE_DATA initdata;
	initdata.pSysMem = m_MeshForModelFileAsset.m_Indices.data();

	HR(SpaceEngineWindow->GetD3DDevice()->CreateBuffer(&desc, &initdata, &m_pIndexBuffer));
}
