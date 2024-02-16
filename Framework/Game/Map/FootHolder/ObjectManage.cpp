#include "Framework.h"
#include "ObjectManage.h"



CrystalMoveFloor::CrystalMoveFloor(Vector3 position, float dir)
	:FootHolder(position, {40, 80, 1.f}, 0.f)
{
	ar = new AnimationRect(position, size, rotation);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"Crystal.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	Vector2 OFF_s = Values::ZeroVec2;
	Vector2 OFF_e = Vector2(texSize.x, texSize.y * (1.f / 2.f));

	////////////////////////////////////////////////////////////////////////////////

	Vector2 ON_s = Vector2(0.f, texSize.y * (1.f / 2.f));
	Vector2 ON_e = Vector2(texSize.x, texSize.y);

	////////////////////////////////////////////////////////////////////////////////

	AnimationClip* OFF = new AnimationClip(L"OFF", srcTex, 6, OFF_s, OFF_e, false, 1.f / 4.f);
	AnimationClip* ON = new AnimationClip(L"ON", srcTex, 6, ON_s, ON_e, false, 1.f / 4.f);

	animator->AddAnimClip(OFF);
	animator->AddAnimClip(ON);

	animator->SetCurrentAnimClip(L"OFF");
	ar->SetAnimator(animator);

	mf = new MoveFloor({ position.x + (80 * dir), position.y - 105, position.z }, dir, true);

	SAFE_DELETE(srcTex);

	collision = new BoundingBox(BoundingBox::Trigger);
	collision->Init(Color(1, 0, 0, 0.1f), BoundingBox::MIDLE_CENTER);

}

CrystalMoveFloor::~CrystalMoveFloor()
{
	SAFE_DELETE(mf);
	SAFE_DELETE(animator);
	SAFE_DELETE(ar);
}

void CrystalMoveFloor::Trigger()
{
	vector<BoundingBox*> weapon = BoundingBox::GetTagCollision(BoundingBox::Weapon);

	for (BoundingBox* w : weapon)
	{
		if (BoundingBox::OBB(collision, w))
		{
			animator->SetCurrentAnimClip(L"ON");
			collision->SetActive(false);
			mf->SetTrigger(true);

		}
	}

	if (mf->GetMoveStack() > 1)
	{
		animator->SetCurrentAnimClip(L"OFF");
		collision->SetActive(true);
		mf->SetTrigger(false);
		mf->SetMoveStack(0);

		mf->GetCollision()->SetFSpeed(0.f);
	}
}

void CrystalMoveFloor::Update()
{
	animator->Update();
	ar->Update(position, size, rotation);
	collision->Update(position, size, rotation);

	mf->Update();

	Trigger();
}

void CrystalMoveFloor::Render()
{
	ar->Render();
	mf->Render();
	//collision->Render();
}

void CrystalMoveFloor::Init()
{
	animator->SetCurrentAnimClip(L"OFF");
	collision->SetActive(false);
	mf->SetTrigger(false);
	mf->SetMoveStack(0);

	mf->GetCollision()->SetFSpeed(0.f);

	mf->Init();
}

void CrystalMoveFloor::OnActive()
{
	collision->SetActive(true);
	mf->OnActive();
}





CrystalUpDownFloor::CrystalUpDownFloor(Vector3 position, float dir)
	:FootHolder(position, { 40, 80, 1.f }, 0.f)
{
	ar = new AnimationRect(position, size, rotation);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"Crystal.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	Vector2 OFF_s = Values::ZeroVec2;
	Vector2 OFF_e = Vector2(texSize.x, texSize.y * (1.f / 2.f));

	////////////////////////////////////////////////////////////////////////////////

	Vector2 ON_s = Vector2(0.f, texSize.y * (1.f / 2.f));
	Vector2 ON_e = Vector2(texSize.x, texSize.y);

	////////////////////////////////////////////////////////////////////////////////

	AnimationClip* OFF = new AnimationClip(L"OFF", srcTex, 6, OFF_s, OFF_e, false, 1.f / 4.f);
	AnimationClip* ON = new AnimationClip(L"ON", srcTex, 6, ON_s, ON_e, false, 1.f / 4.f);

	animator->AddAnimClip(OFF);
	animator->AddAnimClip(ON);

	animator->SetCurrentAnimClip(L"OFF");
	ar->SetAnimator(animator);

	udf = new UpDownFloor({ position.x + (80 * dir), position.y - 50.f, position.z }, true);

	SAFE_DELETE(srcTex);

	collision = new BoundingBox(BoundingBox::Trigger);
	collision->Init(Color(1, 0, 0, 0.1f), BoundingBox::MIDLE_CENTER);

}

