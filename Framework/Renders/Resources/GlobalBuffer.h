// WVP 행렬 정의

#pragma once
#include "Framework.h"

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		D3DXMatrixIdentity(&data.world);
	}

	void SetWorld(Matrix world)
	{
		D3DXMatrixTranspose(&data.world, &world);
	}

	struct Data
	{
		Matrix world;
	};

private:

	Data data;

};

class VPBuffer : public ShaderBuffer
{
public:
	VPBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		// 행렬 초기화
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.projection);
	}

	void SetView(Matrix view)
	{
		// 행렬 전치
		D3DXMatrixTranspose(&data.view, &view);
	}

	void SetProj(Matrix projection)
	{
		D3DXMatrixTranspose(&data.projection, &projection);
	}

	struct Data
	{
		Matrix view;
		Matrix projection;
	};

private:
	Data data;
};

/*
W V P : World, View, Projection

1. World : 월드
	- 모델의 정점을 지역 좌표계에서 세계 좌표계로 변환하는 것을 의미
	- 모델의 위치, 화전 및 크기를 조정

2. View : 뷰
	- 카메라의 위치, 방향 및 시야를 나타내는 행렬
	- 세계 좌표계에서 카메라가 바라보는 방향을 나타냄
	- 카메라의 위치와 방향을 변경

3. Projection : 투영
	- 3D 공간을 2D 스크린 좌표로 변환하는 것을 의미
	- 시야각, 종횡비, 크리핑 평면(Clipping Planes)등을 고려하여 수행


*/