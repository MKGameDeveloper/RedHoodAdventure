#include "Framework.h"
#include "Button.h"

Button::Button()
{
}

void Button::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;
}

void Button::OnActive()
{
}


void Button::IsClick()
{
}

bool Button::IsPress()
{
	return (!prepress && ispress);
}

void Button::SetNonPress()
{
	prepress = ispress;
	ispress = false;
}

bool Button::IsDetected()
{
	return (!predetected && isdetected);
}




DaggerComboUpgrade::DaggerComboUpgrade()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 740, height - 520, 0.f };
	size = { 140,56,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/upgradeNonPress.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y - 10, size.z }, 0.f, TexturePath + L"UI/upgradePress.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);

}

DaggerComboUpgrade::~DaggerComboUpgrade()
{
	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void DaggerComboUpgrade::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;
}

void DaggerComboUpgrade::OnActive()
{
}

void DaggerComboUpgrade::Update()
{
	NonPress->UpdateUI();
	Press->UpdateUI();

	IsClick();

}

void DaggerComboUpgrade::Render()
{
	if (!isdetected)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();
	}

}

void DaggerComboUpgrade::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
			Sounds::Get()->Play("ButtonSound");

		}

		if (Mouse::Get()->Press(0))
		{
			if (PlayerStatus::Get()->GetsCount() < 3)
			{
				if (PlayerStatus::Get()->GetSoulPoint() >= 30)
				{
					prepress = ispress;
					ispress = true;

					Sounds::Get()->Play("UpgradeSound");
					PlayerStatus::Get()->PlusSCount();
					PlayerStatus::Get()->UseSoulPoint(30);
				}
			}
		}
		else
		{
			prepress = ispress;
			ispress = false;
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}
}



DaggerComboButton::DaggerComboButton()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 515, height - 330, 0.f };
	size = { 40,40,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/UnCheckedBox.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y, size.z }, 0.f, TexturePath + L"UI/CheckedBox.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);



	dcb = new TextureRect({ width + 370, height - 339, 0.f }, { 60, 60, 1 }, 0.f, TexturePath + L"UI/ComboDagger.png", DOWN_LEFT);
	textBoard = new TextureRect({ width + 605, height - 400, 0.f }, { 265, 150, 1 }, 0.f, TexturePath + L"UI/ExplainUI.png", DOWN_LEFT);

	text = new TextureRect({ width + 620, height - 265, 0.f }, { 234, 117, 1 }, 0.f, TexturePath + L"UI/DCT.png", UP_LEFT);
	mut = new TextureRect({ width + 620, height - 265, 0.f }, { 234, 117, 1 }, 0.f, TexturePath + L"UI/MUT.png", UP_LEFT);

	dcu = new DaggerComboUpgrade();
	dcu->Update();
}

DaggerComboButton::~DaggerComboButton()
{
	SAFE_DELETE(dcu);

	SAFE_DELETE(mut);
	SAFE_DELETE(text);
	SAFE_DELETE(textBoard);
	SAFE_DELETE(dcb);

	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void DaggerComboButton::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;

	dcu->Init();
}

void DaggerComboButton::OnActive()
{
}

void DaggerComboButton::Update()
{

	NonPress->UpdateUI();
	Press->UpdateUI();
	dcb->UpdateUI();
	textBoard->UpdateUI();
	text->UpdateUI();
	mut->UpdateUI();


	IsClick();

	if (ispress)
	{
		if (PlayerStatus::Get()->GetsCount() == 3)
		{

		}
		else
		{
			dcu->Update();
		}
	}
}

void DaggerComboButton::Render()
{
	if (!ispress)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();

		textBoard->Render();


		if (PlayerStatus::Get()->GetsCount() == 3)
		{
			mut->Render();
		}
		else
		{
			text->Render();
			dcu->Render();
		}
	}

	dcb->Render();
}

void DaggerComboButton::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
		}

		if (Mouse::Get()->Press(0))
		{
			prepress = ispress;
			ispress = true;

			if (IsPress())
				Sounds::Get()->Play("ButtonSound");

			// 실행될 코드
			{

			}
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}

}