CrystalUpDownFloor::~CrystalUpDownFloor()
{
	SAFE_DELETE(udf);
	SAFE_DELETE(animator);
	SAFE_DELETE(ar);
}

void CrystalUpDownFloor::Trigger()
{
	vector<BoundingBox*> weapon = BoundingBox::GetTagCollision(BoundingBox::Weapon);

	for (BoundingBox* w : weapon)
	{
		if (BoundingBox::OBB(collision, w))
		{
			animator->SetCurrentAnimClip(L"ON");
			collision->SetActive(false);
			udf->SetTrigger(true);

		}
	}

	if (udf->GetMoveStack() > 1)
	{
		animator->SetCurrentAnimClip(L"OFF");
		collision->SetActive(true);
		udf->SetTrigger(false);
		udf->SetFirst();
		udf->SetMoveStack(0);
		udf->GetCollision()->SetFYSpeed(0.f);
	}
}

void CrystalUpDownFloor::Update()
{
	animator->Update();
	ar->Update(position, size, rotation);
	collision->Update(position, size, rotation);

	udf->Update();

	Trigger();

}

void CrystalUpDownFloor::Render()
{
	ar->Render();
	udf->Render();
	//collision->Render();
}

void CrystalUpDownFloor::Init()
{
	animator->SetCurrentAnimClip(L"OFF");
	collision->SetActive(false);
	udf->SetTrigger(false);
	udf->SetFirst();
	udf->SetMoveStack(0);
	udf->GetCollision()->SetFYSpeed(0.f);

	udf->Init();
}

void CrystalUpDownFloor::OnActive()
{
	collision->SetActive(true);
	udf->SetFirst();
	udf->OnActive();
}





Portal::Portal(Vector3 position, float dir)
	: FootHolder(position, {150.f, 150.f, 1.f}, 0.f)
{
	this->dir = dir;

	ar = new AnimationRect(position, size, rotation, DOWN_CENTER);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"PurplePortal(512_192).png");
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"PurplePortal(reverse).png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	Vector2 continue_portal_s = Values::ZeroVec2;
	Vector2 continue_portal_e = Vector2(texSize.x, texSize.y * (1.f / 3.f));

	////////////////////////////////////////////////////////////////////////////////

	Vector2 on_portal_s = Vector2(0.f, texSize.y * (1.f / 3.f));
	Vector2 on_portal_e = Vector2(texSize.x, texSize.y * (2.f / 3.f));

	////////////////////////////////////////////////////////////////////////////////

	AnimationClip* continue_portal_f = new AnimationClip(L"continue_portal_f", srcTex, 8, continue_portal_s, continue_portal_e, false, 1.f / 15.f);
	AnimationClip* on_portal_f = new AnimationClip(L"on_portal_f", srcTex, 8, on_portal_s, on_portal_e, false, 1.f / 15.f, false);

	AnimationClip* continue_portal_r = new AnimationClip(L"continue_portal_r", srcTex2, 8, continue_portal_s, continue_portal_e, true, 1.f / 15.f);
	AnimationClip* on_portal_r = new AnimationClip(L"on_portal_r", srcTex2, 8, on_portal_s, on_portal_e, true, 1.f / 15.f, false);

	animator->AddAnimClip(continue_portal_f);
	animator->AddAnimClip(on_portal_f);

	animator->AddAnimClip(continue_portal_r);
	animator->AddAnimClip(on_portal_r);

	animator->SetCurrentAnimClip(L"on_portal_r");
	ar->SetAnimator(animator);

	tr = new TextureRect(position, size, rotation, TexturePath + L"E_down.png", DOWN_CENTER);
	

	SAFE_DELETE(srcTex2);
	SAFE_DELETE(srcTex);

	collision = new BoundingBox(BoundingBox::Object);
	collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);

}

