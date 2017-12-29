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
#include "../Lighting/Light.fx"

cbuffer SceneData : register(b0)
{
	float4 g_DeltaTime;
	float4 g_CameraPosition;		//eye position
	Lights g_Lights;
};
cbuffer ObjectData : register(b1)
{
	float4x4 g_WorldViewProjMatrix;
	float4x4 g_WorldMatrix;
	float4x4 g_InverseTransposeMatrix;
	Material g_Material;
};
struct DefaultVertexInput
{
	float3 m_Position : POSITION;
	float3 m_Normal : NORMAL;
	float2 m_TextureCoord : TEXCOORD0;
};

struct DefaultVertexOutput
{
	float4 m_Position : SV_POSITION;
	float3 m_WorldPosition : POSITION;
	float3 m_Normal : NORMAL;
	float2 m_TextureCoord : TEXCOORD0;
};

DefaultVertexOutput VS(DefaultVertexInput input)
{
	DefaultVertexOutput output;

	output.m_Position = mul(float4(input.m_Position,1.0f), g_WorldViewProjMatrix);
	output.m_WorldPosition = mul(float4(input.m_Position,1.0f),g_WorldMatrix);

	output.m_Normal = mul(input.m_Normal,(float3x3)g_InverseTransposeMatrix);
	output.m_TextureCoord = input.m_TextureCoord;

	return output;
}

float4 PS(DefaultVertexOutput input) : SV_TARGET
{
	float4 color = float4(0.0f,0.0f,0.0f,1.0f);
	for (unsigned int i = 0; i < g_Lights.m_Size[0]; i++)
	{
		color += GetColorByLight(g_Material, g_Lights.m_Content[i], g_CameraPosition.xyz, input.m_WorldPosition, input.m_Normal);
	}
	color.a = g_Material.m_Diffuse.a;
	return color;
}

technique11 MediumQuality
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}

technique11 HighQuality
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}

technique11 LowQuality
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
