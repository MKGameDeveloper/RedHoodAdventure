#include "Framework.h"
#include "Monster.h"

Bringer::Bringer(Vector3 position, float rotation)
	:Monster(position, { 330,215,1 }, rotation)
{
	detectRange = 400.f;

	rigidbody = new RigidBody(*this);

	// Character Status
	{
		MoveSpeed = 1.6f;
		jumpSpeed = 19.f;
	}

	// Animation
	{
		float Max_X = 10.f;
		float Max_Y = 6.f;

		Texture2D* srcTex = new Texture2D(TexturePath + L"bringer_sheet(140_93).png");
		Texture2D* srcTex2 = new Texture2D(TexturePath + L"bringer_sheet(reverse).png");

		Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

		Vector2 idle_f_s = Values::ZeroVec2;
		Vector2 idle_f_e = Vector2(texSize.x * (8.f / Max_X), texSize.y * (1.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 run_f_s = Vector2(0.f, texSize.y * (1.f / Max_Y));
		Vector2 run_f_e = Vector2(texSize.x * (8.f / Max_X), texSize.y * (2.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 damaged_f_s = Vector2(0.f, texSize.y * (2.f / Max_Y));
		Vector2 damaged_f_e = Vector2(texSize.x * (3.f / Max_X), texSize.y * (3.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 die_f_s = Vector2(0.f, texSize.y * (3.f / Max_Y));
		Vector2 die_f_e = Vector2(texSize.x, texSize.y * (4.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 attack_f_s = Vector2(0.f, texSize.y * (4.f / Max_Y));
		Vector2 attack_f_e = Vector2(texSize.x, texSize.y * (5.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 cast_f_s = Vector2(0.f, texSize.y * (5.f / Max_Y));
		Vector2 cast_f_e = Vector2(texSize.x * (9.f / Max_X), texSize.y * (6.f / Max_Y));


		// 24, 14

		AnimationClip* Idle_f = new AnimationClip(L"idle_f", srcTex, 8, Values::ZeroVec2, idle_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_f = new AnimationClip(L"run_f", srcTex, 8, run_f_s, run_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged_f = new AnimationClip(L"damaged_f", srcTex, 3, damaged_f_s, damaged_f_e, false, 1.f / 4.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_f = new AnimationClip(L"die_f", srcTex, 10, die_f_s, die_f_e, false, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* attack_f = new AnimationClip(L"attack_f", srcTex, 10, attack_f_s, attack_f_e, false, 1.f / 4.5f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* cast_f = new AnimationClip(L"cast_f", srcTex, 9, cast_f_s, cast_f_e, false, 1.f / 6.f, false);


		animator->AddAnimClip(Idle_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(attack_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(cast_f);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//reverse
		AnimationClip* Idle_r = new AnimationClip(L"idle_r", srcTex2, 8, Values::ZeroVec2, idle_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_r = new AnimationClip(L"run_r", srcTex2, 8, run_f_s, run_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged_r = new AnimationClip(L"damaged_r", srcTex2, 3, damaged_f_s, damaged_f_e, true, 1.f / 4.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_r = new AnimationClip(L"die_r", srcTex2, 10, die_f_s, die_f_e, true, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* attack_r = new AnimationClip(L"attack_r", srcTex2, 10, attack_f_s, attack_f_e, true, 1.f / 4.5f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* cast_r = new AnimationClip(L"cast_r", srcTex2, 9, cast_f_s, cast_f_e, true, 1.f / 6.f, false);

		animator->AddAnimClip(Idle_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(attack_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(cast_r);


		animator->SetCurrentAnimClip(L"idle_f");

		animRect->SetAnimator(animator);

		rigidbody = new RigidBody(*this);


		SAFE_DELETE(srcTex);
		SAFE_DELETE(srcTex2);

	}

	// Collision
	{
		collision = new BoundingBox(BoundingBox::Monster);
		collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

		weapon_col = new BoundingBox(BoundingBox::MonsterWeapon);
		weapon_col->Init(Color(0, 1, 0, 0.3f), BoundingBox::DOWN_CENTER);
		weapon_col->SetActive(false);
	}

	Init();
}

Bringer::~Bringer()
{
	for (BringerSpell* b : bs)
	{
		SAFE_DELETE(b);
	}
	SAFE_DELETE(weapon_col);
	SAFE_DELETE(collision);
	SAFE_DELETE(rigidbody);
}

void Bringer::ControlState()
{
	// 움직이고 있는지 off
	// 움직일수 있는지 off
	// 입력할수 있는지 초기화 x
	SetInputStateOff(IsMove | bInput | bMove);
	// 현재 상태에 따른 입력값을 받아와서 상태를 변경

	Damaged();

	switch (_State)
	{
	case Bringer::IDLE:
		SetInputStateOn(bMove | bInput);

		collision->SetActive(true);
		weapon_col->SetActive(false);

		Run();
		Smash();

		Cast();

		break;

	case Bringer::RUN:
		SetInputStateOn(bMove | bInput | IsMove);

		Run();
		Smash();

		Cast();

		break;

	case Bringer::ATTACK:
		Smash();

		break;

	case Bringer::CAST:
		Cast();
		break;

	case Bringer::DAMAGED:

		break;

	case Bringer::DIE:

		break;

	case Bringer::DEFAULT:
		_State = IDLE;

		break;

	}


	AnimState();
}

void Bringer::AnimState()
{
	DecreaseAccel();

	switch (_State)
	{
	case Bringer::IDLE:

		if (dir == 1.f)
			animator->SetCurrentAnimClip(L"idle_r");
		else if (dir == -1.f)
			animator->SetCurrentAnimClip(L"idle_f");

		if (CheckTime > TimeDelay)
			isCheck = false;

		break;

	case Bringer::RUN:

		if (dir == 1.f)
			animator->SetCurrentAnimClip(L"run_r");
		else if (dir == -1.f)
			animator->SetCurrentAnimClip(L"run_f");

		break;

	case Bringer::ATTACK:
		if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"attack_r");
		}
		else if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"attack_f");
		}

		weapon_col->SetDamage(_status.currentAtk * 1.f);
		weapon_col->SetDir(dir);
		weapon_col->SetAtkType(KNOCKBACK);

		Bringer::OnWeaponCollision(5, 7, { dir * (collision->GetSize().x * 1.8f),  0.f, 0.f }, { size.x / 1.3f , size.y, 1.f });

		if (animator->IsEnd())
		{
			oldDoAttack = DoAttack;
			DoAttack = false;
			_State = IDLE;
		}

		break;

	case Bringer::CAST:
		if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"cast_r");
		}
		else if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"cast_f");
		}

		if (spell_stack <= 2)
		{
			if (animator->IsEnd())
			{
				if (dir == 1.f)
					animator->SetCurrentAnimClip(L"idle_r");
				else if (dir == -1.f)
					animator->SetCurrentAnimClip(L"idle_f");

				CreateSpell();
				spell_stack++;
			}
		}

		if (spell_stack == 3)
		{
			spell_stack = 0;
			_State = IDLE;
		}

		break;

	case Bringer::DAMAGED:
		
		weapon_col->SetActive(false);
		
		if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"damaged_r");
		}
		else if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"damaged_f");
		}

		if (animator->IsEnd() && CheckState(IsGround))
		{
			if (prevState == CAST )
			{
				_State = prevState;
			}
			else
				_State = IDLE;
			
		}

		break;

	case Bringer::DIE:

		collision->SetActive(false);
		weapon_col->SetActive(false);

		if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"die_r");
		}
		else if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"die_f");
		}

		if (animator->IsEnd())
		{
			isdie = true;
		}

		break;

	default:
		break;
	}
}
void Bringer::Col_Update()
{
	collision->Update({ position.x , position.y, position.z }, { size.x / 4.5f , size.y / 1.7f, size.z }, rotation);
	weapon_col->Update(position + weaponPos, weaponSize, 0.0f);
}

void Bringer::CreateSpell()
{
	vector<BoundingBox*> player = BoundingBox::GetTagCollision(BoundingBox::Player);

	Vector3 cPos = player[0]->GetData()->centerPos;

	if (bs.empty())
	{
		BringerSpell* NewSpell = new BringerSpell({ cPos.x, position.y, 0.f }, 0.f, 20.f, dir);

		bs.push_back(NewSpell);
	}
	else
	{
		BringerSpell* currentSpell = nullptr;
		for (int i = 0; i < bs.size(); i++)
		{
			if (!bs[i]->GetIsActive())
			{
				currentSpell = bs[i];
				bs[i]->Init({ cPos.x, position.y, 0.f }, 0.f, 20.f, dir);
				break;
			}
		}

		if (currentSpell == nullptr)
		{
			BringerSpell* NewSpell = new BringerSpell({ cPos.x, position.y, 0.f }, 0.f, 20.f, dir);

			bs.push_back(NewSpell);
		}
	}
}

void Bringer::Run()
{
	if (!isCheck)
	{
		//dir = playerDir;
		if (!detected)
		{
			_State = RUN;
			MoveDir.x = MoveSpeed * dir;
		}
		else
		{
			dir = playerDir;
			if (!DoAttack)
			{
				_State = RUN;
				MoveDir.x = MoveSpeed * dir;
			}
		}
		
	}
	else
		_State = IDLE;
}

void Bringer::Smash()
{
	if (detected)
	{
		if (!isCheck)
		{
			if (DoAttack)
			{
				if (oldDoAttack == false)
					dir = playerDir;
				MoveDir.x = 0.f;
				isCheck = true;
				TimeDelay = AttackDelay;
				_State = ATTACK;
			}
		}
	}
	
	
	
	
}

void Bringer::Damaged()
{
	vector<BoundingBox*> weapon = BoundingBox::GetTagCollision(BoundingBox::Weapon);

	for (auto w : weapon)
	{
		if (BoundingBox::OBB(collision, w))
		{
			if (w != TargetWeapon)
			{
				olddetected = detected;
				detected = true;
				detectedTime = 0.f;

				SetTargetWeapon(w);
				if ((_status.currentHp - w->GetDamage()) <= 0.f)
				{
					_status.currentHp = 0.f;
					_State = DIE;
					soul->OnIsActive(position);
					cout << "Bringer HP : " << _status.currentHp << endl;
				}
				else
				{
					if (_State == CAST)
					{
						prevState = _State;
					}
					else
					{
						prevState = IDLE;
					}
					DamageReaction(w->GetAtkType(), w->GetDir());
					_status.currentHp -= w->GetDamage();
					_State = DAMAGED;
					cout << "Bringer HP : " << _status.currentHp << endl;
				}
				
			}
			
		}
	}
}


void Bringer::Cast()
{
	if (bSpecialAttack && detected)
	{
		_State = CAST;
		bSpecialAttack = false;
	}
}


void Bringer::Update()
{
	if (!isdie)
	{
		// 방향 초기화
		MoveDir.x = 0.f;
		SetStatusInfo();
		CheckTargetWeapon();
		//cout << "detected : "  << detected << endl;
		//cout << "Do Attack : "  << DoAttack << endl << endl;

		// 시간 체크
		{
			delta = Time::Get()->WorldDelta();

			DetectPlayer();
			CheckDestination();

			if (isCheck)
			{
				CheckTime += delta;
			}
			else
				CheckTime = 0.f;

		}

		// 전처리
		{
			ControlState();

			for (BringerSpell* b : bs)
			{
				b->Update();
			}
		}

		// 후처리
		{
			// 키입력 후 애니메이션 업데이트
			{
				animRect->Update({ position.x + (dir * size.x / 4.f), position.y, position.z }, size, rotation);
				animator->Update();
			}

			Movement();

		}
	}
	else
	{
		soul->Update();
		if (Keyboard::Get()->Down('F'))
		{
			Init();
			_State = IDLE;
			isdie = false;
		}
	}
	


}

void Bringer::Render()
{
	if (!isdie)
	{
		animRect->Render();
		//weapon_col->Render();
	}
	else
	{
		soul->Render();
	}

	for (BringerSpell* b : bs)
	{
		b->Render();
	}
}


void Bringer::Init()
{
	soulPoint = rand() % 50 + 200;

	__super::Init();

	_State = IDLE;
}




MudGuard::MudGuard(Vector3 position, float rotation)
	:Monster(position, { 230,80,1 }, rotation)
{
	detectRange = 200.f;

	attackRange = 80.f;
	AttackDelay = 1.8f;

	rigidbody = new RigidBody(*this);

	// Character Status
	{
		MoveSpeed = 1.f;
		jumpSpeed = 15.f;
	}

	// Animation
	{
		float Max_X = 8.f;
		float Max_Y = 6.f;

		Texture2D* srcTex = new Texture2D(TexturePath + L"MudGuard_sheet(618_138).png");
		Texture2D* srcTex2 = new Texture2D(TexturePath + L"MudGuard_sheet(reverse).png");

		Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

		Vector2 idle_f_s = Values::ZeroVec2;
		Vector2 idle_f_e = Vector2(texSize.x * (5.f / Max_X), texSize.y * (1.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 attack_f_s = Vector2(0.f, texSize.y * (1.f / Max_Y));
		Vector2 attack_f_e = Vector2(texSize.x * (7.f / Max_X), texSize.y * (2.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 sattack_f_s = Vector2(0.f, texSize.y * (2.f / Max_Y));
		Vector2 sattack_f_e = Vector2(texSize.x * (7.f / Max_X), texSize.y * (3.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 run_f_s = Vector2(0.f, texSize.y * (3.f / Max_Y));
		Vector2 run_f_e = Vector2(texSize.x * (6.f / Max_X), texSize.y * (4.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 damaged_f_s = Vector2(0.f, texSize.y * (4.f / Max_Y));
		Vector2 damaged_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (5.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 die_f_s = Vector2(0.f, texSize.y * (5.f / Max_Y));
		Vector2 die_f_e = Vector2(texSize.x * (8.f / Max_X), texSize.y * (6.f / Max_Y));

		


		// 24, 14

		AnimationClip* Idle_f = new AnimationClip(L"idle_f", srcTex, 5, Values::ZeroVec2, idle_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* attack_f = new AnimationClip(L"attack_f", srcTex, 7, attack_f_s, attack_f_e, false, 1.f / 4.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* sattack_f = new AnimationClip(L"sattack_f", srcTex, 7, sattack_f_s, sattack_f_e, false, 1.f / 4.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_f = new AnimationClip(L"run_f", srcTex, 6, run_f_s, run_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged_f = new AnimationClip(L"damaged_f", srcTex, 4, damaged_f_s, damaged_f_e, false, 1.f / 8.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_f = new AnimationClip(L"die_f", srcTex, 8, die_f_s, die_f_e, false, 1.f / 5.f, false);
		


		animator->AddAnimClip(Idle_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(attack_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(sattack_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_f);
		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//reverse
		AnimationClip* Idle_r = new AnimationClip(L"idle_r", srcTex2, 5, Values::ZeroVec2, idle_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* attack_r = new AnimationClip(L"attack_r", srcTex2, 7, attack_f_s, attack_f_e, true, 1.f / 4.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* sattack_r = new AnimationClip(L"sattack_r", srcTex2, 7, sattack_f_s, sattack_f_e, true, 1.f / 4.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_r = new AnimationClip(L"run_r", srcTex2, 6, run_f_s, run_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged_r = new AnimationClip(L"damaged_r", srcTex2, 4, damaged_f_s, damaged_f_e, true, 1.f / 8.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_r = new AnimationClip(L"die_r", srcTex2, 8, die_f_s, die_f_e, true, 1.f / 5.f, false);

		animator->AddAnimClip(Idle_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(attack_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(sattack_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_r);
		


		animator->SetCurrentAnimClip(L"idle_f");

		animRect->SetAnimator(animator);

		rigidbody = new RigidBody(*this);


		SAFE_DELETE(srcTex);
		SAFE_DELETE(srcTex2);

	}

	// Collision
	{
		collision = new BoundingBox(BoundingBox::Monster);
		collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

		weapon_col = new BoundingBox(BoundingBox::MonsterWeapon);
		weapon_col->Init(Color(0, 1, 0, 0.3f), BoundingBox::DOWN_CENTER);
		weapon_col->SetActive(false);
	}


	Init();
}

MudGuard::~MudGuard()
{
	SAFE_DELETE(weapon_col);
	SAFE_DELETE(collision);
	SAFE_DELETE(rigidbody);
}

void MudGuard::ControlState()
{
	// 움직이고 있는지 off
	// 움직일수 있는지 off
	// 입력할수 있는지 초기화 x
	SetInputStateOff(IsMove | bInput | bMove);
	// 현재 상태에 따른 입력값을 받아와서 상태를 변경

	Damaged();

	switch (_State)
	{
	case MudGuard::IDLE:
		SetInputStateOn(bMove | bInput);

		collision->SetActive(true);
		weapon_col->SetActive(false);

		Run();
		Attack();

		S_Attack();

		break;

	case MudGuard::RUN:
		SetInputStateOn(bMove | bInput | IsMove);

		Run();
		Attack();

		S_Attack();

		break;

	case MudGuard::ATTACK:
		Attack();
		break;

	case MudGuard::SATTACK:
		S_Attack();
		break;

	case MudGuard::DAMAGED:

		break;

	case MudGuard::DIE:

		break;

	case MudGuard::DEFAULT:
		_State = IDLE;

		break;

	}


	AnimState();
}

void MudGuard::AnimState()
{
	DecreaseAccel();

	switch (_State)
	{
	case MudGuard::IDLE:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"idle_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"idle_f");

		if (CheckTime > TimeDelay)
			isCheck = false;

		break;

	case MudGuard::RUN:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"run_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"run_f");

		break;

	case MudGuard::ATTACK:
		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"attack_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"attack_f");
		}

		weapon_col->SetDamage(_status.currentAtk * 1.f);
		weapon_col->SetDir(dir);
		weapon_col->SetAtkType(KNOCKBACK);

		MudGuard::OnWeaponCollision(4, 6, { dir * (collision->GetSize().x * 0.8f),  10.f, 0.f }, { size.x / 4.f , size.y / 3.f, 1.f });

		if (animator->IsEnd())
		{
			oldDoAttack = DoAttack;
			DoAttack = false;
			_State = IDLE;
		}

		break;

	case MudGuard::SATTACK:
		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"sattack_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"sattack_f");
		}

		weapon_col->SetDamage(_status.currentAtk * 1.5f);
		weapon_col->SetDir(dir);
		weapon_col->SetAtkType(RISE_UP);

		MudGuard::OnWeaponCollision(4, 6, { dir * (collision->GetSize().x * 2.1f),  10.f, 0.f }, { size.x / 1.35f , size.y / 3.f, 1.f });

		if (satk_stack <= 1)
		{
			if (animator->IsEnd())
			{
				if (dir == -1.f)
					animator->SetCurrentAnimClip(L"idle_r");
				else if (dir == 1.f)
					animator->SetCurrentAnimClip(L"idle_f");

				satk_stack++;
			}
		}

		if (satk_stack == 2)
		{
			satk_stack = 0;

			oldDoAttack = DoAttack;
			DoAttack = false;

			_State = IDLE;
		}

		break;

	case MudGuard::DAMAGED:

		weapon_col->SetActive(false);

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"damaged_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"damaged_f");
		}


		if (animator->IsEnd() && CheckState(IsGround))
		{

			if (prevState == SATTACK)
			{
				_State = prevState;
			}
			else
				_State = IDLE;
		}

		break;

	case MudGuard::DIE:

		collision->SetActive(false);
		weapon_col->SetActive(false);

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"die_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"die_f");
		}

		if (animator->IsEnd())
		{
			isdie = true;
		}

		break;

	default:
		break;
	}
}
void MudGuard::Col_Update()
{
	collision->Update({ position.x , position.y, position.z }, { size.x / 6.f , size.y / 1.5f, size.z }, rotation);
	weapon_col->Update(position + weaponPos, weaponSize, 0.0f);
}


void MudGuard::Run()
{
	if (!isCheck)
	{
		//dir = playerDir;
		if (!detected)
		{
			_State = RUN;
			MoveDir.x = MoveSpeed * dir;
		}
		else
		{
			dir = playerDir;
			if (!DoAttack)
			{
				_State = RUN;
				MoveDir.x = MoveSpeed * dir;
			}
		}

	}
	else
		_State = IDLE;
}

void MudGuard::Attack()
{
	if (detected)
	{
		if (!isCheck)
		{
			if (DoAttack)
			{
				if (oldDoAttack == false)
					dir = playerDir;
				MoveDir.x = 0.f;
				isCheck = true;
				TimeDelay = AttackDelay;
				_State = ATTACK;
			}
		}
	}
}

void MudGuard::S_Attack()
{
	if (bSpecialAttack && detected)
	{
		if (DoAttack)
		{
			if (oldDoAttack == false)
				dir = playerDir;
			MoveDir.x = 0.f;
			isCheck = true;
			TimeDelay = AttackDelay;
			_State = SATTACK;
			bSpecialAttack = false;
		}
		
		
	}
}




void MudGuard::Damaged()
{
	vector<BoundingBox*> weapon = BoundingBox::GetTagCollision(BoundingBox::Weapon);

	for (auto w : weapon)
	{
		if (BoundingBox::OBB(collision, w))
		{
			if (w != TargetWeapon)
			{
				olddetected = detected;
				detected = true;
				detectedTime = 0.f;

				SetTargetWeapon(w);
				if ((_status.currentHp - w->GetDamage()) <= 0.f)
				{
					_status.currentHp = 0.f;
					_State = DIE;
					soul->OnIsActive(position);
					cout << "MudGuard HP : " << _status.currentHp << endl;
				}
				else
				{
					if (_State == SATTACK)
					{
						prevState = _State;
					}
					else
					{
						prevState = IDLE;
					}

					Sounds::Get()->Play("m_damaged", 0.5f);

					DamageReaction(w->GetAtkType(), w->GetDir());
					_status.currentHp -= w->GetDamage();
					_State = DAMAGED;
					cout << "MudGuard HP : " << _status.currentHp << endl;
				}

			}

		}
	}
}


void MudGuard::Update()
{
	if (!isdie)
	{
		// 방향 초기화
		MoveDir.x = 0.f;
		SetStatusInfo();
		CheckTargetWeapon();

		// 시간 체크
		{
			delta = Time::Get()->WorldDelta();

			DetectPlayer();
			CheckDestination();

			if (isCheck)
			{
				CheckTime += delta;
			}
			else
				CheckTime = 0.f;

		}

		// 전처리
		{
			ControlState();
		}

		// 후처리
		{
			// 키입력 후 애니메이션 업데이트
			{
				animRect->Update({ position.x + (dir * size.x / 4.f), position.y, position.z }, size, rotation);
				animator->Update();
			}

			Movement();

		}
	}
	else
	{
		soul->Update();
	}



}

void MudGuard::Render()
{
	if (!isdie)
	{
		//collision->Render();
		animRect->Render();
		//weapon_col->Render();
	}
	else
		soul->Render();

}

void MudGuard::Init()
{
	soulPoint = rand() % 50 + 100;

	__super::Init();

	_State = IDLE;
}




BombDroid::BombDroid(Vector3 position, float rotation)
	:Monster(position, { 280.f,190.f,1 }, rotation)
{
	detectRange = 400.f;

	attackRange = 40.f;
	AttackDelay = 1.8f;

	rigidbody = new RigidBody(*this);

	// Character Status
	{
		MoveSpeed = 2.f;
		jumpSpeed = 15.f;
	}

	// Animation
	{
		float Max_X = 18.f;
		float Max_Y = 4.f;

		Texture2D* srcTex = new Texture2D(TexturePath + L"BombDroid(2088_308).png");
		Texture2D* srcTex2 = new Texture2D(TexturePath + L"BombDroid(reverse).png");

		Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());


		Vector2 attack_f_s = Values::ZeroVec2;
		Vector2 attack_f_e = Vector2(texSize.x * (18.f / Max_X), texSize.y * (1.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 idle_f_s = Vector2(0.f, texSize.y * (1.f / Max_Y));
		Vector2 idle_f_e = Vector2(texSize.x * (6.f / Max_X), texSize.y * (2.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 run_f_s = Vector2(0.f, texSize.y * (2.f / Max_Y));
		Vector2 run_f_e = Vector2(texSize.x * (8.f / Max_X), texSize.y * (3.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 die_f_s = Vector2(0.f, texSize.y * (3.f / Max_Y));
		Vector2 die_f_e = Vector2(texSize.x * (11.f / Max_X), texSize.y * (4.f / Max_Y));




		// 24, 14

		AnimationClip* attack_f = new AnimationClip(L"attack_f", srcTex, 18, Values::ZeroVec2, attack_f_e, false, 1.f / 9.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* Idle_f = new AnimationClip(L"idle_f", srcTex, 6, idle_f_s, idle_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_f = new AnimationClip(L"run_f", srcTex, 8, run_f_s, run_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_f = new AnimationClip(L"die_f", srcTex, 11, die_f_s, die_f_e, false, 1.f / 5.f, false);



		animator->AddAnimClip(attack_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(Idle_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_f);


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//reverse
		AnimationClip* attack_r = new AnimationClip(L"attack_r", srcTex2, 18, Values::ZeroVec2, attack_f_e, true, 1.f / 9.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* Idle_r = new AnimationClip(L"idle_r", srcTex2, 6, idle_f_s, idle_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_r = new AnimationClip(L"run_r", srcTex2, 8, run_f_s, run_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_r = new AnimationClip(L"die_r", srcTex2, 11, die_f_s, die_f_e, true, 1.f / 5.f, false);

		animator->AddAnimClip(attack_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(Idle_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_r);



		animator->SetCurrentAnimClip(L"idle_f");

		animRect->SetAnimator(animator);

		rigidbody = new RigidBody(*this);


		SAFE_DELETE(srcTex);
		SAFE_DELETE(srcTex2);

	}

	// Collision
	{
		collision = new BoundingBox(BoundingBox::Monster);
		collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

		weapon_col = new BoundingBox(BoundingBox::MonsterWeapon);
		weapon_col->Init(Color(0, 1, 0, 0.3f), BoundingBox::DOWN_CENTER);
		weapon_col->SetActive(false);
	}

	Init();
}

BombDroid::~BombDroid()
{
	SAFE_DELETE(weapon_col);
	SAFE_DELETE(collision);
	SAFE_DELETE(rigidbody);
}

void BombDroid::ControlState()
{
	// 움직이고 있는지 off
	// 움직일수 있는지 off
	// 입력할수 있는지 초기화 x
	SetInputStateOff(IsMove | bInput | bMove);
	// 현재 상태에 따른 입력값을 받아와서 상태를 변경

	switch (_State)
	{
	case BombDroid::IDLE:
		SetInputStateOn(bMove | bInput);

		weapon_col->SetActive(false);

		Run();
		Attack();

		break;

	case BombDroid::RUN:
		SetInputStateOn(bMove | bInput | IsMove);

		Run();
		Attack();

		break;

	case BombDroid::ATTACK:
		Attack();
		break;

	case BombDroid::DIE:

		break;

	case BombDroid::DEFAULT:
		_State = IDLE;

		break;

	}


	AnimState();
}

void BombDroid::AnimState()
{
	DecreaseAccel();

	switch (_State)
	{
	case BombDroid::IDLE:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"idle_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"idle_f");

		if (CheckTime > TimeDelay)
			isCheck = false;

		break;

	case BombDroid::RUN:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"run_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"run_f");

		break;

	case BombDroid::ATTACK:
		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"attack_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"attack_f");
		}

		weapon_col->SetDamage(_status.currentAtk * 1.5f);
		weapon_col->SetDir(dir);
		weapon_col->SetAtkType(KNOCKBACK);

		BombDroid::OnWeaponCollision(7, 10, { 0.f,  0.f, 0.f }, { size.x / 2.f , size.y / 5.f, 1.f });

		if (animator->IsEnd())
		{
			oldDoAttack = DoAttack;
			DoAttack = false;
			_State = DIE;
		}

		break;

	case BombDroid::DIE:

		collision->SetActive(false);
		weapon_col->SetActive(false);

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"die_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"die_f");
		}

		weapon_col->SetDamage(_status.currentAtk * 1.f);
		weapon_col->SetDir(dir);
		weapon_col->SetAtkType(RISE_UP);
		BombDroid::OnWeaponCollision(2, 4, { 0.f,  0.f, 0.f }, { size.x / 4.f , size.y / 6.f, 1.f });


		if (animator->IsEnd())
		{
			isdie = true;
		}

		break;

	default:
		break;
	}
}
void BombDroid::Col_Update()
{
	collision->Update({ position.x , position.y, position.z }, { size.x / 6.f , size.y / 1.5f, size.z }, rotation);
	weapon_col->Update(position + weaponPos, weaponSize, 0.0f);
}


void BombDroid::Run()
{
	if (!isCheck)
	{
		//dir = playerDir;
		if (!detected)
		{
			_State = RUN;
			MoveDir.x = MoveSpeed * dir;
		}
		else
		{
			dir = playerDir;
			if (!DoAttack)
			{
				_State = RUN;
				MoveDir.x = MoveSpeed * dir;
			}
		}

	}
	else
		_State = IDLE;
}

void BombDroid::Attack()
{
	if (detected)
	{
		if (!isCheck)
		{
			if (DoAttack)
			{
				if (oldDoAttack == false)
					dir = playerDir;
				MoveDir.x = 0.f;
				isCheck = true;
				TimeDelay = AttackDelay;
				_State = ATTACK;
			}
		}
	}
}

void BombDroid::Update()
{
	if (!isdie)
	{
		// 방향 초기화
		MoveDir.x = 0.f;
		SetStatusInfo();
		CheckTargetWeapon();
		//cout << "detected : "  << detected << endl;
		//cout << "Do Attack : "  << DoAttack << endl << endl;

		// 시간 체크
		{
			delta = Time::Get()->WorldDelta();

			DetectPlayer();
			CheckDestination();

			if (isCheck)
			{
				CheckTime += delta;
			}
			else
				CheckTime = 0.f;

		}

		// 전처리
		{
			ControlState();
		}

		// 후처리
		{
			// 키입력 후 애니메이션 업데이트
			{
				animRect->Update({ position.x , position.y, position.z }, size, rotation);
				animator->Update();
			}

			Movement();

		}
	}
	else
	{
		if (Keyboard::Get()->Down('F'))
		{
			Init();
			_State = IDLE;
		}
	}



}

void BombDroid::Render()
{
	if (!isdie)
	{
		//collision->Render();
		animRect->Render();
		//weapon_col->Render();
	}

}

void BombDroid::Init()
{
	__super::Init();

	_State = IDLE;
}



ShadowMage::ShadowMage(Vector3 position, float rotation)
	:Monster(position, { 200,120,1 }, rotation)
{
	detectRange = 400.f;
	s_attack_cooldown = 3.f;

	rigidbody = new RigidBody(*this);

	// Character Status
	{
		MoveSpeed = 1.6f;
		jumpSpeed = 19.f;
	}

	// Animation
	{
		float Max_X = 8.f;
		float Max_Y = 6.f;

		Texture2D* srcTex = new Texture2D(TexturePath + L"shadowMage(528_216).png");
		Texture2D* srcTex2 = new Texture2D(TexturePath + L"shadowMage(reverse).png");

		Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

		Vector2 idle_f_s = Values::ZeroVec2;
		Vector2 idle_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (1.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 run_f_s = Vector2(0.f, texSize.y * (1.f / Max_Y));
		Vector2 run_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (2.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 damaged_f_s = Vector2(0.f, texSize.y * (2.f / Max_Y));
		Vector2 damaged_f_e = Vector2(texSize.x * (3.f / Max_X), texSize.y * (3.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 die_f_s = Vector2(0.f, texSize.y * (3.f / Max_Y));
		Vector2 die_f_e = Vector2(texSize.x, texSize.y * (4.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 attack_f_s = Vector2(0.f, texSize.y * (4.f / Max_Y));
		Vector2 attack_f_e = Vector2(texSize.x * (6.f / Max_X), texSize.y * (5.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 cast_f_s = Vector2(0.f, texSize.y * (5.f / Max_Y));
		Vector2 cast_f_e = Vector2(texSize.x * (7.f / Max_X), texSize.y * (6.f / Max_Y));


		// 24, 14

		AnimationClip* Idle_f = new AnimationClip(L"idle_f", srcTex, 4, Values::ZeroVec2, idle_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_f = new AnimationClip(L"run_f", srcTex, 4, run_f_s, run_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged_f = new AnimationClip(L"damaged_f", srcTex, 3, damaged_f_s, damaged_f_e, false, 1.f / 4.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_f = new AnimationClip(L"die_f", srcTex, 8, die_f_s, die_f_e, false, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* attack_f = new AnimationClip(L"attack_f", srcTex, 6, attack_f_s, attack_f_e, false, 1.f / 4.5f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* cast_f = new AnimationClip(L"cast_f", srcTex, 7, cast_f_s, cast_f_e, false, 1.f / 6.f, false);


		animator->AddAnimClip(Idle_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(attack_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(cast_f);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//reverse
		AnimationClip* Idle_r = new AnimationClip(L"idle_r", srcTex2, 4, Values::ZeroVec2, idle_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_r = new AnimationClip(L"run_r", srcTex2, 4, run_f_s, run_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* damaged_r = new AnimationClip(L"damaged_r", srcTex2, 3, damaged_f_s, damaged_f_e, true, 1.f / 4.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_r = new AnimationClip(L"die_r", srcTex2, 8, die_f_s, die_f_e, true, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* attack_r = new AnimationClip(L"attack_r", srcTex2, 6, attack_f_s, attack_f_e, true, 1.f / 4.5f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* cast_r = new AnimationClip(L"cast_r", srcTex2, 7, cast_f_s, cast_f_e, true, 1.f / 6.f, false);

		animator->AddAnimClip(Idle_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(damaged_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(attack_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(cast_r);


		animator->SetCurrentAnimClip(L"idle_f");

		animRect->SetAnimator(animator);

		rigidbody = new RigidBody(*this);


		SAFE_DELETE(srcTex);
		SAFE_DELETE(srcTex2);

	}

	// Collision
	{
		collision = new BoundingBox(BoundingBox::Monster);
		collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

		weapon_col = new BoundingBox(BoundingBox::MonsterWeapon);
		weapon_col->Init(Color(0, 1, 0, 0.3f), BoundingBox::DOWN_CENTER);
		weapon_col->SetActive(false);
	}



	Init();
}

ShadowMage::~ShadowMage()
{
	for (ShadowMageSpell* s : ss)
	{
		SAFE_DELETE(s);
	}
	SAFE_DELETE(weapon_col);
	SAFE_DELETE(collision);
	SAFE_DELETE(rigidbody);
}

void ShadowMage::ControlState()
{
	// 움직이고 있는지 off
	// 움직일수 있는지 off
	// 입력할수 있는지 초기화 x
	SetInputStateOff(IsMove | bInput | bMove);
	// 현재 상태에 따른 입력값을 받아와서 상태를 변경

	Damaged();

	switch (_State)
	{
	case ShadowMage::IDLE:
		SetInputStateOn(bMove | bInput);

		collision->SetActive(true);
		weapon_col->SetActive(false);

		Run();
		Smash();

		Cast();

		break;

	case ShadowMage::RUN:
		SetInputStateOn(bMove | bInput | IsMove);

		Run();
		Smash();

		Cast();

		break;

	case ShadowMage::ATTACK:
		Smash();
		break;

	case ShadowMage::CAST:
		Cast();
		break;

	case ShadowMage::DAMAGED:

		break;

	case ShadowMage::DIE:

		break;

	case ShadowMage::DEFAULT:
		_State = IDLE;

		break;

	}


	AnimState();
}

void ShadowMage::AnimState()
{
	DecreaseAccel();

	switch (_State)
	{
	case ShadowMage::IDLE:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"idle_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"idle_f");

		if (CheckTime > TimeDelay)
			isCheck = false;

		break;

	case ShadowMage::RUN:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"run_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"run_f");

		break;

	case ShadowMage::ATTACK:
		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"attack_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"attack_f");
		}

		weapon_col->SetDamage(_status.currentAtk * 1.f);
		weapon_col->SetDir(dir);
		weapon_col->SetAtkType(GRAB);

		ShadowMage::OnWeaponCollision(2, 4, { dir * (collision->GetSize().x),  25.f, 0.f }, { size.x / 2.f , size.y / 2.f, 1.f });

		if (animator->IsEnd())
		{
			oldDoAttack = DoAttack;
			DoAttack = false;
			_State = IDLE;
		}

		break;

	case ShadowMage::CAST:
		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"cast_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"cast_f");
		}

		
		if (animator->IsEnd())
		{
			CreateSpell();
			_State = IDLE;

		}

		break;

	case ShadowMage::DAMAGED:

		weapon_col->SetActive(false);

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"damaged_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"damaged_f");
		}

		if (animator->IsEnd() && CheckState(IsGround))
		{
			if (prevState == CAST)
			{
				_State = prevState;
			}
			else
				_State = IDLE;

		}

		break;

	case ShadowMage::DIE:

		collision->SetActive(false);
		weapon_col->SetActive(false);

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"die_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"die_f");
		}

		if (animator->IsEnd())
		{
			isdie = true;
		}

		break;

	default:
		break;
	}
}
void ShadowMage::Col_Update()
{
	collision->Update({ position.x , position.y, position.z }, { size.x / 4.f , size.y / 1.3f, size.z }, rotation);
	weapon_col->Update(position + weaponPos, weaponSize, 0.0f);
}

void ShadowMage::CreateSpell()
{
	vector<BoundingBox*> player = BoundingBox::GetTagCollision(BoundingBox::Player);

	Vector3 cPos = player[0]->GetData()->centerPos;

	if (ss.empty())
	{
		ShadowMageSpell* NewSpell = new ShadowMageSpell({ cPos.x, position.y, 0.f }, 0.f, 20.f, dir);

		ss.push_back(NewSpell);
	}
	else
	{
		ShadowMageSpell* currentSpell = nullptr;
		for (int i = 0; i < ss.size(); i++)
		{
			if (!ss[i]->GetIsActive())
			{
				currentSpell = ss[i];
				ss[i]->Init({ cPos.x, position.y, 0.f }, 0.f, 20.f, dir);
				break;
			}
		}

		if (currentSpell == nullptr)
		{
			ShadowMageSpell* NewSpell = new ShadowMageSpell({ cPos.x, position.y, 0.f }, 0.f, 20.f, dir);

			ss.push_back(NewSpell);
		}
	}
}

void ShadowMage::Run()
{
	if (!isCheck)
	{
		//dir = playerDir;
		if (!detected)
		{
			_State = RUN;
			MoveDir.x = MoveSpeed * dir;
		}
		else
		{
			dir = playerDir;
			if (!DoAttack)
			{
				_State = RUN;
				MoveDir.x = MoveSpeed * dir;
			}
		}

	}
	else
		_State = IDLE;
}

void ShadowMage::Smash()
{
	if (detected)
	{
		if (!isCheck)
		{
			if (DoAttack)
			{
				if (oldDoAttack == false)
					dir = playerDir;
				MoveDir.x = 0.f;
				isCheck = true;
				TimeDelay = AttackDelay;
				_State = ATTACK;
			}
		}
	}




}

void ShadowMage::Damaged()
{
	vector<BoundingBox*> weapon = BoundingBox::GetTagCollision(BoundingBox::Weapon);

	for (auto w : weapon)
	{
		if (BoundingBox::OBB(collision, w))
		{
			if (w != TargetWeapon)
			{
				olddetected = detected;
				detected = true;
				detectedTime = 0.f;

				SetTargetWeapon(w);
				if ((_status.currentHp - w->GetDamage()) <= 0.f)
				{
					_status.currentHp = 0.f;
					_State = DIE;
					soul->OnIsActive(position);
					cout << "ShadowMage HP : " << _status.currentHp << endl;
				}
				else
				{
					if (_State == CAST)
					{
						prevState = _State;
					}
					else
					{
						prevState = IDLE;
					}
					DamageReaction(w->GetAtkType(), w->GetDir());
					_status.currentHp -= w->GetDamage();
					_State = DAMAGED;
					cout << "ShadowMage HP : " << _status.currentHp << endl;
				}

			}

		}
	}
}


void ShadowMage::Cast()
{
	if (bSpecialAttack && detected)
	{
		_State = CAST;
		bSpecialAttack = false;
	}
}


void ShadowMage::Update()
{
	if (!isdie)
	{
		// 방향 초기화
		MoveDir.x = 0.f;
		SetStatusInfo();
		CheckTargetWeapon();
		//cout << "detected : "  << detected << endl;
		//cout << "Do Attack : "  << DoAttack << endl << endl;

		// 시간 체크
		{
			delta = Time::Get()->WorldDelta();

			DetectPlayer();
			CheckDestination();

			if (isCheck)
			{
				CheckTime += delta;
			}
			else
				CheckTime = 0.f;

		}

		// 전처리
		{
			ControlState();

			for (ShadowMageSpell* s : ss)
			{
				s->Update();
			}
		}

		// 후처리
		{
			// 키입력 후 애니메이션 업데이트
			{
				animRect->Update(position, size, rotation);
				animator->Update();
			}

			Movement();

		}
	}
	else
	{
		soul->Update();

		if (Keyboard::Get()->Down('F'))
		{
			Init();
			_State = IDLE;
			isdie = false;
		}
	}



}

void ShadowMage::Render()
{
	if (!isdie)
	{
		animRect->Render();
		//collision->Render();
		//weapon_col->Render();
	}
	else
	{
		soul->Render();
	}

	for (ShadowMageSpell* s : ss)
	{
		s->Render();
	}
}

void ShadowMage::Init()
{
	soulPoint = rand() % 50 + 300;

	__super::Init();

	_State = IDLE;
}






ShadowStalker::ShadowStalker(Vector3 position, float rotation)
	:Monster(position, { 130,130,1 }, rotation)
{
	detectRange = 300.f;

	attackRange = 100.f;
	AttackDelay = 1.8f;
	s_attack_cooldown = 2.f;

	rigidbody = new RigidBody(*this);

	// Character Status
	{
		MoveSpeed = 1.f;
		AggroSpeed = 1.5f;

		jumpSpeed = 15.f;
	}

	// Animation
	{
		float Max_X = 17.f;
		float Max_Y = 11.f;

		Texture2D* srcTex = new Texture2D(TexturePath + L"shadowStalker(680_440).png");
		Texture2D* srcTex2 = new Texture2D(TexturePath + L"shadowStalker(reverse).png");

		Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

		Vector2 idle_f_s = Values::ZeroVec2;
		Vector2 idle_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (1.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 run_f_s = Vector2(0.f, texSize.y * (1.f / Max_Y));
		Vector2 run_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (2.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 aggro_f_s = Vector2(0.f, texSize.y * (2.f / Max_Y));
		Vector2 aggro_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (3.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 notaggro_f_s = Vector2(0.f, texSize.y * (3.f / Max_Y));
		Vector2 notaggro_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (4.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 arun_f_s = Vector2(0.f, texSize.y * (4.f / Max_Y));
		Vector2 arun_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (5.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 sattack1_f_s = Vector2(0.f, texSize.y * (5.f / Max_Y));
		Vector2 sattack1_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (6.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 attack_f_s = Vector2(0.f, texSize.y * (6.f / Max_Y));
		Vector2 attack_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (7.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 sattack2_f_s = Vector2(0.f, texSize.y * (7.f / Max_Y));
		Vector2 sattack2_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (8.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 damaged_f_s = Vector2(0.f, texSize.y * (8.f / Max_Y));
		Vector2 damaged_f_e = Vector2(texSize.x * (3.f / Max_X), texSize.y * (9.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 die_f_s = Vector2(0.f, texSize.y * (9.f / Max_Y));
		Vector2 die_f_e = Vector2(texSize.x * (17.f / Max_X), texSize.y * (10.f / Max_Y));

		////////////////////////////////////////////////////////////////////////////////

		Vector2 aidle_f_s = Vector2(0.f, texSize.y * (10.f / Max_Y));
		Vector2 aidle_f_e = Vector2(texSize.x * (4.f / Max_X), texSize.y * (11.f / Max_Y));




		// 24, 14

		AnimationClip* Idle_f = new AnimationClip(L"idle_f", srcTex, 4, Values::ZeroVec2, idle_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_f = new AnimationClip(L"run_f", srcTex, 4, run_f_s, run_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* aggro_f = new AnimationClip(L"aggro_f", srcTex, 4, aggro_f_s, aggro_f_e, false, 1.f / 3.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* notaggro_f = new AnimationClip(L"notaggro_f", srcTex, 4, notaggro_f_s, notaggro_f_e, false, 1.f / 3.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* arun_f = new AnimationClip(L"arun_f", srcTex, 4, arun_f_s, arun_f_e, false, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* sattack1_f = new AnimationClip(L"sattack1_f", srcTex, 4, sattack1_f_s, sattack1_f_e, false, 1.f / 3.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* attack_f = new AnimationClip(L"attack_f", srcTex, 4, attack_f_s, attack_f_e, false, 1.f / 4.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* sattack2_f = new AnimationClip(L"sattack2_f", srcTex, 4, sattack2_f_s, sattack2_f_e, false, 1.f / 4.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		AnimationClip* damaged_f = new AnimationClip(L"damaged_f", srcTex, 3, damaged_f_s, damaged_f_e, false, 1.f / 8.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_f = new AnimationClip(L"die_f", srcTex, 17, die_f_s, die_f_e, false, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* aIdle_f = new AnimationClip(L"aidle_f", srcTex, 4, aidle_f_s, aidle_f_e, false, 1.f / 6.f);



		animator->AddAnimClip(Idle_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(aggro_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(notaggro_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(arun_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(sattack1_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(attack_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(sattack2_f);
		////////////////////////////////////////////////////////////////////////////////

		animator->AddAnimClip(damaged_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_f);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(aIdle_f);


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//reverse
		AnimationClip* Idle_r = new AnimationClip(L"idle_r", srcTex2, 4, Values::ZeroVec2, idle_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* run_r = new AnimationClip(L"run_r", srcTex2, 4, run_f_s, run_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* aggro_r = new AnimationClip(L"aggro_r", srcTex2, 4, aggro_f_s, aggro_f_e, true, 1.f / 3.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* notaggro_r = new AnimationClip(L"notaggro_r", srcTex2, 4, notaggro_f_s, notaggro_f_e, true, 1.f / 3.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* arun_r = new AnimationClip(L"arun_r", srcTex2, 4, arun_f_s, arun_f_e, true, 1.f / 6.f);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* sattack1_r = new AnimationClip(L"sattack1_r", srcTex2, 4, sattack1_f_s, sattack1_f_e, true, 1.f / 3.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* attack_r = new AnimationClip(L"attack_r", srcTex2, 4, attack_f_s, attack_f_e, true, 1.f / 4.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* sattack2_r = new AnimationClip(L"sattack2_r", srcTex2, 4, sattack2_f_s, sattack2_f_e, true, 1.f / 4.5f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		AnimationClip* damaged_r = new AnimationClip(L"damaged_r", srcTex2, 3, damaged_f_s, damaged_f_e, true, 1.f / 8.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* die_r = new AnimationClip(L"die_r", srcTex2, 17, die_f_s, die_f_e, true, 1.f / 5.f, false);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		AnimationClip* aIdle_r = new AnimationClip(L"aidle_r", srcTex2, 4, aidle_f_s, aidle_f_e, true, 1.f / 6.f);


		animator->AddAnimClip(Idle_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(run_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(aggro_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(notaggro_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(arun_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(sattack1_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(attack_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(sattack2_r);
		////////////////////////////////////////////////////////////////////////////////

		animator->AddAnimClip(damaged_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(die_r);
		////////////////////////////////////////////////////////////////////////////////
		animator->AddAnimClip(aIdle_r);


		animator->SetCurrentAnimClip(L"idle_f");

		animRect->SetAnimator(animator);

		rigidbody = new RigidBody(*this);


		SAFE_DELETE(srcTex);
		SAFE_DELETE(srcTex2);

	}

	// Collision
	{
		collision = new BoundingBox(BoundingBox::Monster);
		collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

		weapon_col = new BoundingBox(BoundingBox::MonsterWeapon);
		weapon_col->Init(Color(0, 1, 0, 0.3f), BoundingBox::DOWN_CENTER);
		weapon_col->SetActive(false);
	}

	Init();
}

ShadowStalker::~ShadowStalker()
{
	SAFE_DELETE(weapon_col);
	SAFE_DELETE(collision);
	SAFE_DELETE(rigidbody);
}

void ShadowStalker::ControlState()
{
	// 움직이고 있는지 off
	// 움직일수 있는지 off
	// 입력할수 있는지 초기화 x
	SetInputStateOff(IsMove | bInput | bMove);
	// 현재 상태에 따른 입력값을 받아와서 상태를 변경

	Damaged();

	switch (_State)
	{
	case ShadowStalker::IDLE:
		collision->SetActive(true);
		weapon_col->SetActive(false);

		TimeDelay = WalkDelay;

		Run();

		Aggro();

		break;

	case ShadowStalker::RUN:
		TimeDelay = WalkDelay;

		Run();

		Aggro();

		break;

	case ShadowStalker::AGGROIDLE:
		collision->SetActive(true);
		weapon_col->SetActive(false);

		TimeDelay = AttackDelay;

		AggroRun();
		Attack();
		S_Attack();

		DeAggro();

		break;

	case ShadowStalker::AGGRO:

		break;

	case ShadowStalker::NOT_AGGRO:

		break;


	case ShadowStalker::AGGROWALK:
		TimeDelay = AttackDelay;

		AggroRun();
		Attack();
		S_Attack();

		DeAggro();

		break;

	case ShadowStalker::ATTACK:
		TimeDelay = AttackDelay;

		Attack();

		break;

	case ShadowStalker::SATTACK:
		TimeDelay = AttackDelay;

		S_Attack();

		break;

	case ShadowStalker::DAMAGED:

		break;

	case ShadowStalker::DIE:

		break;

	case ShadowStalker::DEFAULT:
		_State = IDLE;

		break;

	}


	AnimState();
}

void ShadowStalker::AnimState()
{
	DecreaseAccel();

	//cout << _State << endl;

	switch (_State)
	{
	case ShadowStalker::IDLE:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"idle_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"idle_f");

		if (CheckTime > TimeDelay)
			isCheck = false;

		break;

	case ShadowStalker::RUN:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"run_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"run_f");

		break;

	case ShadowStalker::AGGROIDLE:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"aidle_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"aidle_f");

		if (CheckTime > TimeDelay)
			isCheck = false;

		break;

	case ShadowStalker::AGGRO:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"aggro_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"aggro_f");

		MoveSpeed = AggroSpeed;

		if (animator->IsEnd())
			_State = AGGROIDLE;

		break;

	case ShadowStalker::NOT_AGGRO:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"notaggro_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"notaggro_f");

		MoveSpeed = 1.f;

		if (animator->IsEnd())
			_State = IDLE;

		break;

	case ShadowStalker::AGGROWALK:

		if (dir == -1.f)
			animator->SetCurrentAnimClip(L"arun_r");
		else if (dir == 1.f)
			animator->SetCurrentAnimClip(L"arun_f");

		break;

	case ShadowStalker::ATTACK:
		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"attack_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"attack_f");
		}

		weapon_col->SetDamage(_status.currentAtk * 1.f);
		weapon_col->SetDir(dir);
		weapon_col->SetAtkType(KNOCKBACK);

		ShadowStalker::OnWeaponCollision(3, 4, { dir * (collision->GetSize().x * 1.1f),  35.f, 0.f }, { size.x / 1.5f , size.y / 5.f, 1.f });

		if (animator->IsEnd())
		{
			oldDoAttack = DoAttack;
			DoAttack = false;
			_State = AGGROIDLE;
		}

		break;

	case ShadowStalker::SATTACK:

		if (satk_stack == 0)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"sattack1_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"sattack1_f");
			}

			weapon_col->SetDamage(_status.currentAtk * 1.f);
			weapon_col->SetDir(dir);
			weapon_col->SetAtkType(GRAB);

			ShadowStalker::OnWeaponCollision(3, 4, { dir * (collision->GetSize().x * 1.5f),  30.f, 0.f }, { size.x / 2.2f , size.y / 3.f, 1.f });

			if(animator->IsEnd())
				satk_stack++;
			
		}
		else if (satk_stack == 1)
		{
			if (dir == -1.f)
			{
				animator->SetCurrentAnimClip(L"sattack2_r");
			}
			else if (dir == 1.f)
			{
				animator->SetCurrentAnimClip(L"sattack2_f");
			}

			weapon_col->SetDamage(_status.currentAtk * 1.2f);
			weapon_col->SetDir(dir);
			weapon_col->SetAtkType(RISE_UP);

			ShadowStalker::OnWeaponCollision(3, 4, { dir * (collision->GetSize().x * 1.1f),  30.f, 0.f }, { size.x / 1.9f , size.y / 3.f, 1.f });

			if (animator->IsEnd())
			{
				satk_stack = 0;

				oldDoAttack = DoAttack;
				DoAttack = false;

				_State = AGGROIDLE;
			}
		}

		break;

	case ShadowStalker::DAMAGED:

		weapon_col->SetActive(false);

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"damaged_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"damaged_f");
		}

		if (animator->IsEnd() && CheckState(IsGround))
		{
			if (prevState == SATTACK)
			{
				_State = prevState;
			}
			else
				_State = AGGROIDLE;
		}

		break;

	case ShadowStalker::DIE:

		collision->SetActive(false);
		weapon_col->SetActive(false);

		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"die_r");
		}
		else if (dir == 1.f)
		{
			animator->SetCurrentAnimClip(L"die_f");
		}

		if (animator->IsEnd())
		{
			isdie = true;
		}

		break;

	default:
		break;
	}
}


void ShadowStalker::Col_Update()
{
	collision->Update({ position.x , position.y, position.z }, { size.x / 3.5f , size.y / 1.4f, size.z }, rotation);
	weapon_col->Update(position + weaponPos, weaponSize, 0.0f);
}


void ShadowStalker::Run()
{
	if (!isCheck)
	{
		//dir = playerDir;
		if (!detected)
		{
			_State = RUN;
			MoveDir.x = MoveSpeed * dir;
		}
	}
	else
		_State = IDLE;
}

void ShadowStalker::Aggro()
{
	if (detected)
		_State = AGGRO;
}

void ShadowStalker::DeAggro()
{
	if (!detected)
		_State = NOT_AGGRO;
}

void ShadowStalker::AggroRun()
{
	if (!isCheck)
	{
		//dir = playerDir;
		
		dir = playerDir;
		if (!DoAttack)
		{
			_State = AGGROWALK;
			MoveDir.x = AggroSpeed * dir;
		}
	}
	else
		_State = AGGROIDLE;
}

void ShadowStalker::Attack()
{
	if (detected)
	{
		if (!isCheck)
		{
			if (DoAttack)
			{
				if (oldDoAttack == false)
					dir = playerDir;
				MoveDir.x = 0.f;
				isCheck = true;
				TimeDelay = AttackDelay;
				_State = ATTACK;
			}
		}
	}
}

void ShadowStalker::S_Attack()
{
	if (bSpecialAttack && detected)
	{
		if (DoAttack)
		{
			if (oldDoAttack == false)
				dir = playerDir;
			MoveDir.x = 0.f;
			isCheck = true;
			TimeDelay = AttackDelay;
			_State = SATTACK;
			bSpecialAttack = false;
		}


	}
}




void ShadowStalker::Damaged()
{
	vector<BoundingBox*> weapon = BoundingBox::GetTagCollision(BoundingBox::Weapon);

	for (auto w : weapon)
	{
		if (BoundingBox::OBB(collision, w))
		{
			if (w != TargetWeapon)
			{
				olddetected = detected;
				detected = true;
				detectedTime = 0.f;

				SetTargetWeapon(w);
				if ((_status.currentHp - w->GetDamage()) <= 0.f)
				{
					_status.currentHp = 0.f;
					_State = DIE;
					soul->OnIsActive(position);
					cout << "ShadowStalker HP : " << _status.currentHp << endl;
				}
				else
				{
					if (_State == SATTACK)
					{
						prevState = _State;
					}
					else
					{
						prevState = IDLE;
					}

					DamageReaction(w->GetAtkType(), w->GetDir());
					_status.currentHp -= w->GetDamage();
					_State = DAMAGED;
					cout << "ShadowStalker HP : " << _status.currentHp << endl;
				}

			}

		}
	}
}


void ShadowStalker::Update()
{
	if (!isdie)
	{
		// 방향 초기화
		MoveDir.x = 0.f;
		SetStatusInfo();
		CheckTargetWeapon();

		// 시간 체크
		{
			delta = Time::Get()->WorldDelta();

			DetectPlayer();
			CheckDestination();

			if (isCheck)
			{
				CheckTime += delta;
			}
			else
				CheckTime = 0.f;

		}

		// 전처리
		{
			ControlState();
		}

		// 후처리
		{
			// 키입력 후 애니메이션 업데이트
			{
				animRect->Update({ position.x + (dir * size.x / 9.f), position.y, position.z }, size, rotation);
				animator->Update();
			}

			Movement();

		}
	}
	else
	{
		soul->Update();

		if (Keyboard::Get()->Down('F'))
		{
			Init();
		}
	}



}

void ShadowStalker::Render()
{
	if (!isdie)
	{
		//collision->Render();
		animRect->Render();
		//weapon_col->Render();
	}
	else
	{
		soul->Render();
	}

}

void ShadowStalker::Init()
{
	soulPoint = rand() % 50 + 200;

	__super::Init();

	_State = IDLE;
}








Monster::Monster(Vector3 position, Vector3 size, float rotation)
	:Character(position,size,rotation)
{

	StartPosition = position;

	detectRange = 200.f;
	attackRange = 100.f;
	s_attack_cooldown = 10.f;

	WalkDelay = 1.5f;
	AttackDelay = 2.f;

	soul = new Soul(position, 0);

}

Monster::~Monster()
{
	SAFE_DELETE(soul);
}

void Monster::Init()
{
	SetStatusInfo();

	collision->SetActive(false);
	weapon_col->SetActive(false);

	position = StartPosition;

	_status.currentHp = _status.MaxHp;

	detectDistance = 0.f;
	detected = false;
	olddetected = false;

	oldDoAttack = false;
	DoAttack = false;

	playerDir = 1.f;

	s_cooltime = 0.f;
	bSpecialAttack = true;

	TimeDelay = 0.f;

	isdie = false;

	soul->Init(position, soulPoint);
	SetDestination();
}

void Monster::OnActive()
{
	collision->SetActive(true);
}

// 몬스터 Ai 중추
void Monster::DetectPlayer()
{
	vector<BoundingBox*> player = BoundingBox::GetTagCollision(BoundingBox::Player);

	if (!bSpecialAttack)
	{
		s_cooltime += delta;

		if (s_cooltime > s_attack_cooldown)
		{
			bSpecialAttack = true;
			s_cooltime = 0.f;
		}
	}

	detectDistance = D3DXVec3Length(&(position - player[0]->GetData()->centerPos));

	if (abs(detectDistance) < detectRange && player[0]->GetIsActive() == true && (position.y - player[0]->GetSize().y) < player[0]->GetPosition().y 
		&& !isleftnull && !isrightnull)
	{
		detectedTime = 0.f;

		if (isside == false)
		{
			olddetected = detected;
			detected = true;

			CheckDetectCoolTime = 0.f;
			Destination = player[0]->GetData()->centerPos;
		}
		else
		{
			CheckDetectCoolTime += delta;
			if (CheckDetectCoolTime > 3.f)
				isside = false;
		}
	}
	else
	{
		if (detected)
		{
			detectedTime += delta;
			if (detectedTime > 3.f)
			{
				olddetected = detected;
				detected = false;
			}
		}
		
	}

	if (isleftnull || isrightnull)
	{
		olddetected = detected;
		detected = false;
	}
	else if(!isleftnull && !isrightnull)
		isnullok = true;

	if (abs(detectDistance) < attackRange)
	{
		oldDoAttack = DoAttack;
		DoAttack = true;
	}
	else
	{
		oldDoAttack = DoAttack;
		DoAttack = false;
	}

	if (detected)
	{
		if ((position.x - player[0]->GetData()->centerPos.x) > 0.f)
			playerDir = -1.f;
		else
			playerDir = 1.f;
	}
}

void Monster::SetDestination()
{
	if (detected)
		return;
	
	// -100 ~ 100 까지의 랜덤 정수
	float randPos = (rand() % 200) - 100;
	Destination = { StartPosition.x + randPos, StartPosition.y, StartPosition.z };

	if ((position.x - Destination.x) >= 0.f)
		dir = -1.f;
	else
		dir = 1.f;
	
}

void Monster::CheckDestination()
{
	if (detected)
		return;

	if ((rigidbody->CheckSide() || (position.x - Destination.x) * dir >= 0.f ))
	{

		if (((isleftnull || isrightnull) && isnullok))
		{
			isside = true;
		}
		isCheck = true;
		isnullok = false;
		TimeDelay = WalkDelay;
		SetDestination();
	}
}


void Monster::Col_Update()
{
	collision->Update({ position.x , position.y, position.z }, { size.x , size.y , size.z }, rotation);
	weapon_col->Update(position + weaponPos, weaponSize, 0.0f);
}

void Monster::Movement()
{
	// collision Update
	{
		Col_Update();
	}

	MoveDir.x = (MoveDir.x * MoveSpeed) + AccelMove;
	rigidbody->Update();

	landGround = (CheckInputState(IsGround) && (Old_InputState & IsGround) == None) ? true : false;
	WallStart = (CheckInputState(IsWall) && (Old_InputState & IsWall) == None) ? true : false;

	isleftnull = rigidbody->IsLeftDownNull();
	isrightnull = rigidbody->IsRightDownNull();

	position += MoveDir;
}
