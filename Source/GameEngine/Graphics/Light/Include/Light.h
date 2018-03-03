/*
Copyright 2018 creatorlxd

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
#pragma once
#include <DirectXMath.h>

namespace SpaceGameEngine
{
	enum LightType :uint32_t
	{
		UnkownLight = 0,
		DirectionLight = 1,
		PointLight = 2,
		SpotLight = 3
	};

	/*
	基本的光源信息，涵盖了基本的三种光源（平行光、点光源、聚光灯）的信息
	*/
	struct Light
	{
		Light();

		XMFLOAT4 m_Ambient;			//环境光
		XMFLOAT4 m_Diffuse;			//漫反射光
		XMFLOAT4 m_Specular;		//镜面反射光

		XMFLOAT3 m_Position;
		float m_Range;

		XMFLOAT3 m_Direction;		//方向光和聚光灯所特有的光的方向
		float m_SpotLightOption;	//聚光灯的参数

		XMFLOAT3 m_LightOption;		//光源的基本的三个参数:a0,a1,a2-->a0+a1*d+a2*d^2
		LightType m_Type;			//光源的类型
	};
}