#include "Framework.h"
#include "MonsterObject.h"

BringerSpell::BringerSpell(Vector3 position, float rotation, float damage, float dir)
	:GameObject(position, { 350,330,1 }, rotation)
{

	spell = new AnimationRect(position, size, rotation, DOWN_CENTER);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"bringer_spell.png");
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"bringer_spell(reverse).png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());


	AnimationClip* DarkHand_f = new AnimationClip(L"DarkHand_f", srcTex, 16, Values::ZeroVec2, texSize, false, 1.f / 50.f, false);
	AnimationClip* DarkHand_r = new AnimationClip(L"DarkHand_r", srcTex2, 16, Values::ZeroVec2, texSize, true, 1.f / 50.f, false);

	animator->AddAnimClip(DarkHand_f);
	animator->AddAnimClip(DarkHand_r);

	SAFE_DELETE(srcTex);
	SAFE_DELETE(srcTex2);

	collision = new BoundingBox(BoundingBox::MonsterWeapon);
	collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

	animator->SetCurrentAnimClip(L"DarkHand_f");

	Init(position, rotation, damage, dir);
}

BringerSpell::~BringerSpell()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(animator);
	SAFE_DELETE(spell);
}

void BringerSpell::Init(Vector3 position, float rotation, float damage, float dir)
{
	this->position = position;
	this->rotation = rotation;

	SetIsActive(GameObject::ON);
	collision->SetActive(false);

	collision->SetDamage(damage);
	collision->SetDir(dir);
	collision->SetAtkType(Attack::KNOCKBACK);


	if (dir == 1.f)
	{
		animator->SetCurrentAnimClip(L"DarkHand_f");
		animator->SetCurrentFrameIndex(0);
	}
	else if (dir == -1.f)
	{
		animator->SetCurrentAnimClip(L"DarkHand_r");
		animator->SetCurrentFrameIndex(0);
	}
	spell->SetAnimator(animator);


}

void BringerSpell::Update()
{
	if (!(_activeState[1] == ON))
		return;

	//OnIsActive();

	collision->Update(position, { size.x / 5.f, size.y / 1.5f, size.z }, rotation);

	if (animator->CheckFrameIndex(8))
	{
		collision->SetActive(true);
	}

	if (animator->CheckFrameIndex(11))
	{
		collision->SetActive(false);
	}
	
	if (animator->IsEnd())
	{
		_activeState[1] = OFF;
	}

	spell->Update(position, size, rotation);


}

void BringerSpell::Render()
{
	if (!_activeState[1])
		return;

	spell->Render();
	//collision->Render();
}


void BringerSpell::OnIsActive()
{
	if (!(_activeState[0] == OFF) || !(_activeState[1] == ON))
		return;

	{
		// 활성화할 시 사용할 코드

	}

	_activeState[1] = ON;
}



ShadowMageSpell::ShadowMageSpell(Vector3 position, float rotation, float damage, float dir)
	:GameObject(position, { 100,100,1 }, rotation)
{

	spell = new AnimationRect(position, size, rotation, DOWN_CENTER);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"shadowMage_spell.png");
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"shadowMage_spell(reverse).png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());


	AnimationClip* Spike_f = new AnimationClip(L"Spike_f", srcTex, 7, Values::ZeroVec2, texSize, false, 1.f / 25.f, false);
	AnimationClip* Spike_r = new AnimationClip(L"Spike_r", srcTex2, 7, Values::ZeroVec2, texSize, true, 1.f / 25.f, false);

	animator->AddAnimClip(Spike_f);
	animator->AddAnimClip(Spike_r);

	SAFE_DELETE(srcTex);
	SAFE_DELETE(srcTex2);

	collision = new BoundingBox(BoundingBox::MonsterWeapon);
	collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

	animator->SetCurrentAnimClip(L"Spike_f");

	Init(position, rotation, damage, dir);
}

ShadowMageSpell::~ShadowMageSpell()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(animator);
	SAFE_DELETE(spell);
}

void ShadowMageSpell::Init(Vector3 position, float rotation, float damage, float dir)
{
	this->position = position;
	this->rotation = rotation;
	this->dir = dir;

	SetIsActive(GameObject::ON);
	collision->SetActive(false);

	collision->SetDamage(damage);
	collision->SetDir(dir);
	collision->SetAtkType(Attack::RISE_UP);


	if (dir == 1.f)
	{
		animator->SetCurrentAnimClip(L"Spike_f");
		animator->SetCurrentFrameIndex(0);
	}
	else if (dir == -1.f)
	{
		animator->SetCurrentAnimClip(L"Spike_r");
		animator->SetCurrentFrameIndex(0);
	}
	spell->SetAnimator(animator);


}