DaggerDamageUpgrade::DaggerDamageUpgrade()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 740, height - 520, 0.f };
	size = { 140,56,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/upgradeNonPress.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y - 10, size.z }, 0.f, TexturePath + L"UI/upgradePress.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);

}

DaggerDamageUpgrade::~DaggerDamageUpgrade()
{
	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void DaggerDamageUpgrade::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;
}

void DaggerDamageUpgrade::OnActive()
{
}

void DaggerDamageUpgrade::Update()
{
	NonPress->UpdateUI();
	Press->UpdateUI();

	IsClick();

}

void DaggerDamageUpgrade::Render()
{
	if (!isdetected)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();
	}

}

void DaggerDamageUpgrade::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
			Sounds::Get()->Play("ButtonSound");

		}

		if (Mouse::Get()->Press(0))
		{
			if (PlayerStatus::Get()->GetSoulPoint() >= 30)
			{
				prepress = ispress;
				ispress = true;

				if (IsPress())
				{
					Sounds::Get()->Play("UpgradeSound");
					PlayerStatus::Get()->PlusSDamage();
					PlayerStatus::Get()->UseSoulPoint(30);
				}
				
			}
			
		}
		else
		{
			prepress = ispress;
			ispress = false;
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}
}



DaggerDamageButton::DaggerDamageButton()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 515, height - 410, 0.f };
	size = { 40,40,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/UnCheckedBox.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y, size.z }, 0.f, TexturePath + L"UI/CheckedBox.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);



	ddb = new TextureRect({ width + 370, height - 419, 0.f }, { 60, 60, 1 }, 0.f, TexturePath + L"UI/DamageDagger.png", DOWN_LEFT);
	textBoard = new TextureRect({ width + 605, height - 400, 0.f }, { 265, 150, 1 }, 0.f, TexturePath + L"UI/ExplainUI.png", DOWN_LEFT);

	text = new TextureRect({ width + 620, height - 265, 0.f }, { 234, 117, 1 }, 0.f, TexturePath + L"UI/DDT.png", UP_LEFT);
	mut = new TextureRect({ width + 620, height - 265, 0.f }, { 234, 117, 1 }, 0.f, TexturePath + L"UI/MUT.png", UP_LEFT);

	ddu = new DaggerDamageUpgrade();
	ddu->Update();
}

DaggerDamageButton::~DaggerDamageButton()
{
	SAFE_DELETE(ddu);

	SAFE_DELETE(mut);
	SAFE_DELETE(text);
	SAFE_DELETE(textBoard);
	SAFE_DELETE(ddb);

	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void DaggerDamageButton::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;

	ddu->Init();
}

void DaggerDamageButton::OnActive()
{
}

void DaggerDamageButton::Update()
{

	NonPress->UpdateUI();
	Press->UpdateUI();
	ddb->UpdateUI();
	textBoard->UpdateUI();
	text->UpdateUI();
	mut->UpdateUI();


	IsClick();

	if (ispress)
	{
		ddu->Update();
	}
}

void DaggerDamageButton::Render()
{
	if (!ispress)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();

		textBoard->Render();


		text->Render();
		ddu->Render();

		Text::Get()->BeginDraw();
		{
			wstring str = L"Damage";
			float size = 20;
			Vector2 pos = Vector2(645, 430);
			Text::Get()->RenderText(str, pos, Color(1, 0, 0, 1), size, true);
		}
		Text::Get()->EndDraw();

		Text::Get()->BeginDraw();
		{
			int damage = PlayerStatus::Get()->GetsDamage();
			wstring str = L" : " + to_wstring(damage);
			float size = 20;
			Vector2 pos = Vector2(720, 430);
			Text::Get()->RenderText(str, pos, Color(0, 0, 0, 1), size, false);
		}
		Text::Get()->EndDraw();
	}

	ddb->Render();
}

