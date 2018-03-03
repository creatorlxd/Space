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
	�����Ĺ�Դ��Ϣ�������˻��������ֹ�Դ��ƽ�й⡢���Դ���۹�ƣ�����Ϣ
	*/
	struct Light
	{
		Light();

		XMFLOAT4 m_Ambient;			//������
		XMFLOAT4 m_Diffuse;			//�������
		XMFLOAT4 m_Specular;		//���淴���

		XMFLOAT3 m_Position;
		float m_Range;

		XMFLOAT3 m_Direction;		//�����;۹�������еĹ�ķ���
		float m_SpotLightOption;	//�۹�ƵĲ���

		XMFLOAT3 m_LightOption;		//��Դ�Ļ�������������:a0,a1,a2-->a0+a1*d+a2*d^2
		LightType m_Type;			//��Դ������
	};
}