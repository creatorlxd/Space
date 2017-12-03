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

/*
Default Shader for the Space Game Engine
*/
cbuffer SceneData : register(b0)
{
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
	float4 DeltaTime;
};
cbuffer ObjectData : register(b1)
{
	float4x4 WorldMatrix;
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