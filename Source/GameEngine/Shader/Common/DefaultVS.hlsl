/*
Default Shader for the Space Game Engine
*/
cbuffer Data : register(b0)
{
	float4x4 WorldMatrix;
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
	float4 DeltaTime;
};
struct DefaultVertexInput
{
	float4 Position : POSITION;
	float4 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD0;
};

struct DefaultVertexOutput
{
	float4 Position : POSITION;
	float4 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD0;
};

DefaultVertexOutput main(DefaultVertexInput input)
{
	DefaultVertexOutput output;

	output.Position = mul(input.Position, WorldMatrix);
	output.Position = mul(output.Position, ViewMatrix);
	output.Position = mul(output.Position, ProjectionMatrix);

	output.Normal = input.Normal;
	output.TextureCoord = input.TextureCoord;

	return output;
}