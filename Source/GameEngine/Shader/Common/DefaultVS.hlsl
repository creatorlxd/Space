/*
Default Shader for the Space Game Engine
*/
cbuffer Data
{
	float4x4 WorldMatrix;
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
	float4 DeltaTime;
};
struct DefaultVertex
{
	float4 Position : POSITION;
	float4 Normal : NORMAL;
	float2 TextureCoord : TEXCOORD0;
};

DefaultVertex main(DefaultVertex input)
{
	return input;
}