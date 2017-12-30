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

struct Material			
{
	float4 m_Ambient;
	float4 m_Diffuse;
	float4 m_Specular; // Specular.w = SpecularPower
	float4 m_Reflect;
};

struct Light
{
	float4 m_Ambient;
	float4 m_Diffuse;
	float4 m_Specular;

	float3 m_Position;
	float m_Range;

	float3 m_Direction;
	float m_SpotLightOption;

	float3 m_LightOption;
	unsigned int m_Type;
};

void ComputeDirectionLight(Material material, Light light, float3 normal, float3 toeye,
	out  float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	ambient = material.m_Ambient*light.m_Ambient;

	float diffuse_factor = dot(-light.m_Direction, normal);

	[flatten]
	if (diffuse_factor > 0.0f)
	{
		float3 v = reflect(light.m_Direction, normal);
		float spec_factor = pow(max(dot(v, toeye), 0.0f), material.m_Specular.w);

		diffuse = diffuse_factor*material.m_Diffuse*light.m_Diffuse;
		spec = spec_factor*material.m_Specular*light.m_Specular;
	}
}

void ComputePointLight(Material material, Light light, float3 pos, float3 normal, float3 toeye,
	out  float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	light.m_Direction = pos - light.m_Position;
	
	float dis = length(light.m_Direction);

	if (dis > light.m_Range)
		return;

	ambient = material.m_Ambient*light.m_Ambient;
	light.m_Direction = normalize(light.m_Direction);

	float diffuse_factor = dot(-light.m_Direction, normal);

	[flatten]
	if (diffuse_factor > 0.0f)
	{
		float3 v = reflect(light.m_Direction, normal);
		float spec_factor = pow(max(dot(v, toeye), 0.0f), material.m_Specular.w);

		diffuse = diffuse_factor*material.m_Diffuse*light.m_Diffuse;
		spec = spec_factor*material.m_Specular*light.m_Specular;
	}

	float att = 1.0f / dot(light.m_LightOption, float3(1.0f, dis, dis*dis));
	diffuse *= att;
	spec *= att;
}

void ComputeSpotLight(Material material, Light light, float3 pos, float3 normal, float3 toeye,
	out  float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 light_vec = pos - light.m_Position;

	float dis = length(light_vec);

	if (dis > light.m_Range)
		return;

	ambient = material.m_Ambient*light.m_Ambient;
	light_vec = normalize(light_vec);

	float diffuse_factor = dot(-light_vec, normal);

	[flatten]
	if (diffuse_factor > 0.0f)
	{
		float3 v = reflect(light_vec, normal);
		float spec_factor = pow(max(dot(v, toeye), 0.0f), material.m_Specular.w);

		diffuse = diffuse_factor*material.m_Diffuse*light.m_Diffuse;
		spec = spec_factor*material.m_Specular*light.m_Specular;
	}

	float spot = pow(max(dot(light_vec, light.m_Direction), 0.0f), light.m_SpotLightOption);

	float att = spot / dot(light.m_LightOption, float3(1.0f, dis, dis*dis));
	ambient *= att;
	diffuse *= att;
	spec *= att;
}

void ComputeCommonLight(Material material, Light light, float3 pos, float3 normal, float3 toeye,
	out float4 ambient, out float4 diffuse, out float4 spec)
{
	switch (light.m_Type)
	{
	case 1:		//Direction Light
	{
		ComputeDirectionLight(material, light, normal, toeye, ambient, diffuse, spec);
		break;
	}
	case 2:		//Point Light
	{
		ComputePointLight(material, light, pos, normal, toeye, ambient, diffuse, spec);
		break;
	}
	case 3:		//Spot Light
	{
		ComputeSpotLight(material, light, pos, normal, toeye, ambient, diffuse, spec);
		break;
	}
	default:
	{
		ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	}
	}
}

#define MaxLightSize 8
struct Lights
{
	Light m_Content[8];
	unsigned int m_Size[4];
};

float4 GetColorByLights(Material material, Lights lights,float3 eyepos, float3 pos, float3 normal)
{
	float4 litcolor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	normal = normalize(normal);
	float3 toeye = normalize(eyepos - pos);

	for (unsigned int i = 0; i < lights.m_Size[0]; i++)
	{
		ComputeCommonLight(material, lights.m_Content[i], pos, normal, toeye, ambient, diffuse, specular);
		litcolor += ambient + diffuse + specular;
	}

	litcolor.a = material.m_Diffuse.a;

	return litcolor;
}

void GetColorByLightsEx(Material material, Lights lights, float3 eyepos, float3 pos, float3 normal,out float4 ambient,out float4 diffuse,out float4 specular)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 A = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 D = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 S = float4(0.0f, 0.0f, 0.0f, 0.0f);

	normal = normalize(normal);
	float3 toeye = normalize(eyepos - pos);

	for (unsigned int i = 0; i < lights.m_Size[0]; i++)
	{
		ComputeCommonLight(material, lights.m_Content[i], pos, normal, toeye, A, D, S);
		ambient += A;
		diffuse += D;
		specular += S;
	}
}