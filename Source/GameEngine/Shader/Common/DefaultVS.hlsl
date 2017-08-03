/*
Default Shader for the Space Game Engine
*/
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