Portal::~Portal()
{
	SAFE_DELETE(collision)
	SAFE_DELETE(tr)

	SAFE_DELETE(animator)
	SAFE_DELETE(ar)
}

void Portal::StateControll()
{
	switch (_state)
	{
	case Portal::ON_PORTAL:
		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"on_portal_r");
		}
		else
			animator->SetCurrentAnimClip(L"on_portal_f");

		if (animator->IsEnd())
			_state = CONTINUE;

		break;
	case Portal::CONTINUE:
		if (dir == -1.f)
		{
			animator->SetCurrentAnimClip(L"continue_portal_r");
		}
		else
			animator->SetCurrentAnimClip(L"continue_portal_f");

		break;
	default:
		break;
	}
}

void Portal::Update()
{
	/*if (Keyboard::Get()->Down('E'))
	{
		SetOn();
	}*/

	if (isOn)
	{
		StateControll();

		ar->Update({ position.x, position.y - 10.f, position.z }, size, rotation);
		collision->Update({ position.x, position.y + 10.f, position.z }, { size.x / 2.5f, size.y / 1.5f, size.z }, rotation);
		tr->Update({ position.x, position.y + size.y / 1.3f, position.z }, { 30.f,30.f,1.f }, 0.f);

		vector<BoundingBox*> player = BoundingBox::GetTagCollision(BoundingBox::Player);

		isDetect = false;
		if (BoundingBox::OBB(player[0], collision))
			isDetect = true;


		if (isDetect)
		{
			if (Keyboard::Get()->Down('E'))
			{
				Sounds::Get()->Play("warp");
				isnext = true;
			}
		}
	}

}

void Portal::Render()
{
	if (isOn)
	{
		ar->Render();
		//collision->Render();

		if (isDetect)
		{
			tr->Render();
		}
	}
}

void Portal::Init()
{
	collision->SetActive(false);

	isnext = false;
	isOn = false;

	_state = ON_PORTAL;
}

void Portal::OnActive()
{
	collision->SetActive(true);
}



BigTree1::BigTree1(Vector3 position)
	:FootHolder(position, { 256, 368, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"BigTree1(256_368).png", DOWN_CENTER);

	tr->Update(position, size, rotation);
}

BigTree1::~BigTree1()
{
	SAFE_DELETE(tr);
}

void BigTree1::Update()
{
}

void BigTree1::Render()
{
	tr->Render();
}

void BigTree1::Init()
{
}

void BigTree1::OnActive()
{
	tr->Update(position, size, rotation);
}


BigTree2::BigTree2(Vector3 position)
	:FootHolder(position, { 256, 368, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"BigTree2(256_368).png", DOWN_CENTER);

	tr->Update(position, size, rotation);
}

BigTree2::~BigTree2()
{
	SAFE_DELETE(tr);
}

void BigTree2::Update()
{
}

void BigTree2::Render()
{
	tr->Render();
}

void BigTree2::Init()
{
}

void BigTree2::OnActive()
{
	tr->Update(position, size, rotation);
}


BigTree3::BigTree3(Vector3 position)
	:FootHolder(position, { 304, 368, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"BigTree3(304_368).png", DOWN_CENTER);

	tr->Update(position, size, rotation);
}

BigTree3::~BigTree3()
{
	SAFE_DELETE(tr);
}

void BigTree3::Update()
{
}

void BigTree3::Render()
{
	tr->Render();
}

void BigTree3::Init()
{
}

void BigTree3::OnActive()
{
	tr->Update(position, size, rotation);
}


