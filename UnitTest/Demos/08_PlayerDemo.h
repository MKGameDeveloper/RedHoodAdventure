#pragma once

#include "Character/Player.h"

#include "UI/HUD.h"

#include "Map/Map_Arr.h"

class PlayerDemo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	BoundingBox* leftwall = nullptr;
	BoundingBox* rightwall = nullptr;


private:
	class HUD* hud = nullptr;
	class Player* player = nullptr;

	//class ShadowStalker* s1 = nullptr;
	
	void Map_Push(MapManager* m);
	vector<MapManager*> maps;

	void SetMap(int num);

	void ChangeMap();

	int lastTown = 0;
	int map_num = 0;

	float CameraSize = 1.f;
};