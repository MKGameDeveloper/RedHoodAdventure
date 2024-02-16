#pragma once

#include "Framework.h"

#include "Game/Map/FootHolder/FootHolder.h"
#include "Game/Map/FootHolder/Floor.h"
#include "Game/Map/FootHolder/BackFloor.h"
#include "Game/Map/FootHolder/MoveFloor.h"

#include "Game/Map/FootHolder/ObjectManage.h"

#include "Game/Monster/Monster.h"

#include "Game/Character.h"

#include "Geomatries/Tile/Tile.h"
#include "Geomatries/Tile/TileMap.h"
#include "Geomatries/Tile/TileSet.h"

class MapManager
{
public:
	enum Active
	{
		OFF = 0,
		ON,
	};

public:
	virtual void Destroy();	// �Ҹ��� ��ü

	void OnIsActive(); // Ȱ��ȭ �� 1ȸ ȣ��

	Vector2 GetMapSize() { return MapSize; }

	virtual void Update();

	virtual void Render();
	void PostRender();	// ��ó���� �ʿ��� �ڵ带 ó��

	virtual void BackGroundSight();

	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void PUSH_Floor(vector<FootHolder*>& fls, FootHolder* f) { fls.push_back(f); }

	void CreateObject(Tile::ObjectType type, Vector3 position, int num);

	void PUSH_Monster(Monster* m) { ms.push_back(m); }

	void LoadMap(string path);

	void SetIsActive(Active isActive)
	{
		_activeState[0] = _activeState[1];
		_activeState[1] = isActive; 
	}

	Vector3 GetFirstPoint() { return FirstPoint; }
	Vector3 GetSecondPoint() { return SecondPoint; }

	bool IsTown() { return istown; }

	bool NextMap() { return isNext == true; }

	void Init();
	void MapOn();

protected:
	MapManager();

	uint width, height, spacing;

	vector<VertexTile> vertices;
	VertexBuffer* vb = nullptr;
	D3D11_MAPPED_SUBRESOURCE subResource;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world = Values::Identity;
	WorldBuffer* wb = nullptr;

	IndexNumBuffer* inb = nullptr;

protected:
	vector<vector<FootHolder*>> fs;

	Portal* portal = nullptr;

	vector<Monster*> ms;

	vector<class TextureRect*> map;

protected:
	Active _activeState[2] = {OFF, ON};

	

	Vector2 MapSize; // ��ũ��

	Vector3 FirstPoint;	// 1�� ��ȯ ��ġ
	Vector3 SecondPoint; // 2�� ��ȯ ��ġ

	string MusicName;

	bool isNext = false;

	bool istown = false;

	bool allmonsterdie = false;

	float deltaTime = 0.f;

	float NoticeTime = 1.f;

	bool isClear = false;
};