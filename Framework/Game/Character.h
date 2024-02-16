#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

#include "Utilities/RigidBody.h"

class Character : public GameObject
{
public:
	Character(Vector3 position, Vector3 size, float rotation);
	~Character();

	void Update();
	void Render();

	virtual void ControlState();
	virtual void AnimState();

	Vector3* GetMoveDir() { return &MoveDir; }

	BoundingBox* GetCollision() { return collision; }


	// 상태 관리
	BYTE Current_State;
	BYTE Old_InputState;

	BYTE GetCurrentState() { return Current_State; }

	float GetDir() { return dir; }
	void SetDir(float dir) { this->dir = dir; }

	Status& GetStatus() { return _status; }
	void SetStatusInfo();

	void SetInputState(BYTE change);

	void SetInputStateOn(BYTE change);
	void SetInputStateOff(BYTE change);
	
	bool CheckInputState(BYTE check1);
	bool CheckInputState(BYTE check1, BYTE check2);
	bool CheckInputState(BYTE check1, BYTE check2, BYTE check3);
	bool CheckInputState(BYTE check1, BYTE check2, BYTE check3, BYTE check4);

	void OnWeaponCollision(int start, int end, Vector3 position, Vector3 size);			// 애니메이션 프레임으로 콜리젼 조작
	void OnWeaponCollision(bool isbool, float Time, Vector3 position, Vector3 size);	// 조건 bool로 콜리젼 조작

	void SetTargetWeapon(BoundingBox* target);
	void CheckTargetWeapon();

	void DamageReaction(Attack _attack, float dir);

	virtual void DecreaseAccel();

protected:
	bool CheckState(BYTE check);


protected:
	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;

	class RigidBody* rigidbody = nullptr;

	BoundingBox* collision = nullptr;
	BoundingBox* weapon_col = nullptr;

	BoundingBox* TargetWeapon = nullptr;


protected:
	float dir = 1.f;
	float delta = 0.0f;

	float MoveSpeed;

	float AccelMove;
	float MaxAccel;

	float jumpSpeed;

	bool landGround;
	bool WallStart;

	Vector3 MoveDir;

	Vector3 weaponPos = {};
	Vector3 weaponSize = {};

	float CheckTime = 0.0f;
	bool isCheck = false;

protected:
	Vector3 Destination = {};
	Status _status;

protected:
	Attack _attack = NORMAL;
};