SmallTree1::SmallTree1(Vector3 position)
	:FootHolder(position, { 224, 320, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"SmallTree1(112_160).png", DOWN_CENTER);

	tr->Update(position, size, rotation);
}

SmallTree1::~SmallTree1()
{
	SAFE_DELETE(tr);
}

void SmallTree1::Update()
{
}

void SmallTree1::Render()
{
	tr->Render();
}

void SmallTree1::Init()
{
}

void SmallTree1::OnActive()
{
	tr->Update(position, size, rotation);
}


SmallTree2::SmallTree2(Vector3 position)
	:FootHolder(position, { 160, 224, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"SmallTree2(80_112).png", DOWN_CENTER);

	tr->Update(position, size, rotation);
}

SmallTree2::~SmallTree2()
{
	SAFE_DELETE(tr);
}

void SmallTree2::Update()
{
}

void SmallTree2::Render()
{
	tr->Render();
}

void SmallTree2::Init()
{
}

void SmallTree2::OnActive()
{
	tr->Update(position, size, rotation);
}


SmallTree3::SmallTree3(Vector3 position)
	:FootHolder(position, { 192, 256, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"SmallTree3(96_128).png", DOWN_CENTER);

	tr->Update(position, size, rotation);
}

SmallTree3::~SmallTree3()
{
	SAFE_DELETE(tr);
}

void SmallTree3::Update()
{
}

void SmallTree3::Render()
{
	tr->Render();
}

void SmallTree3::Init()
{
}

void SmallTree3::OnActive()
{
	tr->Update(position, size, rotation);
}


Root1::Root1(Vector3 position)
	:FootHolder(position, { 192, 128, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"Root1(96_64).png", UP_RIGHT);

	tr->Update(position, size, rotation);
}

Root1::~Root1()
{
	SAFE_DELETE(tr);
}

void Root1::Update()
{
}

void Root1::Render()
{
	tr->Render();
}

void Root1::Init()
{
}

void Root1::OnActive()
{
	tr->Update(position, size, rotation);
}


Root2::Root2(Vector3 position)
	:FootHolder(position, { 64, 160, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"Root2(32_80).png", UP_CENTER);

	tr->Update(position, size, rotation);
}

Root2::~Root2()
{
	SAFE_DELETE(tr);
}

void Root2::Update()
{
}

void Root2::Render()
{
	tr->Render();
}

void Root2::Init()
{
}

void Root2::OnActive()
{
	tr->Update(position, size, rotation);
}


Root3::Root3(Vector3 position)
	:FootHolder(position, { 192, 128, 0.f }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"Root3(96_64).png", UP_LEFT);

	tr->Update(position, size, rotation);
}

Root3::~Root3()
{
	SAFE_DELETE(tr);
}

void Root3::Update()
{
}

void Root3::Render()
{
	tr->Render();
}

void Root3::Init()
{
}

void Root3::OnActive()
{
	tr->Update(position, size, rotation);
}




Shop::Shop(Vector3 position)
	:FootHolder(position, { 300,300,1 }, 0.f)
{
	ar = new AnimationRect(position, size, rotation, DOWN_CENTER);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"shop_anim.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	AnimationClip* ShopAnim = new AnimationClip(L"ShopAnim", srcTex, 6, Values::ZeroVec2, Vector2(texSize.x, texSize.y), false, 1.f / 4.f);

	animator->AddAnimClip(ShopAnim);
	animator->SetCurrentAnimClip(L"ShopAnim");

	ar->SetAnimator(animator);

	SAFE_DELETE(srcTex);

	tr = new TextureRect({ position.x, position.y + size.y / 1.3f, position.z }, { 30.f,30.f,1.f }, rotation, TexturePath + L"E_down.png", DOWN_CENTER);

	collision = new BoundingBox(BoundingBox::Object);
	collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);
	collision->Update({ position.x, position.y , position.z }, { size.x, size.y / 1.5f, size.z }, rotation);

}

Shop::~Shop()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(tr);
	SAFE_DELETE(animator);
	SAFE_DELETE(ar);
}

