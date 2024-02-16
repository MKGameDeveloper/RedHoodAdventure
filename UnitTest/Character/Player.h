#pragma once

#include "Game/Object/Arrow.h"
#include "Game/Character.h"


class Player : public Character
{
public:

	typedef enum State
	{
		DEFAULT = 0,
		IDLE,
		RUN,
		TURN,
		UP,
		DOWN,
		LAND,
		WALL,
		JUMPATK,
		SLIDE,
		BOW,
		SSA,
		EA,
		DAMAGED,
		DIE,
		BACKJUMP,

	}State;


public:
	Player(Vector3 position, Vector3 size, float rotation);
	~Player();

	virtual void ControlState() override;
	virtual void AnimState() override;

	void Update();
	void Render();
	void GUI();


private:
	// 캐릭터 행동 함수
	void Movement();
	virtual void DecreaseAccel() override;

	void CreateArrow(float dir);
	void CalculateComboTime();

	void Run();
	void Dash();

	void WallJump();

	void Jumping();
	void Down();
	void Land();

	void Wall_Grab();

	void BackJump();

	void S_Attack();
	void E_Attack();
	void JumpAttack();

	void Bow();

	void Slide();

	void Damaged();
	void IsAttack();

	void Die();

	void RecoveryStamina();


private:
	vector<class Arrow*> as;

private:
	/// /////////////////////////////////////////////////////
	// Attack

	bool isAttack = false;
	float AttackDelay = 0.f;

	float SSAcomboTime = .0f;
	int SSA_Combo = 1;
	bool isSSA = false;

	float EAcomboTime = .0f;
	int EA_Combo = 1;
	bool isEA = false;

	State _State = IDLE;

	Vector3 spawnPos = { 40, 350, 0 };

	string s_state = "idle";

	bool isDamaged = false;
	float InvncTime = 0.f;
	int damagemode = 1;
};