void DaggerDamageButton::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
		}

		if (Mouse::Get()->Press(0))
		{
			prepress = ispress;
			ispress = true;

			if (IsPress())
				Sounds::Get()->Play("ButtonSound");

			// 실행될 코드
			{

			}
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}

}




DaggerButton::DaggerButton()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 339, height - 244, 0.f };
	size = { 75,40,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/daggerButton.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y - 4, size.z }, 0.f, TexturePath + L"UI/pressedDaggerButton.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);

	dcb = new DaggerComboButton();
	ddb = new DaggerDamageButton();
}

DaggerButton::~DaggerButton()
{
	SAFE_DELETE(ddb);
	SAFE_DELETE(dcb);
	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void DaggerButton::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;

	dcb->Init();
	ddb->Init();
}

void DaggerButton::OnActive()
{
}

void DaggerButton::Update()
{

	NonPress->UpdateUI();
	Press->UpdateUI();

	IsClick();

	if (ispress)
	{
		dcb->Update();
		ddb->Update();

		if (dcb->IsPress())
		{
			ddb->Init();
		}
		else if (ddb->IsPress())
		{
			dcb->Init();
		}
	}
}

void DaggerButton::Render()
{
	if (!ispress)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();
		dcb->Render();
		ddb->Render();
	}
}

void DaggerButton::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
		}

		if (Mouse::Get()->Press(0))
		{
			prepress = ispress;
			ispress = true;

			if (IsPress())
				Sounds::Get()->Play("ButtonSound");

			// 실행될 코드
			{

			}
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}

}




AxeComboUpgrade::AxeComboUpgrade()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 740, height - 520, 0.f };
	size = { 140,56,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/upgradeNonPress.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y - 10, size.z }, 0.f, TexturePath + L"UI/upgradePress.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);

}

AxeComboUpgrade::~AxeComboUpgrade()
{
	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void AxeComboUpgrade::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;
}

void AxeComboUpgrade::OnActive()
{
}

void AxeComboUpgrade::Update()
{
	NonPress->UpdateUI();
	Press->UpdateUI();

	IsClick();

}

void AxeComboUpgrade::Render()
{
	if (!isdetected)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();
	}

}

void AxeComboUpgrade::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
			Sounds::Get()->Play("ButtonSound");

		}

		if (Mouse::Get()->Press(0))
		{
			if (PlayerStatus::Get()->GeteCount() < 3)
			{
				if (PlayerStatus::Get()->GetSoulPoint() >= 30)
				{
					prepress = ispress;
					ispress = true;

					Sounds::Get()->Play("UpgradeSound");
					PlayerStatus::Get()->PlusECount();
					PlayerStatus::Get()->UseSoulPoint(30);
				}
			}
		}
		else
		{
			prepress = ispress;
			ispress = false;
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}
}



AxeComboButton::AxeComboButton()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 515, height - 330, 0.f };
	size = { 40,40,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/UnCheckedBox.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y, size.z }, 0.f, TexturePath + L"UI/CheckedBox.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);



	acb = new TextureRect({ width + 370, height - 339, 0.f }, { 60, 60, 1 }, 0.f, TexturePath + L"UI/ComboAxe.png", DOWN_LEFT);
	textBoard = new TextureRect({ width + 605, height - 400, 0.f }, { 265, 150, 1 }, 0.f, TexturePath + L"UI/ExplainUI.png", DOWN_LEFT);

	text = new TextureRect({ width + 620, height - 265, 0.f }, { 234, 117, 1 }, 0.f, TexturePath + L"UI/ACT.png", UP_LEFT);
	mut = new TextureRect({ width + 620, height - 265, 0.f }, { 234, 117, 1 }, 0.f, TexturePath + L"UI/MUT.png", UP_LEFT);

	acu = new AxeComboUpgrade();
	acu->Update();
}

AxeComboButton::~AxeComboButton()
{
	SAFE_DELETE(acu);

	SAFE_DELETE(mut);
	SAFE_DELETE(text);
	SAFE_DELETE(textBoard);
	SAFE_DELETE(acb);

	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void AxeComboButton::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;

	acu->Init();
}