void Shop::Update()
{
	animator->Update();


	ar->Update({ position.x, position.y, position.z }, size, rotation);

	vector<BoundingBox*> player = BoundingBox::GetTagCollision(BoundingBox::Player);

	isDetect = false;
	if (BoundingBox::OBB(player[0], collision))
		isDetect = true;

	if (isDetect)
	{
		if (Keyboard::Get()->Down('E'))
		{
			Sounds::Get()->Play("shop_enter");
		}
		if (Keyboard::Get()->Down('F'))
		{
			Sounds::Get()->Play("buyitem");
		}
	}

}

void Shop::Render()
{
	ar->Render();

	if (isDetect)
	{
		tr->Render();
	}
}

void Shop::Init()
{
	collision->SetActive(false);
}

void Shop::OnActive()
{
	collision->SetActive(true);

}



UpgradeNPC::UpgradeNPC(Vector3 position)
	:FootHolder(position, { 100,100,1 }, 0.f)
{
	ar = new AnimationRect(position, size, rotation, DOWN_CENTER);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"npc_hunt_f.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	AnimationClip* npc_hunt_f = new AnimationClip(L"npc_hunt_f", srcTex, 4, Values::ZeroVec2, Vector2(texSize.x, texSize.y), false, 1.f / 4.f);

	animator->AddAnimClip(npc_hunt_f);
	animator->SetCurrentAnimClip(L"npc_hunt_f");

	ar->SetAnimator(animator);

	SAFE_DELETE(srcTex);

	tr = new TextureRect({ position.x, position.y + size.y + 10.f, position.z }, { 30.f,30.f,1.f }, rotation, TexturePath + L"E_down.png", DOWN_CENTER);

	collision = new BoundingBox(BoundingBox::Object);
	collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_CENTER);
	collision->Update({ position.x, position.y , position.z }, { size.x, size.y, size.z }, rotation);

	us = new UpgradeShop();

}

UpgradeNPC::~UpgradeNPC()
{
	SAFE_DELETE(us);
	SAFE_DELETE(collision);
	SAFE_DELETE(tr);
	SAFE_DELETE(animator);
	SAFE_DELETE(ar);
}

void UpgradeNPC::Update()
{
	animator->Update();


	ar->Update({ position.x + 15.f, position.y, position.z }, size, rotation);

	vector<BoundingBox*> player = BoundingBox::GetTagCollision(BoundingBox::Player);

	isDetect = false;
	if (BoundingBox::OBB(player[0], collision))
		isDetect = true;

	if (isDetect)
	{
		if (Keyboard::Get()->Down('E'))
		{
			Sounds::Get()->Play("hunterScript");
			isOn = true;
		}
		if (Keyboard::Get()->Down(VK_ESCAPE))
		{
			isOn = false;
			us->Init();
		}
	}
	else
	{
		isOn = false;
		us->Init();
	}

	if (isOn)
	{
		us->Update();
	}

}

void UpgradeNPC::Render()
{
	ar->Render();
	if (isDetect)
	{
		tr->Render();
	}
	
}

void UpgradeNPC::PostRender()
{
	if (isOn)
	{
		us->Render();

		Text::Get()->BeginDraw();
		{
			int soul = PlayerStatus::Get()->GetSoulPoint();
			wstring str = to_wstring(soul) ;
			float size = 25;
			Vector2 pos = Vector2(780, 230);
			Text::Get()->RenderText(str, pos, Color(0, 0, 0, 1), size, true);
		}
		Text::Get()->EndDraw();

		Text::Get()->BeginDraw();
		{
			wstring str = L"Soul";
			float size = 25;
			Vector2 pos = Vector2(850, 230);
			Text::Get()->RenderText(str, pos, Color(1, 1, 0, 1), size, false);
		}
		Text::Get()->EndDraw();

	}
	
}

void UpgradeNPC::Init()
{
	collision->SetActive(false);
	isOn = false;
}

void UpgradeNPC::OnActive()
{
	collision->SetActive(true);

}
