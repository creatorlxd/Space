/*
Default Shader for the Space Game Engine
*/

struct DefaultVertexOutput
{
	float4 Position : POSITION;
	float4 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD0;
};

float4 main(DefaultVertexOutput input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}