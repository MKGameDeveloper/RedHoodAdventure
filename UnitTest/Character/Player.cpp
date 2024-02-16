#include "stdafx.h"
#include "Player.h"


Player::Player(Vector3 position, Vector3 size, float rotation)
	:Character(position, size, rotation)
{

	// Character Status
	{
		MoveSpeed = 4.f;
		jumpSpeed = 18.2f;
	}

	// Animation
	{
		float Max_Y = 18.f;

		Texture2D* srcTex = new Texture2D(TexturePath + L"RedHood(74_48).png");
		Texture2D* srcTex2 = new Texture2D(TexturePath + L"RedHood(reverse).png");

		Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

		Vector2 idle_f_s = Values::ZeroVec2;
		Vector2 idle_f_e = Vector2(texSize.x * (18.f / 24.f), texSize.y * (1.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 run_f_s = Vector2(0.f, texSize.y * (1.f / Max_Y));
		Vector2 run_f_e = Vector2(texSize.x, texSize.y * (2.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 bow_f_s = Vector2(0.f, texSize.y * (2.f / Max_Y));
		Vector2 bow_f_e = Vector2(texSize.x * (9.f / 24.f), texSize.y * (3.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 up_f_s = Vector2(0.f, texSize.y * (3.f / Max_Y));
		Vector2 up_f_e = Vector2(texSize.x * (7.f / 24.f), texSize.y * (4.f / Max_Y));

		Vector2 down_f_s = Vector2(0.f, texSize.y * (4.f / Max_Y));
		Vector2 down_f_e = Vector2(texSize.x * (7.f / 24.f), texSize.y * (5.f / Max_Y));

		Vector2 land_f_s = Vector2(0.f, texSize.y * (5.f / Max_Y));
		Vector2 land_f_e = Vector2(texSize.x * (3.f / 24.f), texSize.y * (6.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 slide_f_s = Vector2(0.f, texSize.y * (6.f / Max_Y));
		Vector2 slide_f_e = Vector2(texSize.x * (4.f / 24.f), texSize.y * (7.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 ss1_f_s = Vector2(0.f, texSize.y * (7.f / Max_Y));
		Vector2 ss1_f_e = Vector2(texSize.x * (7.f / 24.f), texSize.y * (8.f / Max_Y));

		Vector2 ss2_f_s = Vector2(0.f, texSize.y * (8.f / Max_Y));
		Vector2 ss2_f_e = Vector2(texSize.x * (6.f / 24.f), texSize.y * (9.f / Max_Y));

		Vector2 ss3_f_s = Vector2(0.f, texSize.y * (9.f / Max_Y));
		Vector2 ss3_f_e = Vector2(texSize.x * (10.f / 24.f), texSize.y * (10.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 e1_f_s = Vector2(0.f, texSize.y * (10.f / Max_Y));
		Vector2 e1_f_e = Vector2(texSize.x * (10.f / 24.f), texSize.y * (11.f / Max_Y));

		Vector2 e2_f_s = Vector2(0.f, texSize.y * (11.f / Max_Y));
		Vector2 e2_f_e = Vector2(texSize.x * (13.f / 24.f), texSize.y * (12.f / Max_Y));

		Vector2 e3_f_s = Vector2(0.f, texSize.y * (12.f / Max_Y));
		Vector2 e3_f_e = Vector2(texSize.x * (17.f / 24.f), texSize.y * (13.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 damaged_f_s = Vector2(0.f, texSize.y * (13.f / Max_Y));
		Vector2 damaged_f_e = Vector2(texSize.x * (6.f / 24.f), texSize.y * (14.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 landAtk_f_s = Vector2(0.f, texSize.y * (12.f / Max_Y));
		Vector2 landAtk_f_e = Vector2(texSize.x * (7.f / 24.f), texSize.y * (13.f / Max_Y));

		Vector2 landAtk_r_s = Vector2(texSize.x * (10.f / 24.f), texSize.y * (12.f / Max_Y));
		Vector2 landAtk_r_e = Vector2(texSize.x * (17.f / 24.f), texSize.y * (13.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 die_f_s = Vector2(0.f, texSize.y * (14.f / Max_Y));
		Vector2 die_f_e = Vector2(texSize.x * (7.f / 24.f), texSize.y * (15.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 backjump_f_s = Vector2(texSize.x * (6.f / 24.f), texSize.y * (1.f / Max_Y));
		Vector2 backjump_f_e = Vector2(texSize.x * (12.f / 24.f), texSize.y * (2.f / Max_Y));

		Vector2 backjump_r_s = Vector2(texSize.x * (12.f / 24.f), texSize.y * (1.f / Max_Y));
		Vector2 backjump_r_e = Vector2(texSize.x * (18.f / 24.f), texSize.y * (2.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 damaged2_f_s = Vector2(0.f, texSize.y * (15.f / Max_Y));
		Vector2 damaged2_f_e = Vector2(texSize.x * (5.f / 24.f), texSize.y * (16.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 wallgrab_f_s = Vector2(0.f, texSize.y * (16.f / Max_Y));
		Vector2 wallgrab_f_e = Vector2(texSize.x * (4.f / 24.f), texSize.y * (17.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 turned_f_s = Vector2(0.f, texSize.y * (17.f / Max_Y));
		Vector2 turned_f_e = Vector2(texSize.x * (5.f / 24.f), texSize.y * (18.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		// 24, 14

		AnimationClip* Idle_f = new AnimationClip(L"idle_f", srcTex, 18, Values::ZeroVec2, idle_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_f = new AnimationClip(L"run_f", srcTex, 24, run_f_s, run_f_e, true, 1.f / 15.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* bow_f = new AnimationClip(L"bow_f", srcTex, 9, bow_f_s, bow_f_e, true, 1.f / 15.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* up_f = new AnimationClip(L"up_f", srcTex, 7, up_f_s, up_f_e, true, 1.f / 6.f, false);
		AnimationClip* down_f = new AnimationClip(L"down_f", srcTex, 7, down_f_s, down_f_e, true, 1.f / 6.f, false);
		AnimationClip* land_f = new AnimationClip(L"land_f", srcTex, 3, land_f_s, land_f_e, true, 1.f / 6.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* slide_f = new AnimationClip(L"slide_f", srcTex, 4, slide_f_s, slide_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* ss1_f = new AnimationClip(L"ss1_f", srcTex, 7, ss1_f_s, ss1_f_e, true, 1.f / 9.f, false);
		AnimationClip* ss2_f = new AnimationClip(L"ss2_f", srcTex, 6, ss2_f_s, ss2_f_e, true, 1.f / 9.f, false);
		AnimationClip* ss3_f = new AnimationClip(L"ss3_f", srcTex, 10, ss3_f_s, ss3_f_e, true, 1.f / 9.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* e1_f = new AnimationClip(L"e1_f", srcTex, 10, e1_f_s, e1_f_e, true, 1.f / 10.f, false);
		AnimationClip* e2_f = new AnimationClip(L"e2_f", srcTex, 13, e2_f_s, e2_f_e, true, 1.f / 10.f, false);
		AnimationClip* e3_f = new AnimationClip(L"e3_f", srcTex, 17, e3_f_s, e3_f_e, true, 1.f / 10.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged_f = new AnimationClip(L"damaged_f", srcTex, 6, damaged_f_s, damaged_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* landAtk_f = new AnimationClip(L"landAtk_f", srcTex, 7, landAtk_f_s, landAtk_f_e, true, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_f = new AnimationClip(L"die_f", srcTex, 7, die_f_s, die_f_e, true, 1.f / 8.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* backjump_f = new AnimationClip(L"backjump_f", srcTex, 6, backjump_f_s, backjump_f_e, false, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged2_f = new AnimationClip(L"damaged2_f", srcTex, 5, damaged2_f_s, damaged2_f_e, true, 1.f / 6.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* wallgrab_f = new AnimationClip(L"wallgrab_f", srcTex, 4, wallgrab_f_s, wallgrab_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* turned_f = new AnimationClip(L"turned_f", srcTex, 5, turned_f_s, turned_f_e, true, 1.f / 15.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		animator->AddAnimClip(Idle_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(bow_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(up_f);
		animator->AddAnimClip(down_f);
		animator->AddAnimClip(land_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(slide_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(ss1_f);
		animator->AddAnimClip(ss2_f);
		animator->AddAnimClip(ss3_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(e1_f);
		animator->AddAnimClip(e2_f);
		animator->AddAnimClip(e3_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(landAtk_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(backjump_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged2_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(wallgrab_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(turned_f);


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//reverse
		AnimationClip* Idle_r = new AnimationClip(L"idle_r", srcTex2, 18, Values::ZeroVec2, idle_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_r = new AnimationClip(L"run_r", srcTex2, 24, run_f_s, run_f_e, false, 1.f / 15.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* bow_r = new AnimationClip(L"bow_r", srcTex2, 9, bow_f_s, bow_f_e, false, 1.f / 15.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* up_r = new AnimationClip(L"up_r", srcTex2, 7, up_f_s, up_f_e, false, 1.f / 6.f, false);
		AnimationClip* down_r = new AnimationClip(L"down_r", srcTex2, 7, down_f_s, down_f_e, false, 1.f / 6.f, false);
		AnimationClip* land_r = new AnimationClip(L"land_r", srcTex2, 3, land_f_s, land_f_e, false, 1.f / 6.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* slide_r = new AnimationClip(L"slide_r", srcTex2, 4, slide_f_s, slide_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* ss1_r = new AnimationClip(L"ss1_r", srcTex2, 7, ss1_f_s, ss1_f_e, false, 1.f / 9.f, false);
		AnimationClip* ss2_r = new AnimationClip(L"ss2_r", srcTex2, 6, ss2_f_s, ss2_f_e, false, 1.f / 9.f, false);
		AnimationClip* ss3_r = new AnimationClip(L"ss3_r", srcTex2, 10, ss3_f_s, ss3_f_e, false, 1.f / 9.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* e1_r = new AnimationClip(L"e1_r", srcTex2, 10, e1_f_s, e1_f_e, false, 1.f / 10.f, false);
		AnimationClip* e2_r = new AnimationClip(L"e2_r", srcTex2, 13, e2_f_s, e2_f_e, false, 1.f / 10.f, false);
		AnimationClip* e3_r = new AnimationClip(L"e3_r", srcTex2, 17, e3_f_s, e3_f_e, false, 1.f / 10.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged_r = new AnimationClip(L"damaged_r", srcTex2, 6, damaged_f_s, damaged_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* landAtk_r = new AnimationClip(L"landAtk_r", srcTex2, 7, landAtk_r_s, landAtk_r_e, false, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_r = new AnimationClip(L"die_r", srcTex2, 7, die_f_s, die_f_e, false, 1.f / 8.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* backjump_r = new AnimationClip(L"backjump_r", srcTex2, 6, backjump_r_s, backjump_r_e, true, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged2_r = new AnimationClip(L"damaged2_r", srcTex2, 5, damaged2_f_s, damaged2_f_e, false, 1.f / 6.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* wallgrab_r = new AnimationClip(L"wallgrab_r", srcTex2, 4, wallgrab_f_s, wallgrab_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* turned_r = new AnimationClip(L"turned_r", srcTex2, 5, turned_f_s, turned_f_e, false, 1.f / 15.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		animator->AddAnimClip(Idle_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(bow_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(up_r);
		animator->AddAnimClip(down_r);
		animator->AddAnimClip(land_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(slide_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(ss1_r);
		animator->AddAnimClip(ss2_r);
		animator->AddAnimClip(ss3_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(e1_r);
		animator->AddAnimClip(e2_r);
		animator->AddAnimClip(e3_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(landAtk_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(backjump_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged2_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(wallgrab_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(turned_r);

		animator->SetCurrentAnimClip(L"idle_f");

		animRect->SetAnimator(animator);

		rigidbody = new RigidBody(*this);


		SAFE_DELETE(srcTex);
		SAFE_DELETE(srcTex2);

	}

	// Collision
	{
		collision = new BoundingBox(BoundingBox::Player);
		collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

		weapon_col = new BoundingBox(BoundingBox::Weapon);
		weapon_col->Init(Color(0, 1, 0, 0.3f), BoundingBox::DOWN_CENTER);
		weapon_col->SetActive(false);
	}

}

Player::~Player()
{
	for (Arrow* a : as)
	{
		SAFE_DELETE(a);
	}
	SAFE_DELETE(weapon_col);
	SAFE_DELETE(collision);
	SAFE_DELETE(rigidbody);
}

void Player::ControlState()
{
	// 움직이고 있는지 off
	// 움직일수 있는지 off
	// 입력할수 있는지 초기화 x
	SetInputStateOff(IsMove | bInput | bMove);

	Damaged();

	// 현재 상태에 따른 입력값을 받아와서 상태를 변경
	switch (_State)
	{
	case Player::IDLE:
		SetInputStateOn(bMove | bInput);

		weapon_col->SetActive(false);

		Run();

		Jumping();
		Down();
		Land();

		BackJump();

		S_Attack();
		E_Attack();
		Bow();

		Slide();
		Damaged();
		Die();

		break;
	case Player::RUN:
		SetInputStateOn(bMove | bInput | IsMove);

		Run();
		Dash();

		Jumping();
		Down();

		BackJump();

		S_Attack();
		E_Attack();
		Bow();

		Slide();
		Die();

		break;
	case Player::TURN:
		SetInputStateOn(IsMove | bMove);

		Run();

		break;
	case Player::UP:
		SetInputStateOn(IsMove | bMove);

		Run();

		Wall_Grab();

		Bow();
		Down();

		break;
	case Player::DOWN:
		SetInputStateOn(IsMove | bMove);
		weapon_col->SetActive(false);

		Run();

		Wall_Grab();

		Bow();

		Land();
		JumpAttack();

		break;
	case Player::LAND:

		break;
	case Player::WALL:
		SetInputStateOn(bMove);

		JumpAttack();
		Wall_Grab();
		WallJump();

		Run();

		break;
	case Player::JUMPATK:

		break;
	case Player::SLIDE:
		Slide();
		Land();
		S_Attack();

		break;
	case Player::BOW:
		//Land();

		break;
	case Player::SSA:
		Down();

		break;
	case Player::EA:


		break;
	case Player::DAMAGED:
		weapon_col->SetActive(false);


		break;
	case Player::DIE:
		weapon_col->SetActive(false);

		break;
	case Player::BACKJUMP:
		Land();

		break;

	case Player::DEFAULT:
		_State = IDLE;

	}


	AnimState();

}

void Player::AnimState()
{

	DecreaseAccel();

	switch (_State)
	{
	case Player::IDLE:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"idle_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"idle_f");

		break;

	case Player::RUN:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"run_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"run_f");

		break;

	case Player::TURN:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"turned_f");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"turned_r");

		if (AccelMove == 0.0f || animator->IsEnd())
		{
			_State = RUN;
		}

		break;

	case Player::UP:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"up_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"up_f");

		break;

	case Player::DOWN:
		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"down_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"down_f");

		break;

	case Player::LAND:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"land_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"land_f");

		if (animator->IsEnd())
		{
			_State = IDLE;
		}

		break;

	case Player::WALL:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"wallgrab_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"wallgrab_f");

		break;

	case Player::JUMPATK:

		MoveDir.y -= 2.f;

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"landAtk_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"landAtk_f");

		if (landGround)
			Sounds::Get()->Play("e3", 0.5f);

		weapon_col->SetDir(dir);
		weapon_col->SetAtkType(RISE_UP);

		if (!CheckInputState(IsGround))
		{
			weapon_col->SetDamage(_status.currentAtk * 1.2f);

			OnWeaponCollision(2, 5, { dir * 40.f, 0.f, 0 }, { size.x / 2.f, size.y / 4.f, 1.f });
		}
		else
		{
			weapon_col->SetDamage(_status.currentAtk * 1.4f);

			OnWeaponCollision(landGround, 0.2f, { dir * 40.f, 0.f, 0 }, { size.x * 1.2f, size.y / 4.f, 1.f });
		}

		if (CheckInputState(IsGround) && animator->IsEnd())
		{
			_State = IDLE;
		}

		break;

	case Player::SLIDE:

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"slide_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"slide_f");
		}


		break;

	case Player::BOW:

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"bow_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"bow_f");
		}
		if (animator->CheckStartFrame(6))
		{
			if (PlayerStatus::Get()->GetCurrentArrowCount() > 0)
			{
				PlayerStatus::Get()->UseArrow();
				CreateArrow(dir);
				AccelMove = 8.f * dir * (-1.f);
				Sounds::Get()->Play("arrow", 0.5f);
			}
			else
			{

			}
			
		}

		if (animator->IsEnd() && AccelMove == 0.f)
		{
			_State = IDLE;
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"idle_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"idle_f");
			}
		}
		break;

	case Player::SSA:
		if (SSA_Combo == 1)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"ss1_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"ss1_f");
			}
			if (animator->CheckStartFrame(3))
			{
				Sounds::Get()->Play("s3", 0.5f);
			}
			weapon_col->SetDamage(PlayerStatus::Get()->GetsDamage() * 0.5f);
			weapon_col->SetDir(dir);
			weapon_col->SetAtkType(NORMAL);

			OnWeaponCollision(3, 5, { dir * (30.f),  0.f, 0.f }, { size.x / 2.f, size.y, 1.f });

			if (animator->CheckStartFrame(5))
			{
				SetInputStateOn(bInput);
			}

			if (animator->IsEnd())
			{
				isSSA = true;
				_State = IDLE;
				isAttack = true;
				SSA_Combo++;
			}
		}
		else if (SSA_Combo == 2)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"ss2_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"ss2_f");
			}

			if (animator->CheckStartFrame(2))
				Sounds::Get()->Play("s3", 0.5f);

			weapon_col->SetDamage(PlayerStatus::Get()->GetsDamage() * 0.5f);
			weapon_col->SetDir(dir);
			weapon_col->SetAtkType(NORMAL);

			OnWeaponCollision(2, 4, { dir * (35.f),  0.f, 0.f }, { size.x / 1.8f, size.y, 1.f });

			if (animator->CheckStartFrame(4))
			{
				SetInputStateOn(bInput);
			}

			if (animator->IsEnd())
			{
				isSSA = true;
				_State = IDLE;
				isAttack = true;
				SSA_Combo++;
			}
		}
		else if (SSA_Combo == 3)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"ss3_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"ss3_f");
			}
			if (animator->CheckStartFrame(3))
			{
				AccelMove = 10.f * dir;
				Sounds::Get()->Play("s3", 0.5f);
			}

			weapon_col->SetDamage(PlayerStatus::Get()->GetsDamage() * 1.f);
			weapon_col->SetDir(dir);
			weapon_col->SetAtkType(KNOCKBACK);

			OnWeaponCollision(3, 6, { dir * (15.f),  0.f, 0.f }, { size.x / 1.5f, size.y, 1.f });

			if (animator->CheckStartFrame(6))
			{
				SetInputStateOn(bInput);
			}

			if (animator->IsEnd())
			{
				isSSA = true;
				_State = IDLE;
				isAttack = true;
				SSA_Combo = 1;
			}
		}

		break;

	case Player::EA:
		if (EA_Combo == 1)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"e1_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"e1_f");
			}
			if (animator->CheckStartFrame(5))
				Sounds::Get()->Play("e2", 0.5f);

			weapon_col->SetDamage(PlayerStatus::Get()->GeteDamage() * 0.7f);
			weapon_col->SetDir(dir);
			weapon_col->SetAtkType(KNOCKBACK);

			OnWeaponCollision(4, 8, { 0.f,  0.f, 0.f }, { size.x * 0.8f, size.y, 1.f });

			if (animator->CheckStartFrame(8))
			{
				SetInputStateOn(bInput);
			}

			if (animator->IsEnd())
			{
				isEA = true;
				_State = IDLE;
				isAttack = true;
				EA_Combo++;
			}
		}
		else if (EA_Combo == 2)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"e2_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"e2_f");
			}
			if (animator->CheckStartFrame(9))
				Sounds::Get()->Play("e2", 0.5f);

			weapon_col->SetDamage(PlayerStatus::Get()->GeteDamage() * 0.7f);
			weapon_col->SetDir(dir);
			weapon_col->SetAtkType(KNOCKBACK);

			OnWeaponCollision(8, 11, { dir * (20.f),  0.f, 0.f }, { size.x * 0.85f, size.y, 1.f });

			if (animator->CheckStartFrame(11))
			{
				SetInputStateOn(bInput);
			}

			if (animator->IsEnd())
			{
				isEA = true;
				_State = IDLE;
				isAttack = true;
				EA_Combo++;
			}
		}
		else if (EA_Combo == 3)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"e3_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"e3_f");
			}
			if (animator->CheckStartFrame(12))
				Sounds::Get()->Play("e3", 0.5f);

			weapon_col->SetDamage(PlayerStatus::Get()->GeteDamage() * 1.f);
			weapon_col->SetDir(dir);
			weapon_col->SetAtkType(RISE_UP);

			OnWeaponCollision(11, 16, { 0.f,  0.f, 0.f }, { size.x, size.y, 1.f });

			if (animator->CheckStartFrame(16))
			{
				SetInputStateOn(bInput);
			}
			
			if (animator->IsEnd())
			{
				isEA = true;
				_State = IDLE;
				isAttack = true;
				EA_Combo = 1;
			}
		}

		break;

	case Player::DAMAGED:
		if (damagemode == 0)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"damaged2_f");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"damaged2_r");
			}
		}
		else
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"damaged_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"damaged_f");
			}
		}
		

		if (animator->IsEnd() && CheckState(IsGround))
			_State = IDLE;

		break;

	case Player::DIE:

		collision->SetActive(false);

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"die_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"die_f");
		}

		if (!CheckInputState(IsGround))
		{
			MoveDir.x = dir * (-1.f) * 2.f;
		}

		if (Keyboard::Get()->Down('I'))
		{
			PlayerStatus::Get()->SetHp(PlayerStatus::Get()->GetMaxHp());
			_State = IDLE;
		}

		break;

	case Player::BACKJUMP:

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"backjump_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"backjump_f");
		}

		if (!CheckInputState(IsGround))
		{
			MoveDir.x = dir * (-1.f) * 2.f;
		}

		break;

	default:
		//_State = IDLE;
		break;
	}

	/*if (animator->IsEnd())
		_State = DEFAULT; */

}

void Player::Movement()
{
	// collision Update
	{
		if (_State == SLIDE)
		{
			collision->Update({ position.x, position.y, 0 }, { size.x * 0.24f , size.y * 0.4f, 1 }, 0.0f);
		}
		else
		{
			collision->Update({ position.x, position.y, 0 }, { size.x * 0.24f , size.y * 0.7f, 1 }, 0.0f);
		}
		weapon_col->Update(position + weaponPos, weaponSize, 0.0f);

	}

	MoveDir.x = (MoveDir.x * MoveSpeed) + AccelMove;
	rigidbody->Update();

	landGround = (CheckInputState(IsGround) && (Old_InputState & IsGround) == None) ? true : false;
	WallStart = (CheckInputState(IsWall) && (Old_InputState & IsWall) == None) ? true : false;

	position += MoveDir;


}





void Player::CreateArrow(float dir)
{
	if (as.empty())
	{
		Arrow* NewArrow = new Arrow({ position.x + (collision->GetSize().x / 2.f * dir), position.y + size.y * 0.36f, 0.f }, { 50.f, 10.f, 1.f }, 0.f, dir);

		as.push_back(NewArrow);
	}
	else
	{
		Arrow* currentArrow = nullptr;
		for (int i = 0; i < as.size(); i++)
		{
			if (!as[i]->GetIsActive())
			{
				currentArrow = as[i];
				as[i]->Init({ position.x + (collision->GetSize().x / 2.f * dir), position.y + size.y * 0.36f, 0.f }, { 50.f, 10.f, 1.f }, 0.f, dir);
				break;
			}
		}

		if (currentArrow == nullptr)
		{
			Arrow* NewArrow = new Arrow({ position.x + (collision->GetSize().x / 2.f * dir), position.y + size.y * 0.36f, 0.f }, { 50.f, 10.f, 1.f }, 0.f, dir);

			as.push_back(NewArrow);
		}
	}
}

void Player::CalculateComboTime()
{
	if (!isSSA && !isEA)
		return;

	if (isSSA == true)
	{
		if (SSAcomboTime > 1.f)
		{
			SSAcomboTime = 0.f;
			isSSA = false;
			SSA_Combo = 1;
		}
		else
			SSAcomboTime += delta;

	}
	if (isEA == true)
	{
		if (EAcomboTime > 1.5f)
		{
			EAcomboTime = 0.f;
			isEA = false;
			EA_Combo = 1;
		}
		else
			EAcomboTime += delta;

	}

}

void Player::Run()
{
	auto key = Keyboard::Get();

	// 움직임 조작
	if (key->Press(VK_RIGHT) && CheckInputState(bMove))
	{
		

		if (CheckInputState(bInput))
		{

			if (dir == -1.f)
				_State = TURN;
			else
				_State = RUN;
		}
		dir = 1.f;

		MoveDir.x = 1.f;
	}
	else if (key->Press(VK_LEFT) && CheckInputState(bMove))
	{
		

		if (CheckInputState(bInput))
		{

			if (dir == 1.f)
				_State = TURN;
			else
				_State = RUN;
		}
		dir = -1.f;

		MoveDir.x = -1.f;
	}


	if (!key->Press(VK_LEFT) && !key->Press(VK_RIGHT) && _State == RUN)
	{
		_State = DEFAULT;
	}
}

void Player::Dash()
{
	auto key = Keyboard::Get();

	if (key->Press(VK_LSHIFT))
	{
		if (abs(AccelMove) <= MaxAccel)
			AccelMove += (dir * 0.5f);

		if (abs(AccelMove) >= MaxAccel)
			AccelMove = MaxAccel * dir;
	}

}

void Player::DecreaseAccel()
{
	if (_State == RUN && Keyboard::Get()->Press(VK_LSHIFT))
		return;

	float Decrease = 0.f;

	switch (_State)
	{
		case Player::DEFAULT:
		case Player::IDLE:
		case Player::TURN:
		case Player::DOWN:
		case Player::LAND:
		case Player::WALL:
		case Player::JUMPATK:
		case Player::SLIDE:
		case Player::BOW:
		case Player::SSA:
		case Player::EA:
		case Player::DAMAGED:
		case Player::BACKJUMP:
		case Player::DIE:
		{
			Decrease = 0.5f;
			break;
		}
		case Player::UP:
		case Player::RUN:
		{
			Decrease = 0.2f;
			break;
		}
	}

	if (AccelMove > 0.f)
	{
		AccelMove -= Decrease;
	}
	else if (AccelMove < 0.f)
	{
		AccelMove += Decrease;
	}

	if (AccelMove >= -Decrease && AccelMove <= Decrease)
	{
		AccelMove = 0.f;
	}

}

void Player::WallJump()
{
	auto key = Keyboard::Get();

	if (key->Down(VK_SPACE))
	{
		_State = UP;
		MoveDir.y = jumpSpeed * 0.7f;
		AccelMove = dir * (-7.f);
		dir *= -1.f;
	}
}

void Player::Jumping()
{
	auto key = Keyboard::Get();

	if (key->Press(VK_SPACE) && CheckInputState(IsGround))
	{
		MoveDir.y = jumpSpeed;
		_State = UP;
	}

}

void Player::Down()
{
	if (MoveDir.y < 0.f && !CheckInputState(IsGround))
	{
		_State = DOWN;
	}
}

void Player::Land()
{
	if (landGround)
		_State = LAND;
}

void Player::Wall_Grab()
{
	auto key = Keyboard::Get();



	if (!CheckInputState(IsGround) && CheckInputState(IsWall))
	{
		if (WallStart)
			AccelMove = 0.f;

		_State = WALL;
		MoveDir.y = MoveDir.y * 0.5f;

	}
	else if ((CheckInputState(IsGround) || !CheckInputState(IsWall)) && _State == WALL)
	{
		_State = DEFAULT;
	}

}

void Player::BackJump()
{
	auto key = Keyboard::Get();

	if (key->Press(VK_UP) && CheckInputState(IsGround))
	{
		_State = BACKJUMP;
		MoveDir.y = jumpSpeed * 0.8f;
	}

}

void Player::S_Attack()
{
	auto key = Keyboard::Get();

	
	if (key->Press('A'))
	{
		if (_State != SLIDE)
		{
			if (isAttack)
				return;

			if ((PlayerStatus::Get()->GetCurrentStamina() - 100.f) >= 0.f)
			{
				PlayerStatus::Get()->UseStamina(100.f);

				_State = SSA;

				if (SSAcomboTime < 1.f)
				{
					SSAcomboTime = 0.f;

					if (SSA_Combo > PlayerStatus::Get()->GetsCount())
					{
						SSA_Combo = 1;
					}

				}
			}
		}
		else
		{
			if ((PlayerStatus::Get()->GetCurrentStamina() - 80.f) >= 0.f)
			{
				PlayerStatus::Get()->UseStamina(80.f);

				isSSA = false;
				_State = SSA;
				SSA_Combo = 3;
			}
		}
	}

}

void Player::E_Attack()
{
	auto key = Keyboard::Get();

	if (key->Press('S'))
	{
		if (isAttack)
			return;

		if ((PlayerStatus::Get()->GetCurrentStamina() - 300.f) >= 0.f)
		{
			PlayerStatus::Get()->UseStamina(300.f);

			_State = EA;

			if (EAcomboTime < 1.5f)
			{
				EAcomboTime = 0.f;

				if (EA_Combo > PlayerStatus::Get()->GeteCount())
				{
					EA_Combo = 1;
				}
			}
		}

	}

}

void Player::JumpAttack()
{
	auto key = Keyboard::Get();

	if (PlayerStatus::Get()->IsUnlockJumpAttack())
	{
		if (key->Press('S'))
		{
			if ((PlayerStatus::Get()->GetCurrentStamina() - 350.f) >= 0.f)
			{
				PlayerStatus::Get()->UseStamina(350.f);

				_State = JUMPATK;
			}
		}
	}
	
}

void Player::Bow()
{
	auto key = Keyboard::Get();

	if (key->Press('D'))
	{
		_State = BOW;
	}
}

void Player::Slide()
{
	auto key = Keyboard::Get();

	if ((AccelMove == 0.f || landGround) && _State == SLIDE)
	{
		collision->SetActive(true);
		_State = IDLE;
	}

	if (key->Down('Q') && CheckInputState(bInput))
	{
		if ((PlayerStatus::Get()->GetCurrentStamina() - 300.f) >= 0.f)
		{
			PlayerStatus::Get()->UseStamina(300.f);

			AccelMove = 14.f * dir;

			collision->SetActive(false);
			_State = SLIDE;
		}
	}

}

void Player::Damaged()
{
	vector<BoundingBox*> enemyWeapon = BoundingBox::GetTagCollision(BoundingBox::MonsterWeapon);

	for (auto w : enemyWeapon)
	{
		if (BoundingBox::OBB(collision, w))
		{


			if ((PlayerStatus::Get()->GetCurrentHp() - w->GetDamage()) <= 0.f)
			{
				PlayerStatus::Get()->SetHp(0.f);

				MoveDir.y = jumpSpeed * 0.5f;
				_State = DIE;
				cout << "Player HP : " << PlayerStatus::Get()->GetCurrentHp() << endl;
			}
			else
			{
				if (isDamaged)
					break;

				isDamaged = true;

				int rn = rand() % 6;

				switch (rn)
				{
				case 0:
				case 2:
				case 4:
				{
					Sounds::Get()->Play("d1", 0.3f);
					break;
				}
				case 1:
				case 3:
				case 5:
				{
					Sounds::Get()->Play("d3", 0.3f);
					break;
				}
				default:
					break;
				}

				DamageReaction(w->GetAtkType(), w->GetDir());
				if (w->GetAtkType() == GRAB)
					damagemode = 0;
				else
					damagemode = 1;

				PlayerStatus::Get()->SetHpDamaged(w->GetDamage());
				_State = DAMAGED;
				cout << "Player HP : " << PlayerStatus::Get()->GetCurrentHp() << endl;
			}

		}
	}

	if (isDamaged)
	{
		collision->SetActive(false);

		InvncTime += delta;

		if (InvncTime > 0.6f)
		{
			collision->SetActive(true);
			isDamaged = false;
			InvncTime = 0.f;
		}
	}
	else
	{
		if (_State == SLIDE || _State == JUMPATK)
			collision->SetActive(false);
		else
			collision->SetActive(true);
	}
}

void Player::IsAttack()
{
	if (!isAttack)
		return; 

	AttackDelay += delta;
	
	if (AttackDelay > 0.1f)
	{
		isAttack = false;
		AttackDelay = 0.f;
	}
}

void Player::Die()
{
	auto key = Keyboard::Get();

	if (key->Press(VK_DOWN))
	{
		MoveDir.y = jumpSpeed * 0.5f;
		_State = DIE;
	}
}

void Player::RecoveryStamina()
{
	PlayerStatus::Get()->PlusCurrentStamina(2.5f);
}

void Player::Update()
{

	// 방향 초기화
	MoveDir.x = 0.f;
	SetStatusInfo();


	// 시간 체크
	{
		delta = Time::Get()->WorldDelta();

		if (isCheck)
		{
			CheckTime += delta;
		}
		else
			CheckTime = 0.f;

		CalculateComboTime();
		IsAttack();
	}

	// 전처리
	{
		ControlState();

		for (Arrow* a : as)
		{
			a->Update();
		}
	}

	// 후처리
	{

		// 키입력 후 애니메이션 업데이트
		{
			animator->Update();
			animRect->Update(position, size, rotation);
		}

		Movement();
		RecoveryStamina();

	}


	// 리스폰
	if (position.y < -200.f)
	{
		SetPos(spawnPos);
		_State = DOWN;
		MoveDir.y = 0.f;
	}

}

void Player::Render()
{

	animRect->Render();
	//collision->Render();
	//rigidbody->Render();
	//weapon_col->Render();

	for (Arrow* a : as)
	{
		if (a->GetIsActive())
			a->Render();
	}
}

void Player::GUI()
{
	ImGui::Begin("State");
	{
		switch (_State)
		{
		case Player::DEFAULT:
			s_state = "DEFAULT";
			break;
		case Player::IDLE:
			s_state = "IDLE";
			break;
		case Player::RUN:
			s_state = "RUN";
			break;
		case Player::TURN:
			s_state = "TURN";
			break;
		case Player::UP:
			s_state = "UP";
			break;
		case Player::DOWN:
			s_state = "DOWN";
			break;
		case Player::LAND:
			s_state = "LAND";
			break;
		case Player::WALL:
			s_state = "WALL";
			break;
		case Player::JUMPATK:
			s_state = "JUMPATK";
			break;
		case Player::SLIDE:
			s_state = "SLIDE";
			break;
		case Player::BOW:
			s_state = "BOW";
			break;
		case Player::SSA:
			s_state = "SSA";
			break;
		case Player::EA:
			s_state = "EA";
			break;
		case Player::DAMAGED:
			s_state = "DAMAGED";
			break;
		case Player::DIE:
			s_state = "DIE";
			break;
		case Player::BACKJUMP:
			s_state = "BACKJUMP";
			break;
		default:
			break;
		}
		int d = dir;
		float s = MoveDir.x;
		int h = SSA_Combo;
		ImGui::Text(s_state.c_str());
		ImGui::Text("Direction : %d", d);
		ImGui::Text("Speed : %f", s);
		ImGui::Text("sCombo : %d", h);
	}
	ImGui::End();
}