void AxeComboButton::OnActive()
{
}

void AxeComboButton::Update()
{

	NonPress->UpdateUI();
	Press->UpdateUI();
	acb->UpdateUI();
	textBoard->UpdateUI();
	text->UpdateUI();
	mut->UpdateUI();


	IsClick();

	if (ispress)
	{
		if (PlayerStatus::Get()->GeteCount() == 3)
		{

		}
		else
		{
			acu->Update();
		}
	}
}

void AxeComboButton::Render()
{
	if (!ispress)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();

		textBoard->Render();


		if (PlayerStatus::Get()->GeteCount() == 3)
		{
			mut->Render();
		}
		else
		{
			text->Render();
			acu->Render();
		}
	}

	acb->Render();
}

void AxeComboButton::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
		}

		if (Mouse::Get()->Press(0))
		{
			prepress = ispress;
			ispress = true;

			if (IsPress())
				Sounds::Get()->Play("ButtonSound");

			// 실행될 코드
			{

			}
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}

}



AxeDamageUpgrade::AxeDamageUpgrade()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 740, height - 520, 0.f };
	size = { 140,56,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/upgradeNonPress.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y - 10, size.z }, 0.f, TexturePath + L"UI/upgradePress.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);

}

AxeDamageUpgrade::~AxeDamageUpgrade()
{
	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void AxeDamageUpgrade::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;
}

void AxeDamageUpgrade::OnActive()
{
}

void AxeDamageUpgrade::Update()
{
	NonPress->UpdateUI();
	Press->UpdateUI();

	IsClick();

}

void AxeDamageUpgrade::Render()
{
	if (!isdetected)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();
	}

}

void AxeDamageUpgrade::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
			Sounds::Get()->Play("ButtonSound");

		}

		if (Mouse::Get()->Press(0))
		{
			if (PlayerStatus::Get()->GetSoulPoint() >= 30)
			{
				prepress = ispress;
				ispress = true;

				if (IsPress())
				{
					Sounds::Get()->Play("UpgradeSound");
					PlayerStatus::Get()->PlusEDamage();
					PlayerStatus::Get()->UseSoulPoint(30);
				}
				
			}

		}
		else
		{
			prepress = ispress;
			ispress = false;
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}
}



AxeDamageButton::AxeDamageButton()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 515, height - 410, 0.f };
	size = { 40,40,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/UnCheckedBox.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y, size.z }, 0.f, TexturePath + L"UI/CheckedBox.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);



	adb = new TextureRect({ width + 370, height - 419, 0.f }, { 60, 60, 1 }, 0.f, TexturePath + L"UI/DamageAxe.png", DOWN_LEFT);
	textBoard = new TextureRect({ width + 605, height - 400, 0.f }, { 265, 150, 1 }, 0.f, TexturePath + L"UI/ExplainUI.png", DOWN_LEFT);

	text = new TextureRect({ width + 620, height - 265, 0.f }, { 234, 117, 1 }, 0.f, TexturePath + L"UI/ADT.png", UP_LEFT);
	mut = new TextureRect({ width + 620, height - 265, 0.f }, { 234, 117, 1 }, 0.f, TexturePath + L"UI/MUT.png", UP_LEFT);

	adu = new AxeDamageUpgrade();
	adu->Update();
}

AxeDamageButton::~AxeDamageButton()
{
	SAFE_DELETE(adu);

	SAFE_DELETE(mut);
	SAFE_DELETE(text);
	SAFE_DELETE(textBoard);
	SAFE_DELETE(adb);

	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void AxeDamageButton::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;

	adu->Init();
}

void AxeDamageButton::OnActive()
{
}

void AxeDamageButton::Update()
{

	NonPress->UpdateUI();
	Press->UpdateUI();
	adb->UpdateUI();
	textBoard->UpdateUI();
	text->UpdateUI();
	mut->UpdateUI();


	IsClick();

	if (ispress)
	{
		adu->Update();
	}
}

