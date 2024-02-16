#include "Framework.h"
#include "MainProfile.h"

MainProfile::MainProfile()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	tr = new TextureRect({ width - 40, height, 0.f }, { 408,150,1 }, 0.f, TexturePath + L"UI/MainUI(74_31).png", UP_LEFT);
	arrow = new TextureRect({ width + 129, height - 78, 0.f }, { 34,34,1 }, 0.f, TexturePath + L"UI/bowicon.png", UP_LEFT);

	// Animation
	{
		ar = new AnimationRect({ width - 41, height - 22, 0.f }, { 200,80,1 }, 0.f, UP_LEFT);
		animator = new Animator();

		Texture2D* srcTex = new Texture2D(TexturePath + L"UI/" + L"RedHoodProfile.png");

		Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

		AnimationClip* profile = new AnimationClip(L"profile", srcTex, 18, Values::ZeroVec2, {texSize.x, texSize.y}, false, 1.f / 6.f);

		animator->AddAnimClip(profile);

		animator->SetCurrentAnimClip(L"profile");
		ar->SetAnimator(animator);

		SAFE_DELETE(srcTex);
	}

	fhp = new ProgressBar({ width + 134, height - 24, 0.f }, { 216, 12, 1 }, 0.0f, Color(1, 0, 0, 1), UI::LEFT_TO_RIGHT);
	bhp = new ProgressBar({ width + 134, height - 24, 0.f }, { 216, 12,1 }, 0.f, Color(0.5f, 0.5f, 0, 1), UI::LEFT_TO_RIGHT);
	fstamina = new ProgressBar({ width + 122, height - 51, 0.f }, { 240,6,1 }, 0.f, Color(0, 0.5f, 0, 1), UI::LEFT_TO_RIGHT);
	bstamina = new ProgressBar({ width + 122, height - 51, 0.f }, { 240,6,1 }, 0.f, Color(1, 0.5f, 0.5f, 1), UI::LEFT_TO_RIGHT);



}
MainProfile::~MainProfile()
{
	SAFE_DELETE(bstamina);
	SAFE_DELETE(fstamina);
	SAFE_DELETE(bhp);
	SAFE_DELETE(fhp);

	SAFE_DELETE(animator);
	SAFE_DELETE(ar);

	SAFE_DELETE(arrow);
	SAFE_DELETE(tr);
}

void MainProfile::Update()
{
	deltaTime = Time::Get()->WorldDelta();

	fhp->UpdateProgressBar(PlayerStatus::Get()->GetCurrentHp() / PlayerStatus::Get()->GetMaxHp());

	if (fhp->GetPercent() != bhp->GetPercent())
	{
		HpDelay += deltaTime;
		if (HpDelay >= 0.6f)
		{
			bhp->UpdateProgressBar(fhp->GetPercent());
			HpDelay = 0.f;
		}
	}

	fstamina->UpdateProgressBar(PlayerStatus::Get()->GetCurrentStamina() / PlayerStatus::Get()->GetMaxStamina());

	if (fstamina->GetPercent() != bstamina->GetPercent())
	{
		StaminaDelay += deltaTime;
		if (StaminaDelay >= 0.6f)
		{
			bstamina->UpdateProgressBar(fstamina->GetPercent());
			StaminaDelay = 0.f;
		}
	}

	fhp->Update();
	bhp->Update();
	fstamina->Update();
	bstamina->Update();

	animator->Update();

	ar->UpdateUI();

	arrow->UpdateUI();
	tr->UpdateUI();
}

void MainProfile::Render()
{
	tr->Render();
	arrow->Render();

	ar->Render();

	bhp->Render();
	fhp->Render();
	bstamina->Render();
	fstamina->Render();

	

	Text::Get()->BeginDraw();
	{
		int max = PlayerStatus::Get()->GetMaxArrowCount();
		int cur = PlayerStatus::Get()->GetCurrentArrowCount();
		wstring str = L"x " + String::ToWstring(to_string(cur) + "/" + to_string(max));
		float size = (float)Text::Get()->GetStringWidth(str, 8.f);
		Vector2 pos = Vector2(220, 117);
		Text::Get()->RenderText(str, pos, Color(0, 0, 0, 1), size, false);
	}
	Text::Get()->EndDraw();


}
