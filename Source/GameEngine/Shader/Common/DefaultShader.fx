cbuffer SceneData : register(b0)
{
	float4 DeltaTime;
};
cbuffer ObjectData : register(b1)
{
	float4x4 WorldViewProjMatrix;
};
struct DefaultVertexInput
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD0;
};

struct DefaultVertexOutput
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD0;
};

DefaultVertexOutput VS(DefaultVertexInput input)
{
	DefaultVertexOutput output;

	output.Position = mul(float4(input.Position,1.0f), WorldViewProjMatrix);

	output.Normal = input.Normal;
	output.TextureCoord = input.TextureCoord;

	return output;
}

float4 PS(DefaultVertexOutput input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

technique11 Main
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