void ShadowMageSpell::Update()
{
	if (!(_activeState[1] == ON))
		return;

	//OnIsActive();

	collision->Update({position.x + (-dir) * 30.f, position.y + 20.f, position.z}, { size.x / 3.f , size.y, size.z }, dir * -45.f);

	if (animator->CheckFrameIndex(3))
	{
		collision->SetActive(true);
	}

	if (animator->CheckFrameIndex(5))
	{
		collision->SetActive(false);
	}

	if (animator->IsEnd())
	{
		_activeState[1] = OFF;
	}

	spell->Update(position, size, rotation);


}

void ShadowMageSpell::Render()
{
	if (!_activeState[1])
		return;

	spell->Render();
	//collision->Render();
}


void ShadowMageSpell::OnIsActive()
{
	if (!(_activeState[0] == OFF) || !(_activeState[1] == ON))
		return;

	{
		// 활성화할 시 사용할 코드

	}

	_activeState[1] = ON;
}





Soul::Soul(Vector3 position, float point)
	:GameObject(position, { 50,50,1 }, 0.f)
{

	soul = new AnimationRect(position, size, rotation, DOWN_CENTER);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"Soul.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	Vector2 soul_f_s = Values::ZeroVec2;
	Vector2 soul_f_e = Vector2(texSize.x, texSize.y * (1.f / 3.f));

	////////////////////////////////////////////////////////////////////////////////

	Vector2 soul_r_s = Vector2(0.f, texSize.y * (1.f / 3.f));
	Vector2 soul_r_e = Vector2(texSize.x, texSize.y * (2.f / 3.f));

	////////////////////////////////////////////////////////////////////////////////

	Vector2 get_soul_s = Vector2(0.f, texSize.y * (2.f / 3.f));
	Vector2 get_soul_e = Vector2(texSize.x * (2.f / 3.f), texSize.y);

	AnimationClip* Soul_f = new AnimationClip(L"Soul_f", srcTex, 3, soul_f_s, soul_f_e, false, 1.f / 8.f, false);
	AnimationClip* Soul_r = new AnimationClip(L"Soul_r", srcTex, 3, soul_r_s, soul_r_e, true, 1.f / 8.f, false);
	AnimationClip* Get_Soul = new AnimationClip(L"Get_Soul", srcTex, 2, get_soul_s, get_soul_e, false, 1.f / 20.f, false);

	animator->AddAnimClip(Soul_f);
	animator->AddAnimClip(Soul_r);
	animator->AddAnimClip(Get_Soul);

	SAFE_DELETE(srcTex);

	collision = new BoundingBox(BoundingBox::Item);
	collision->Init(Color(1, 0, 0, .3f), BoundingBox::DOWN_CENTER);

	animator->SetCurrentAnimClip(L"Soul_f");

	Init(position, point);
}

Soul::~Soul()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(animator);
	SAFE_DELETE(soul);
}

void Soul::Init(Vector3 position, float point)
{
	this->position = position;
	this->point = point;

	SetIsActive(GameObject::OFF);
	collision->SetActive(false);
}

void Soul::Update()
{
	if (!(_activeState[1]))
		return;


	vector<BoundingBox*> player = BoundingBox::GetTagCollision(BoundingBox::Player);

	Vector3 dir = player[0]->GetPosition() - position;
	D3DXVec3Normalize(&dir, &dir);

	Speed += .1f;

	position += dir * Speed;

	if (BoundingBox::OBB(collision, player[0]))
	{
		_State = GET;

	}

	switch (_State)
	{
	case Soul::NORMAL:
		animator->SetCurrentAnimClip(L"Soul_f");

		if (animator->IsEnd())
			_State = REVERSE;

		break;
	case Soul::REVERSE:
		animator->SetCurrentAnimClip(L"Soul_r");

		if (animator->IsEnd())
			_State = NORMAL;
		break;
	case Soul::GET:
		animator->SetCurrentAnimClip(L"Get_Soul");

		if (animator->IsEnd())
		{
			_activeState[1] = OFF;
			PlayerStatus::Get()->PlusSoulPoint(point);
			Sounds::Get()->Play("Coin", 0.5f);
		}

		break;
	default:
		break;
	}


	soul->Update(position, size, rotation);
	collision->Update({ position.x, position.y + size.y / 4.f, position.z }, { size.x / 2.f , size.y / 2.f, size.z }, 0.f);

}

void Soul::Render()
{
	if (!_activeState[1])
		return;

	soul->Render();
	//collision->Render();
}


void Soul::OnIsActive(Vector3 position)
{
	_activeState[1] = ON;

	this->position = position;

	_State = NORMAL;
	animator->SetCurrentAnimClip(L"Soul_f");
	animator->SetCurrentFrameIndex(0);
	soul->SetAnimator(animator);

	Speed = 0;

	collision->SetActive(true);
}