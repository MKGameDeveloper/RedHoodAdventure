#include "Framework.h"
#include "PlayerStatus.h"

void PlayerStatus::PlusSCount()
{
	sAttackCount++; 
}

void PlayerStatus::PlusSDamage()
{
	sAttackDamage += 5;
}

int PlayerStatus::GetsCount()
{
	return sAttackCount;
}

float PlayerStatus::GetsDamage()
{
	return sAttackDamage;
}

void PlayerStatus::PlusECount()
{
	eAttackCount++;
}

void PlayerStatus::PlusEDamage()
{
	eAttackDamage += 10;
}

int PlayerStatus::GeteCount()
{
	return eAttackCount;
}

float PlayerStatus::GeteDamage()
{
	return eAttackDamage;
}

void PlayerStatus::SetUnlockJumpAttack()
{
	JumpAttackUnlock = true;
}

bool PlayerStatus::IsUnlockJumpAttack()
{
	return JumpAttackUnlock;
}

void PlayerStatus::PlusMaxHp()
{
	MaxHp += 100;
}

void PlayerStatus::PlusCurrentHp(float heal)
{
	if (CurrentHp + heal <= MaxHp) 
		CurrentHp += heal; 
	else 
		CurrentHp = MaxHp; 
}

void PlayerStatus::SetHpDamaged(float damage)
{
	CurrentHp -= damage;
}

void PlayerStatus::SetHp(float set)
{
	CurrentHp = set;
}

float PlayerStatus::GetMaxHp()
{
	return MaxHp;
}

float PlayerStatus::GetCurrentHp()
{
	return CurrentHp;
}

void PlayerStatus::PlusMaxStamina()
{
	MaxStamina += 500;
}

void PlayerStatus::PlusCurrentStamina(float heal)
{
	if (CurrentStamina + heal <= MaxStamina) 
		CurrentStamina += heal; 
	else
		CurrentStamina = MaxStamina;
}

void PlayerStatus::UseStamina(float use)
{
	CurrentStamina -= use;
}

float PlayerStatus::GetMaxStamina()
{
	return MaxStamina;
}

float PlayerStatus::GetCurrentStamina()
{
	return CurrentStamina;
}

void PlayerStatus::PlusMaxArrowCount()
{
	MaxArrowCount += 2;
}

void PlayerStatus::PlusCurrentArrow(int count)
{
	if (CurrentArrowCount + count <= MaxArrowCount) 
		CurrentArrowCount += count; 
	else 
		CurrentArrowCount = MaxArrowCount;
}

void PlayerStatus::UseArrow()
{
	CurrentArrowCount--;
}

void PlayerStatus::PlusBowDamge()
{
	BowDamage += 5;
}

int PlayerStatus::GetMaxArrowCount()
{
	return MaxArrowCount;
}

int PlayerStatus::GetCurrentArrowCount()
{
	return CurrentArrowCount;
}

float PlayerStatus::GetBowDamage()
{
	return BowDamage;
}

void PlayerStatus::SetUnlockBowMode()
{
	BowUnlock = true;
}

bool PlayerStatus::IsUnlockBow()
{
	return BowUnlock;
}

int PlayerStatus::GetSoulPoint()
{
	return SoulPoint;
}

void PlayerStatus::PlusSoulPoint(int soul)
{
	SoulPoint += soul;
}

void PlayerStatus::UseSoulPoint(int soul)
{
	SoulPoint -= soul;
}

PlayerStatus::PlayerStatus()
{
}

PlayerStatus::~PlayerStatus()
{

}

