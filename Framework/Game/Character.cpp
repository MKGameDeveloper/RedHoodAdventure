#include "Framework.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size, float rotation)
	: GameObject(position, size, rotation, DOWN_CENTER)
{ 
	animRect = new AnimationRect(position, size, rotation, pivot);
	animator = new Animator();

	dir = 1.f;
	MoveDir = { 0,0,0 };

	MoveSpeed = 2.f;

	AccelMove = 0.f;
	MaxAccel = 3.f;

	jumpSpeed = 10.f;

	Current_State = MaxState;
	Old_InputState = None;

	landGround = false;
	WallStart = false;

	

}

Character::~Character()
{
	SAFE_DELETE(animator);
	SAFE_DELETE(animRect);
}

void Character::Update()
{
}

void Character::Render()
{
}

void Character::ControlState()
{
}

void Character::AnimState()
{
}


void Character::SetStatusInfo()
{
	_status.currentAtk = _status.Atk + _status.plusAtk;

	_status.currentDef = _status.Def + _status.plusDef;

	_status.MaxHp = _status.Hp + _status.plusHp;

	_status.MaxStamina = _status.Stamina + _status.plusStamina;
}

void Character::SetInputState(BYTE change)
{
	Old_InputState = Current_State;
	Current_State = change;
}

void Character::SetInputStateOn(BYTE change)
{
	Old_InputState = Current_State;
	Current_State = Current_State | change;
}
void Character::SetInputStateOff(BYTE change)
{
	BYTE check = MaxState ^ change;

	Old_InputState = Current_State;
	Current_State &= check;

}

///////////////

bool Character::CheckState(BYTE check)
{
	return  (Current_State & check) == check;
}

void Character::SetTargetWeapon(BoundingBox* target)
{
	if (TargetWeapon != nullptr)
		return;

	TargetWeapon = target;

}

void Character::CheckTargetWeapon()
{
	if (TargetWeapon == nullptr)
		return;

	// �ش� ��ü�� ������ ���� �ݸ����� ��Ȱ��ȭ�� �ɶ������� �ν����� ���ϰ� �Ͽ� 1ȸ�� �ǰݴ��� �� �ְ� �ϱ����� �ڵ�
	// Ÿ�� ������ nullptr�� �ƴ϶�� ���̻� �ش� Ÿ���� ���� �������� ���� �ʵ��� ������ ����
	if (TargetWeapon->GetIsActive() == false)
		TargetWeapon = nullptr;

}

void Character::DamageReaction(Attack _attack, float dir)
{
	this->dir = dir * -1.f;

	switch (_attack)
	{
	case NORMAL:
		break;
	case KNOCKBACK:
		AccelMove = dir * 5.f;
		break;
	case RISE_UP:
		MoveDir.y = jumpSpeed * 0.7f;
		AccelMove = dir * 7.f;
		break;
	case GRAB:
		AccelMove = dir * 6.f * -1.f;
		break;
	case SUPER_KNOCKBACK:
		AccelMove = dir * 10.f;
		break;
	default:
		break;
	}
}

void Character::DecreaseAccel()
{

	if (AccelMove > 0.f)
	{
		AccelMove -= 0.5f;
	}
	else if (AccelMove < 0.f)
	{
		AccelMove += 0.5f;
	}

	if (AccelMove >= -0.5f && AccelMove <= 0.5f)
	{
		AccelMove = 0.f;
	}
}



bool Character::CheckInputState(BYTE check1)
{
	return CheckState(check1);
}

bool Character::CheckInputState(BYTE check1, BYTE check2)
{
	return CheckState(check1 | check2);
}

bool Character::CheckInputState(BYTE check1, BYTE check2, BYTE check3)
{
	return CheckState(check1 | check2 | check3);
}

bool Character::CheckInputState(BYTE check1, BYTE check2, BYTE check3, BYTE check4)
{
	return CheckState(check1 | check2 | check3 | check4);
}

// ���� �浹ü ����

void Character::OnWeaponCollision(int start, int end, Vector3 position, Vector3 size)
{
	if (animator->CheckFrameIndex(start))
	{
		weaponPos = position;
		weaponSize = size;
		this->weapon_col->SetActive(true);
	}
	if (animator->CheckFrameIndex(end))
	{
		weapon_col->SetActive(false);
	}
}

void Character::OnWeaponCollision(bool isbool, float Time, Vector3 position, Vector3 size)
{
	if (isbool)
	{
		isCheck = true;
		weaponPos = position;
		weaponSize = size;
		weapon_col->SetActive(true);
	}
	if (CheckTime > Time && animator->IsEnd())
	{
		isCheck = false;
		weapon_col->SetActive(false);
	}
}


