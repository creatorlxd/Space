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