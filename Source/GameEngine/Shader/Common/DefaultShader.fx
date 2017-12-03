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
};
cbuffer ObjectData : register(b1)
{
	float4x4 g_WorldViewProjMatrix;
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
	output.m_WorldPosition = input.m_Position;

	output.m_Normal = input.m_Normal;
	output.m_TextureCoord = input.m_TextureCoord;

	return output;
}

float4 PS(DefaultVertexOutput input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
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
