#pragma once

#include "Game/Character.h"
#include "Game/Object/MonsterObject.h"

class Monster : public Character
{
public:

public:
	Monster(Vector3 position, Vector3 size, float rotation);
	~Monster();

	virtual void Init();
	virtual void OnActive();

	virtual void Update() {}
	virtual void Render() {}

	bool IsDie() { return isdie; }

protected:
	// 몬스터 행동 함수
	void DetectPlayer();
	void SetDestination();
	void CheckDestination();

	virtual void Col_Update();
	void Movement();


protected:
	float detectRange;
	float detectDistance;

	float attackRange;

	bool oldDoAttack;
	bool DoAttack;

	bool detected;
	bool olddetected = false;
	float detectedTime;

	float playerDir;

	float s_attack_cooldown;
	float s_cooltime;
	bool bSpecialAttack;

	float TimeDelay;
	float WalkDelay;
	float AttackDelay;

	bool isdie = false;

	bool isleftnull = false;
	bool isrightnull = false;

	bool isnullok = false;

	bool isside = false;
	float CheckDetectCoolTime = 0.f;

protected:
	/// /////////////////////////////////////////////////////
	// Attack

	// 몬스터는 최초 스폰 위치 근처에서만 이동한다!
	Vector3 StartPosition;

	Soul* soul = nullptr;
	float soulPoint = 0.f;
};


class Bringer : public Monster
{
public:

	typedef enum State
	{
		DEFAULT = 0,
		IDLE,
		RUN,
		ATTACK,
		CAST,
		DAMAGED,
		DIE,

	}State;

public:
	Bringer(Vector3 position, float rotation);
	~Bringer();

	virtual void ControlState() override;
	virtual void AnimState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

private:
	// 몬스터 행동 함수
	virtual void Col_Update() override;

	void CreateSpell();

	void Run();
	void Smash();
	void Damaged();
	void Cast();


private:
	vector<class BringerSpell*> bs;

private:
	State _State = IDLE;
	State prevState = IDLE;

private:
	//MonsterStatus
	int spell_stack = 0;
};



class MudGuard : public Monster
{
public:

	typedef enum State
	{
		DEFAULT = 0,
		IDLE,
		RUN,
		ATTACK,
		SATTACK,
		DAMAGED,
		DIE,

	}State;

public:
	MudGuard(Vector3 position, float rotation);
	~MudGuard();

	virtual void ControlState() override;
	virtual void AnimState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

private:
	// 몬스터 행동 함수
	virtual void Col_Update() override;

	void Run();
	void Attack();
	void S_Attack();
	void Damaged();

private:
	State _State = IDLE;
	State prevState = IDLE;

private:
	//MonsterStatus
	int satk_stack = 0;

};

class BombDroid : public Monster
{
public:

	typedef enum State
	{
		DEFAULT = 0,
		IDLE,
		RUN,
		ATTACK,
		DIE,

	}State;

public:
	BombDroid(Vector3 position, float rotation);
	~BombDroid();

	virtual void ControlState() override;
	virtual void AnimState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

private:
	// 몬스터 행동 함수
	virtual void Col_Update() override;

	void Run();
	void Attack();

private:
	State _State = IDLE;
	State prevState = IDLE;

private:
	//MonsterStatus
	int satk_stack = 0;

};


class ShadowMage : public Monster
{
public:

	typedef enum State
	{
		DEFAULT = 0,
		IDLE,
		RUN,
		ATTACK,
		CAST,
		DAMAGED,
		DIE,

	}State;

public:
	ShadowMage(Vector3 position, float rotation);
	~ShadowMage();

	virtual void ControlState() override;
	virtual void AnimState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

private:
	// 몬스터 행동 함수
	virtual void Col_Update() override;

	void CreateSpell();

	void Run();
	void Smash();
	void Damaged();
	void Cast();


private:
	vector<class ShadowMageSpell*> ss;

private:
	State _State = IDLE;
	State prevState = IDLE;

private:
	//MonsterStatus
	int spell_stack = 0;
};


class ShadowStalker: public Monster
{
public:

	typedef enum State
	{
		DEFAULT = 0,
		IDLE,
		RUN,
		AGGROIDLE,
		AGGRO,
		NOT_AGGRO,
		AGGROWALK,
		ATTACK,
		SATTACK,
		DAMAGED,
		DIE,

	}State;

public:
	ShadowStalker(Vector3 position, float rotation);
	~ShadowStalker();

	virtual void ControlState() override;
	virtual void AnimState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

private:
	// 몬스터 행동 함수
	virtual void Col_Update() override;

	void Run();

	void Aggro();
	void DeAggro();

	void AggroRun();
	void Attack();
	void S_Attack();

	void Damaged();

private:
	State _State = IDLE;
	State prevState = IDLE;

private:
	//MonsterStatus
	int satk_stack = 0;

	float AggroSpeed = 0;

};