void AxeDamageButton::Render()
{
	if (!ispress)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();

		textBoard->Render();


		
		text->Render();
		adu->Render();

		Text::Get()->BeginDraw();
		{
			wstring str = L"Damage";
			float size = 20;
			Vector2 pos = Vector2(645, 430);
			Text::Get()->RenderText(str, pos, Color(1, 0, 0, 1), size, true);
		}
		Text::Get()->EndDraw();

		Text::Get()->BeginDraw();
		{
			int damage = PlayerStatus::Get()->GeteDamage();
			wstring str = L" : " + to_wstring(damage);
			float size = 20;
			Vector2 pos = Vector2(720, 430);
			Text::Get()->RenderText(str, pos, Color(0, 0, 0, 1), size, false);
		}
		Text::Get()->EndDraw();
	}

	adb->Render();
}

void AxeDamageButton::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
		}

		if (Mouse::Get()->Press(0))
		{
			prepress = ispress;
			ispress = true;

			if (IsPress())
				Sounds::Get()->Play("ButtonSound");

			// 실행될 코드
			{

			}
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}

}



AxeButton::AxeButton()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 426, height - 244, 0.f };
	size = { 75,40,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/AxeButton.png", DOWN_LEFT);
	Press = new TextureRect(position, { size.x, size.y - 4, size.z }, 0.f, TexturePath + L"UI/pressedAxeButton.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);

	acb = new AxeComboButton();
	adb = new AxeDamageButton();
}

AxeButton::~AxeButton()
{
	SAFE_DELETE(adb);
	SAFE_DELETE(acb);
	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void AxeButton::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;

	acb->Init();
	adb->Init();
}

void AxeButton::OnActive()
{
}

void AxeButton::Update()
{

	NonPress->UpdateUI();
	Press->UpdateUI();

	IsClick();

	if (ispress)
	{
		acb->Update();
		adb->Update();

		if (acb->IsPress())
		{
			adb->Init();
		}
		else if (adb->IsPress())
		{
			acb->Init();
		}
	}
}

void AxeButton::Render()
{
	if (!ispress)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();
		acb->Render();
		adb->Render();
	}
}

void AxeButton::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
		}

		if (Mouse::Get()->Press(0))
		{
			prepress = ispress;
			ispress = true;

			if (IsPress())
				Sounds::Get()->Play("ButtonSound");

			// 실행될 코드
			{

			}
		}
	}
	else
	{
		predetected = isdetected;
		isdetected = false;
	}

}



BowButton::BowButton()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	position = { width + 513, height - 244, 0.f };
	size = { 75,40,1 };

	NonPress = new TextureRect(position, size, 0.f, TexturePath + L"UI/BowButton.png", DOWN_LEFT);
	Press = new TextureRect(position, {size.x, size.y - 4, size.z}, 0.f, TexturePath + L"UI/pressedBowButton.png", DOWN_LEFT);

	position += Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);
}

BowButton::~BowButton()
{
	SAFE_DELETE(Press);
	SAFE_DELETE(NonPress);
}

void BowButton::Init()
{
	prepress = false;
	ispress = false;
	isOn = false;
}

void BowButton::OnActive()
{
}

void BowButton::Update()
{

	NonPress->UpdateUI();
	Press->UpdateUI();

	IsClick();

	if (ispress)
	{

	}
}

void BowButton::Render()
{
	if (!ispress)
	{
		NonPress->Render();
	}
	else
	{
		Press->Render();
	}
}

void BowButton::IsClick()
{
	mPos = Mouse::Get()->GetPosition();

	if (mPos.x >= position.x && mPos.x <= (position.x + size.x) && mPos.y >= position.y && mPos.y <= (position.y + size.y))
	{
		predetected = isdetected;
		isdetected = true;

		if (IsDetected())
		{
			// 처음 마우스를 가져다 댔을 경우
		}

		if (Mouse::Get()->Press(0))
		{
			prepress = ispress;
			ispress = true;

			if(IsPress())
				Sounds::Get()->Play("ButtonSound");

			// 실행될 코드
			{

			}
		}
	}

}







