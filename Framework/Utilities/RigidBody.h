#pragma once

#include "Game/Character.h"
#include "Game/Map/FootHolder/FootHolder.h"

class RigidBody
{
public:
	friend class Character;


public:

	RigidBody(Character& character);
	RigidBody(FootHolder& floor);
	~RigidBody();

	void Update();
	void Render();

	void Movement();
	void FloorMovement();

	void UpdateCollision();
	void CheckCollision();

	void CheckUpCol();
	void CheckDownCol();
	void CheckLeftRightCol();
	void ChangeCol();

	void CheckBool();
	
	void UpdateFloorCollision();
	void CheckFloorCollision();

	void SetGrav(float gravPow);
	bool CheckState(BYTE check);
	bool CheckSide() { return isside; }

	bool IsLeftDownNull() { return isleftnull; }
	bool IsRightDownNull() { return isrightnull; }

private:

	BoundingBox* CheckDown = nullptr;
	BoundingBox* CheckUp = nullptr;
	BoundingBox* CheckLeft = nullptr;
	BoundingBox* CheckRight = nullptr;

	BoundingBox* CheckLeftDown = nullptr;
	BoundingBox* CheckRightDown = nullptr;

	bool isground;
	bool iswall;
	bool isCollisionFloor;

	Character* character;
	FootHolder* floor;

	bool IsCharacter;

	float FSpeed;
	float FYSpeed;

	int count;

private:
	bool isup;
	bool isdown;
	bool isleft;
	bool isright;

	bool isleftnull;
	bool isrightnull;

	bool isside;

	Vector3 grav;	// 점프 중력
	Vector3 FinalMove; // 최종 움직임

	
};