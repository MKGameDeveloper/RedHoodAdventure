#pragma once

class PlayerStatus : public SingletonBase<PlayerStatus>
{
public:
	friend class SingletonBase<PlayerStatus>;

public:
	void PlusSCount();
	void PlusSDamage();
	int GetsCount();
	float GetsDamage();

	void PlusECount();
	void PlusEDamage();
	int GeteCount();
	float GeteDamage();

	void SetUnlockJumpAttack();
	bool IsUnlockJumpAttack();

	void PlusMaxHp();
	void PlusCurrentHp(float heal);
	void SetHpDamaged(float damage);
	void SetHp(float set);
	float GetMaxHp();
	float GetCurrentHp();

	void PlusMaxStamina();
	void PlusCurrentStamina(float heal);
	void UseStamina(float use);
	float GetMaxStamina();
	float GetCurrentStamina();

	void PlusMaxArrowCount();
	void PlusCurrentArrow(int count);
	void UseArrow();
	void PlusBowDamge();
	int GetMaxArrowCount();
	int GetCurrentArrowCount();
	float GetBowDamage();

	void SetUnlockBowMode();
	bool IsUnlockBow();

	int GetSoulPoint();
	void PlusSoulPoint(int soul);
	void UseSoulPoint(int soul);



private:
	PlayerStatus();
	~PlayerStatus();


private:
	int sAttackCount = 2;
	float sAttackDamage = 310;

	int eAttackCount = 2;
	float eAttackDamage = 25;
	float JumpAttackUnlock = true;

	float MaxHp = 100;
	float CurrentHp = 100;

	float MaxStamina = 1000;
	float CurrentStamina = 1000;

	int MaxArrowCount = 10;
	int CurrentArrowCount = 5;
	float BowDamage = 10;
	bool BowUnlock = false;

	int SoulPoint = 10000;

};